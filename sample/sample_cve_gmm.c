/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#include "lib_cve.h"
#include "sample_comm_cve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define CVE_GMM_POWER_TEST

typedef struct {
    CVE_SRC_IMAGE_T stSrc;
    CVE_SRC_IMAGE_T stFactor;
    CVE_DST_IMAGE_T stFg;
    CVE_DST_IMAGE_T stBg;
    CVE_MEM_INFO_T stModel;
    CVE_GMM_CTRL_T stGmmCtrl;
    FILE *pFpSrc1;
#ifndef CVE_GMM_POWER_TEST
    FILE *pFpSrc2;
    FILE *pFpDstFg;
    FILE *pFpDstBg;
    FILE *pFpDstMemPrev;
    FILE *pFpDstMem;
#endif
} SAMPLE_CVE_GMM_INFO_T;

SAMPLE_CVE_GMM_INFO_T stGmmInfo;

void SAMPLE_CVE_GmmCaseList(void)
{
    printf("\t\t  0) GmmMode: Binary, Src U8C1, dsmode = 0.\n");
    printf("\t\t  1) GmmMode: Trunc, Src U8C3_PLANAR, dsmode = 0.\n");
    printf("\t\t  2) GmmMode: Binary, Src U8C1, dsmode = 1.\n");
    printf("\t\t  3) GmmMode: Trunc, Src U8C3_PLANAR, dsmode = 1.\n");
    printf("\t\t  4) GmmMode: Binary, Src U8C1, dsmode = 2.\n");
    printf("\t\t  5) GmmMode: Trunc, Src U8C3_PLANAR, dsmode = 2.\n");
    return;
}

static AML_VOID SAMPLE_CVE_GmmUninit(SAMPLE_CVE_GMM_INFO_T *pstGmmInfo)
{

#ifndef CVE_GMM_POWER_TEST
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = SAMPLE_COMM_CVE_WriteFile(&pstGmmInfo->stFactor, pstGmmInfo->pFpSrc2);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Fg Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile(&pstGmmInfo->stFg, pstGmmInfo->pFpDstFg);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Fg Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile(&pstGmmInfo->stBg, pstGmmInfo->pFpDstBg);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Bg Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile_From_Mem(&pstGmmInfo->stModel, pstGmmInfo->pFpDstMem);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Mem Image failed!\n", s32Ret);
    }
#endif
    CVE_PMZ_FREE(pstGmmInfo->stSrc.au64PhyAddr[0], pstGmmInfo->stSrc.au64VirAddr[0]);
    CVE_PMZ_FREE(pstGmmInfo->stFactor.au64PhyAddr[0], pstGmmInfo->stFactor.au64VirAddr[0]);
    CVE_PMZ_FREE(pstGmmInfo->stFg.au64PhyAddr[0], pstGmmInfo->stFg.au64VirAddr[0]);
    CVE_PMZ_FREE(pstGmmInfo->stBg.au64PhyAddr[0], pstGmmInfo->stBg.au64VirAddr[0]);
    CVE_PMZ_FREE(pstGmmInfo->stModel.u64PhyAddr, pstGmmInfo->stModel.u64VirAddr);
    CVE_CLOSE_FILE(pstGmmInfo->pFpSrc1);
#ifndef CVE_GMM_POWER_TEST
    CVE_CLOSE_FILE(pstGmmInfo->pFpSrc2);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstFg);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstBg);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstMem);
#endif
}

static AML_VOID SAMPLE_CVE_GMM_FACTOR_INIT(CVE_IMAGE_T *pstImg, AML_U16 value)
{
    AML_U32 i, j;
    AML_U16 *pU16;
    AML_U32 u32Width;
    AML_U32 u32Height;
    AML_U32 u32Stride;

    pU16 = (AML_U16 *)(AML_UL)pstImg->au64VirAddr[0];
    u32Width = pstImg->u32Width;
    u32Height = pstImg->u32Height;
    u32Stride = pstImg->au32Stride[0];
    for (i = 0; i < u32Width; i++) {
        for (j = 0; j < u32Height; j++) {
            pU16[i + j * u32Stride] = value;
        }
    }
}

static AML_S32 SAMPLE_CVE_GmmInit(SAMPLE_CVE_GMM_INFO_T *pstGmmInfo, CVE_IMAGE_TYPE_E enSrcType,
                                  CVE_GMM_DOWN_SCALE_MODE_E enDownScaleMode, AML_U32 u32Width,
                                  AML_U32 u32Height, AML_CHAR *pchSrc1FileName,
                                  AML_CHAR *pchSrc2FileName, AML_CHAR *pchDstFgFileName,
                                  AML_CHAR *pchDstBgFileName, AML_CHAR *pchDstMemPrevFileName,
                                  AML_CHAR *pchDstMemFileName)
{
    AML_S32 s32Ret = AML_SUCCESS;
    AML_U32 u32DstSize;
    AML_U8 modelnum;
    AML_U32 channel_num;

    memset(&pstGmmInfo->stSrc, 0, sizeof(CVE_SRC_IMAGE_T));
    memset(&pstGmmInfo->stFactor, 0, sizeof(CVE_SRC_IMAGE_T));
    memset(&pstGmmInfo->stFg, 0, sizeof(CVE_DST_IMAGE_T));
    memset(&pstGmmInfo->stBg, 0, sizeof(CVE_DST_IMAGE_T));
    memset(&pstGmmInfo->stModel, 0, sizeof(CVE_MEM_INFO_T));

    CVE_OPEN_FILE(pstGmmInfo->pFpSrc1, pchSrc1FileName, "r+");
#ifndef CVE_GMM_POWER_TEST
    CVE_OPEN_FILE(pstGmmInfo->pFpSrc2, pchSrc2FileName, "w");
    CVE_OPEN_FILE(pstGmmInfo->pFpDstFg, pchDstFgFileName, "w");
    CVE_OPEN_FILE(pstGmmInfo->pFpDstBg, pchDstBgFileName, "w");
    CVE_OPEN_FILE(pstGmmInfo->pFpDstMemPrev, pchDstMemPrevFileName, "r+");
    CVE_OPEN_FILE(pstGmmInfo->pFpDstMem, pchDstMemFileName, "w");
#endif
    modelnum = 3;
    if (enSrcType == CVE_IMAGE_TYPE_U8C3_PACKAGE) {
        channel_num = 3;
    } else {
        channel_num = 1;
    }
    s32Ret = SAMPLE_COMM_CVE_CreateImage(&pstGmmInfo->stSrc, enSrcType, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Src Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT1;
    }

    s32Ret = SAMPLE_COMM_CVE_CreateImage(&pstGmmInfo->stFactor, CVE_IMAGE_TYPE_U16C1,
                                         u32Width >> enDownScaleMode, u32Height >> enDownScaleMode);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Src Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT2;
    }

    s32Ret = SAMPLE_COMM_CVE_CreateImage(&pstGmmInfo->stFg, CVE_IMAGE_TYPE_U8C1,
                                         u32Width >> enDownScaleMode, u32Height >> enDownScaleMode);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT3;
    }

    s32Ret = SAMPLE_COMM_CVE_CreateImage(&pstGmmInfo->stBg, enSrcType, u32Width >> enDownScaleMode,
                                         u32Height >> enDownScaleMode);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT4;
    }

    u32DstSize = (u32Width >> enDownScaleMode) * (1 + modelnum * (4 + 2 * channel_num)) *
                 (u32Height >> enDownScaleMode);
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstGmmInfo->stModel, u32DstSize);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Mem failed!\n", s32Ret);
        goto CVE_GMM_EXIT5;
    }

    s32Ret = SAMPLE_COMM_CVE_ReadFile(&pstGmmInfo->stSrc, pstGmmInfo->pFpSrc1);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT6;
    }

#ifndef CVE_GMM_POWER_TEST
    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Mem(&pstGmmInfo->stModel, pstGmmInfo->pFpDstMemPrev);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read dst mem model Image failed!\n", s32Ret);
        goto CVE_GMM_EXIT6;
    }
#endif
    SAMPLE_CVE_GMM_FACTOR_INIT(&pstGmmInfo->stFactor, 0x2020);

    pstGmmInfo->stGmmCtrl.enOutputMode = CVE_GMM_OUTPUT_MODE_FG_AND_BG;
    pstGmmInfo->stGmmCtrl.enSnsFactorMode = CVE_GMM_SNS_FACTOR_MODE_PIX;
    pstGmmInfo->stGmmCtrl.enDurationUpdateFactorMode = CVE_GMM_DURATION_UPDATE_FACTOR_MODE_PIX;
    pstGmmInfo->stGmmCtrl.enDownScaleMode = enDownScaleMode;
    pstGmmInfo->stGmmCtrl.enOutputDataMode = CVE_GMM_OUTPUT_DATA_MODE_U8;
    pstGmmInfo->stGmmCtrl.u10q6NoiseVar = (25 * channel_num) << 6;
    pstGmmInfo->stGmmCtrl.u10q6MaxVar = (40 * channel_num) << 6;
    pstGmmInfo->stGmmCtrl.u10q6MinVar = (15 * channel_num) << 6;
    pstGmmInfo->stGmmCtrl.u0q16LearnRate = ((1 << 16) - 1) / 500;  //(1 / 500) * ((1 << 16) - 1);
    pstGmmInfo->stGmmCtrl.u0q16InitWeight = ((1 << 16) - 1) / 500; // 1024;
    pstGmmInfo->stGmmCtrl.u0q16WeightThr = 58982;
    pstGmmInfo->stGmmCtrl.u8ModelNum = modelnum;
    pstGmmInfo->stGmmCtrl.u3q7SigmaScale = 320;
    pstGmmInfo->stGmmCtrl.enFastLearn = 1;
    goto CVE_GMM_EXIT0;

CVE_GMM_EXIT6:
    CVE_PMZ_FREE(pstGmmInfo->stModel.u64PhyAddr, pstGmmInfo->stModel.u64VirAddr);
CVE_GMM_EXIT5:
    CVE_PMZ_FREE(pstGmmInfo->stBg.au64PhyAddr[0], pstGmmInfo->stBg.au64VirAddr[0]);
CVE_GMM_EXIT4:
    CVE_PMZ_FREE(pstGmmInfo->stFg.au64PhyAddr[0], pstGmmInfo->stFg.au64VirAddr[0]);
CVE_GMM_EXIT3:
    CVE_PMZ_FREE(pstGmmInfo->stFactor.au64PhyAddr[0], pstGmmInfo->stFactor.au64VirAddr[0]);
CVE_GMM_EXIT2:
    CVE_PMZ_FREE(pstGmmInfo->stSrc.au64PhyAddr[0], pstGmmInfo->stSrc.au64VirAddr[0]);
CVE_GMM_EXIT1:
    CVE_CLOSE_FILE(pstGmmInfo->pFpSrc1);
#ifndef CVE_GMM_POWER_TEST
    CVE_CLOSE_FILE(pstGmmInfo->pFpSrc2);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstFg);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstBg);
    CVE_CLOSE_FILE(pstGmmInfo->pFpDstMem);
#endif
CVE_GMM_EXIT0:

    return s32Ret;
}

static AML_S32 SAMPLE_CVE_GmmProc(SAMPLE_CVE_GMM_INFO_T *pstGmmInfo)
{
    AML_BOOL_E bInstant = AML_FALSE;
    AML_BOOL_E bFinish = AML_FALSE;
    CVE_HANDLE cveHandle;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = CVE_GMM(&cveHandle, &pstGmmInfo->stSrc, &pstGmmInfo->stFactor, &pstGmmInfo->stFg,
                     &pstGmmInfo->stBg, &pstGmmInfo->stModel, &pstGmmInfo->stGmmCtrl, bInstant);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE GMM Proc error\n");
        return s32Ret;
    }
    s32Ret = CVE_Query(cveHandle, &bFinish, AML_TRUE);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE GMM Query error\n");
        return s32Ret;
    }

    return s32Ret;
}

AML_S32 SAMPLE_CVE_GmmCase(AML_U32 u32CaseIndex)
{
    AML_U32 u32Width = 720;
    AML_U32 u32Height = 576;
    AML_S32 s32Ret;
    CVE_IMAGE_TYPE_E enSrcType;
    CVE_GMM_DOWN_SCALE_MODE_E enDownScaleMode;
    AML_CHAR pFpSrc1Name[64] = {0};
    AML_CHAR pFpSrc2Name[64] = {0};
    AML_CHAR pFpDstFgName[64] = {0};
    AML_CHAR pFpDstBgName[64] = {0};
    AML_CHAR pFpDstMemName[64] = {0};
    AML_CHAR pFpDstMemPrevName[64] = {0};
    AML_S32 i = 1;

    switch (u32CaseIndex) {
    case 0:
        TEST_PRT("[INFO] Gmm CASE 0: GmmMode: Binary dsmode = 0\n");
        enSrcType = CVE_IMAGE_TYPE_U8C1;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_DISABLE;
        break;
    case 1:
        TEST_PRT("[INFO] Gmm CASE 1: GmmMode: Trunc dsmode=0\n");
        enSrcType = CVE_IMAGE_TYPE_U8C3_PACKAGE;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_DISABLE;
        break;
    case 2:
        TEST_PRT("[INFO] Gmm CASE 2: GmmMode: Binary dsmode = 1 2x2\n");
        enSrcType = CVE_IMAGE_TYPE_U8C1;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_2X2;
        break;
    case 3:
        TEST_PRT("[INFO] Gmm CASE 3: GmmMode: Trunc dsmode = 1 2x2\n");
        enSrcType = CVE_IMAGE_TYPE_U8C3_PACKAGE;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_2X2;
        break;
    case 4:
        TEST_PRT("[INFO] Gmm CASE 4: GmmMode: Binary dsmode = 2 4x4\n");
        enSrcType = CVE_IMAGE_TYPE_U8C1;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_4X4;
        break;
    case 5:
        TEST_PRT("[INFO] Gmm CASE 5: GmmMode: Trunc dsmode = 2 4x4\n");
        enSrcType = CVE_IMAGE_TYPE_U8C3_PACKAGE;
        enDownScaleMode = CVE_GMM_DOWN_SCALE_MODE_4X4;
        break;
    default:
        printf("the thresh case index is invaild! valid index:\n");
        SAMPLE_CVE_GmmCaseList();
        return AML_FAILURE;
    }

    for (i = 1; i < 10; i++) {
        memset(pFpSrc1Name, 0, 64);
        memset(pFpSrc2Name, 0, 64);
        memset(pFpDstFgName, 0, 64);
        memset(pFpDstBgName, 0, 64);
        memset(pFpDstMemPrevName, 0, 64);
        memset(pFpDstMemName, 0, 64);

#ifndef CVE_GMM_POWER_TEST
        if (enSrcType == CVE_IMAGE_TYPE_U8C1) {
            sprintf(pFpSrc1Name, "/data/cve/GmmSrc/hall_%d_y.yuv", i);
            sprintf(pFpSrc2Name, "/data/cve/GmmDst_U8C1/Gmm_Src1_%d.data", i);
            sprintf(pFpDstFgName, "/data/cve/GmmDst_U8C1/GmmFg_%d.out", i);
            sprintf(pFpDstBgName, "/data/cve/GmmDst_U8C1/GmmBg_%d.out", i);
            sprintf(pFpDstMemPrevName, "/data/cve/GmmDst_U8C1/GmmPixel_%d.out", i - 1);
            sprintf(pFpDstMemName, "/data/cve/GmmDst_U8C1/GmmPixel_%d.out", i);
        } else {
            sprintf(pFpSrc1Name, "/data/cve/GmmSrc/hall_%d_rgbpackage.rgb", i);
            sprintf(pFpSrc2Name, "/data/cve/GmmDst/Gmm_Src1_%d.data", i);
            sprintf(pFpDstFgName, "/data/cve/GmmDst/GmmFg_%d.out", i);
            sprintf(pFpDstBgName, "/data/cve/GmmDst/GmmBg_%d.out", i);
            sprintf(pFpDstMemPrevName, "/data/cve/GmmDst/GmmPixel_%d.out", i - 1);
            sprintf(pFpDstMemName, "/data/cve/GmmDst/GmmPixel_%d.out", i);
        }
        printf("src1 file name:%s\n", pFpSrc1Name);
        printf("src2 file name:%s\n", pFpSrc2Name);
        printf("dst fg file name:%s\n", pFpDstFgName);
        printf("dst bg file name:%s\n", pFpDstBgName);
        printf("dst mem prev file name:%s\n", pFpDstMemPrevName);
        printf("dst mem file name:%s\n", pFpDstMemName);
#else
        sprintf(pFpSrc1Name, "/data/cve/GmmSrc/hall_1_rgbpackage.rgb");
        // sprintf(pFpSrc1Name, "/data/cve/gmm_input_1_720_576_3.bin");
        printf("src1 file name:%s\n", pFpSrc1Name);
#endif

        s32Ret = SAMPLE_CVE_GmmInit(&stGmmInfo, enSrcType, enDownScaleMode, u32Width, u32Height,
                                    pFpSrc1Name, pFpSrc2Name, pFpDstFgName, pFpDstBgName,
                                    pFpDstMemPrevName, pFpDstMemName);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("[ERROR][%x] SAMPLE_CVE_GmmInit failed!\n", s32Ret);
            return s32Ret;
        }

        s32Ret = SAMPLE_CVE_GmmProc(&stGmmInfo);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("[ERROR][%x] SAMPLE_CVE_GmmProc failed!\n", s32Ret);
        }

        SAMPLE_CVE_GmmUninit(&stGmmInfo);
        memset(&stGmmInfo, 0, sizeof(SAMPLE_CVE_GMM_INFO_T));
    }
    return s32Ret;
}
