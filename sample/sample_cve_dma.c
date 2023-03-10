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

typedef struct {
    CVE_SRC_DATA_T stSrc;
    CVE_DST_DATA_T stDst;
    CVE_DMA_CTRL_T stDmaCtrl;
    FILE *pFpSrc;
    FILE *pFpDst;
} SAMPLE_CVE_DMA_INFO_T;

SAMPLE_CVE_DMA_INFO_T stDmaInfo;

void SAMPLE_CVE_DmaCaseList(void)
{
    printf("\t\t  0) Direct Copy.\n");
    printf("\t\t  1) Interval Copy.\n");
    printf("\t\t  2) Set 3Byte.\n");
    printf("\t\t  3) Set 8Byte.\n");
    printf("\t\t  4) Not mode Copy.\n");
    return;
}

static AML_VOID SAMPLE_CVE_DmaUninit(SAMPLE_CVE_DMA_INFO_T *pstDmaInfo)
{
    SAMPLE_COMM_CVE_WriteFile_From_Data(&pstDmaInfo->stDst, pstDmaInfo->pFpDst);

    CVE_PMZ_FREE(pstDmaInfo->stSrc.dmafd, pstDmaInfo->stSrc.u64VirAddr);
    CVE_PMZ_FREE(pstDmaInfo->stDst.dmafd, pstDmaInfo->stDst.u64VirAddr);

    CVE_CLOSE_FILE(pstDmaInfo->pFpSrc);
    CVE_CLOSE_FILE(pstDmaInfo->pFpDst);
}

static AML_S32 SAMPLE_CVE_DmaInit(SAMPLE_CVE_DMA_INFO_T *pstDmaInfo, CVE_DMA_MODE_E enMode,
                                  AML_CHAR *pchSrcFileName, AML_CHAR *pchDstFileName,
                                  AML_U32 u32Width, AML_U32 u32Height)
{
    AML_S32 s32Ret = AML_SUCCESS;

    memset(&pstDmaInfo->stSrc, 0, sizeof(CVE_SRC_DATA_T));
    memset(&pstDmaInfo->stDst, 0, sizeof(CVE_DST_DATA_T));

    CVE_OPEN_FILE(pstDmaInfo->pFpSrc, pchSrcFileName, "r+");
    CVE_OPEN_FILE(pstDmaInfo->pFpDst, pchDstFileName, "w");

    s32Ret = SAMPLE_COMM_CVE_CreateData(&pstDmaInfo->stSrc, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Src Data failed!\n", s32Ret);
        goto CVE_DMA_EXIT1;
    }

    s32Ret = SAMPLE_COMM_CVE_CreateData(&pstDmaInfo->stDst, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Data failed!\n", s32Ret);
        goto CVE_DMA_EXIT2;
    }

    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Data(&pstDmaInfo->stSrc, pstDmaInfo->pFpSrc);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src Data failed!\n", s32Ret);
        goto CVE_DMA_EXIT3;
    }

    pstDmaInfo->stDmaCtrl.enMode = enMode;
    if (pstDmaInfo->stDmaCtrl.enMode == CVE_DMA_MODE_INTERVAL_COPY) {
        pstDmaInfo->stDmaCtrl.u8HorSegSize = 3;
        pstDmaInfo->stDmaCtrl.u8VerSegRows = 5;
        pstDmaInfo->stDmaCtrl.u8ElemSize = 1;
    }

    if (pstDmaInfo->stDmaCtrl.enMode == CVE_DMA_MODE_SET_3BYTE ||
        pstDmaInfo->stDmaCtrl.enMode == CVE_DMA_MODE_SET_8BYTE) {
        pstDmaInfo->stDmaCtrl.u64Val = 0x1122334455667788;
    }
    goto CVE_DMA_EXIT0;

CVE_DMA_EXIT3:
    CVE_PMZ_FREE(pstDmaInfo->stDst.u64PhyAddr, pstDmaInfo->stDst.u64VirAddr);
CVE_DMA_EXIT2:
    CVE_PMZ_FREE(pstDmaInfo->stSrc.u64PhyAddr, pstDmaInfo->stSrc.u64VirAddr);
CVE_DMA_EXIT1:
    CVE_CLOSE_FILE(pstDmaInfo->pFpSrc);
    CVE_CLOSE_FILE(pstDmaInfo->pFpDst);
CVE_DMA_EXIT0:
    return s32Ret;
}

static AML_S32 SAMPLE_CVE_DmaProc(SAMPLE_CVE_DMA_INFO_T *pstDmaInfo)
{
    AML_BOOL_E bInstant = AML_FALSE;
    AML_BOOL_E bFinish = AML_FALSE;
    CVE_HANDLE cveHandle;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = CVE_DMA(&cveHandle, &pstDmaInfo->stSrc, &pstDmaInfo->stDst, &pstDmaInfo->stDmaCtrl,
                     bInstant);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE DMA Proc error\n");
        return s32Ret;
    }
    s32Ret = CVE_Query(cveHandle, &bFinish, AML_TRUE);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE DMA Query error\n");
        return s32Ret;
    }

    return s32Ret;
}

AML_S32 SAMPLE_CVE_DmaCase(AML_U32 u32CaseIndex)
{
    AML_U32 u32Width = 1920;
    AML_U32 u32Height = 1080;
    CVE_DMA_MODE_E enMode;
    AML_S32 s32Ret;
    AML_CHAR *SrcName = "/data/cve/09140_yuv422sp.yuv";
    AML_CHAR pFpSrcName[64] = {0};
    AML_CHAR *pFpDstName = "/data/cve/dma.out";

    switch (u32CaseIndex) {
    case 0:
        TEST_PRT("[INFO] DMA CASE 0: Direct Copy\n");
        enMode = CVE_DMA_MODE_DIRECT_COPY;
        break;
    case 1:
        TEST_PRT("[INFO] DMA CASE 1: Interval Copy\n");
        enMode = CVE_DMA_MODE_INTERVAL_COPY;
        break;
    case 2:
        TEST_PRT("[INFO] DMA CASE 2: Set 3Byte\n");
        enMode = CVE_DMA_MODE_SET_3BYTE;
        break;
    case 3:
        TEST_PRT("[INFO] DMA CASE 3: Set 8Byte\n");
        enMode = CVE_DMA_MODE_SET_8BYTE;
        break;
    case 4:
        TEST_PRT("[INFO] DMA CASE 4: Not mode copy\n");
        enMode = CVE_DMA_MODE_NOT;
        break;
    default:
        printf("the dma case index is invaild! valid index:\n");
        SAMPLE_CVE_DmaCaseList();
        return AML_FAILURE;
    }

    printf("please input src file name:");
    // SAMPLE_COMM_CVE_Input_FileName(pFpSrcName, sizeof(pFpSrcName), SrcName);
    sprintf(pFpSrcName, "%s", SrcName);
    printf("src file name:%s\n", pFpSrcName);
    printf("dst file name:%s\n", pFpDstName);
    s32Ret = SAMPLE_CVE_DmaInit(&stDmaInfo, enMode, pFpSrcName, pFpDstName, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] SAMPLE_CVE_DmaInit failed!\n", s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_CVE_DmaProc(&stDmaInfo);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] SAMPLE_CVE_DmaProc failed!\n", s32Ret);
    }

    SAMPLE_CVE_DmaUninit(&stDmaInfo);
    memset(&stDmaInfo, 0, sizeof(SAMPLE_CVE_DMA_INFO_T));

    return s32Ret;
}
