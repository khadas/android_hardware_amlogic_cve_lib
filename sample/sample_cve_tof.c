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
    CVE_SRC_RAW_T stSrcRaw;
    CVE_SRC_RAW_T stSrcFpn;
    CVE_SRC_MEM_INFO_T stSrcCoef;
    CVE_SRC_MEM_INFO_T stBpc;
    CVE_DST_MEM_INFO_T stDstStatus;
    CVE_DST_MEM_INFO_T stDstIR;
    CVE_DST_MEM_INFO_T stDstData;
    CVE_DST_MEM_INFO_T stDstHist;
    CVE_TOF_CTRL_T stTofCtrl;
    FILE *pFpSrcRaw;
    FILE *pFpSrcFpn;
    FILE *pFpSrcCoef;
    FILE *pFpBpc;
    FILE *pFpDstStatus;
    FILE *pFpDstIR;
    FILE *pFpDstData;
    FILE *pFpDstHist;

    FILE *pFpTemp;
} SAMPLE_CVE_TOF_INFO_T;

SAMPLE_CVE_TOF_INFO_T stTofInfo;

AML_S32 as32PCoef_0[] = {54597, -108650, 85804, -5390, -7104};
AML_S16 as16TCoef1_0[] = {253, 12, 267, -3};
AML_S32 as32PCoef_1[] = {14035, -13113, 639, 22505, -8740};
AML_S16 as16TCoef1_1[] = {240, 8, 330, -4};

void SAMPLE_CVE_TofCaseList(void)
{
    printf("\t\t  0) Tof Raw mode Raw6,   Fpn Mode Bypass.\n");
    printf("\t\t  1) Tof Raw mode Raw7,   Fpn Mode Bypass.\n");
    printf("\t\t  2) Tof Raw mode Raw8,   Fpn Mode Bypass.\n");
    printf("\t\t  3) Tof Raw mode Raw10,  Fpn Mode Bypass.\n");
    printf("\t\t  4) Tof Raw mode Raw12,  Fpn Mode Bypass.\n");
    printf("\t\t  5) Tof Raw mode Raw6,   Fpn Mode Fpn.\n");
    printf("\t\t  6) Tof Raw mode Raw7,   Fpn Mode Fpn.\n");
    printf("\t\t  7) Tof Raw mode Raw8,   Fpn Mode Fpn.\n");
    printf("\t\t  8) Tof Raw mode Raw10,  Fpn Mode Fpn.\n");
    printf("\t\t  9) Tof Raw mode Raw12,  Fpn Mode Fpn.\n");
    printf("\t\t 10) Tof Raw mode Raw6,   Fpn Mode Fd.\n");
    printf("\t\t 11) Tof Raw mode Raw7,   Fpn Mode Fd.\n");
    printf("\t\t 12) Tof Raw mode Raw8,   Fpn Mode Fd.\n");
    printf("\t\t 13) Tof Raw mode Raw10,  Fpn Mode Fd.\n");
    printf("\t\t 14) Tof Raw mode Raw12,  Fpn Mode Fd.\n");
    return;
}

static AML_VOID SAMPLE_CVE_TofUninit(SAMPLE_CVE_TOF_INFO_T *pstTofInfo)
{
    CVE_PMZ_FREE(pstTofInfo->stSrcRaw.dmafd, pstTofInfo->stSrcRaw.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stSrcFpn.dmafd, pstTofInfo->stSrcFpn.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stSrcCoef.dmafd, pstTofInfo->stSrcCoef.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stBpc.dmafd, pstTofInfo->stBpc.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stDstStatus.dmafd, pstTofInfo->stDstStatus.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stDstIR.dmafd, pstTofInfo->stDstIR.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stDstData.dmafd, pstTofInfo->stDstData.u64VirAddr);
    CVE_PMZ_FREE(pstTofInfo->stDstHist.dmafd, pstTofInfo->stDstHist.u64VirAddr);
}

static AML_S32 SAMPLE_CVE_TofInit(SAMPLE_CVE_TOF_INFO_T *pstTofInfo, CVE_RAW_MODE_E enRawMode,
                                  AML_U32 u32Width, AML_U32 u32Height)
{
    AML_S32 s32Ret = AML_SUCCESS;
    AML_U32 u32Size;

    memset(&pstTofInfo->stSrcRaw, 0, sizeof(CVE_SRC_RAW_T));
    memset(&pstTofInfo->stSrcFpn, 0, sizeof(CVE_SRC_RAW_T));
    memset(&pstTofInfo->stSrcCoef, 0, sizeof(CVE_SRC_MEM_INFO_T));
    memset(&pstTofInfo->stBpc, 0, sizeof(CVE_SRC_MEM_INFO_T));
    memset(&pstTofInfo->stDstStatus, 0, sizeof(CVE_DST_MEM_INFO_T));
    memset(&pstTofInfo->stDstIR, 0, sizeof(CVE_DST_MEM_INFO_T));
    memset(&pstTofInfo->stDstData, 0, sizeof(CVE_DST_MEM_INFO_T));
    memset(&pstTofInfo->stDstHist, 0, sizeof(CVE_DST_MEM_INFO_T));

    s32Ret = SAMPLE_COMM_CVE_CreateRawInfo(&pstTofInfo->stSrcRaw, enRawMode, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Src Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }

    s32Ret = SAMPLE_COMM_CVE_CreateRawInfo(&pstTofInfo->stSrcFpn, enRawMode, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Src Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }

    u32Size = pstTofInfo->stSrcRaw.u32Stride * 8 * u32Height;
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stSrcCoef, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create SRC Coef Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    u32Size = CVE_MAP_NUM * sizeof(AML_U32);
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stBpc, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Bpc Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    u32Size = pstTofInfo->stSrcRaw.u32Stride * 2 * u32Height;
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stDstStatus, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Stat Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    u32Size = pstTofInfo->stSrcRaw.u32Stride * 2 * u32Height;
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stDstIR, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst IR Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    u32Size = pstTofInfo->stSrcRaw.u32Stride * 2 * u32Height;
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stDstData, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Data Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    u32Size = CVE_HIST_NUM * sizeof(AML_U32) * 3;
    s32Ret = SAMPLE_COMM_CVE_CreateMemInfo(&pstTofInfo->stDstHist, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Create Dst Hist Mem failed!\n", s32Ret);
        goto CVE_EXIT;
    }

    if ((u32Width == 640) && (u32Height == 480)) {
        memcpy(pstTofInfo->stTofCtrl.as32PCoef, as32PCoef_0, sizeof(as32PCoef_0));
        memcpy(pstTofInfo->stTofCtrl.as16TCoef1, as16TCoef1_0, sizeof(as16TCoef1_0));
        pstTofInfo->stTofCtrl.u8BadPointNum = 17;
        pstTofInfo->stTofCtrl.s8IntTemp = 38;
        pstTofInfo->stTofCtrl.s8ExtTemp = 32;

    } else if ((u32Width == 320) && (u32Height == 240)) {
        memcpy(pstTofInfo->stTofCtrl.as32PCoef, as32PCoef_1, sizeof(as32PCoef_1));
        memcpy(pstTofInfo->stTofCtrl.as16TCoef1, as16TCoef1_1, sizeof(as16TCoef1_1));
        pstTofInfo->stTofCtrl.u8BadPointNum = 55;
        pstTofInfo->stTofCtrl.s8IntTemp = 36;
        pstTofInfo->stTofCtrl.s8ExtTemp = 24;
    }
    pstTofInfo->stTofCtrl.u16HistXstart = 0;
    pstTofInfo->stTofCtrl.u16HistYstart = 0;
    pstTofInfo->stTofCtrl.u16HistXend = u32Width;
    pstTofInfo->stTofCtrl.u16HistYend = u32Height;
    pstTofInfo->stTofCtrl.bBypass = AML_FALSE;
    pstTofInfo->stTofCtrl.bSpa1En = AML_TRUE;
    pstTofInfo->stTofCtrl.bSpa2En = AML_TRUE;
    pstTofInfo->stTofCtrl.bRawShift = AML_FALSE;

    pstTofInfo->stTofCtrl.u16Q1HighThr = 3700;
    pstTofInfo->stTofCtrl.u16Q23HighThr = 3700;
    pstTofInfo->stTofCtrl.u16IRLowThr = 30;
    pstTofInfo->stTofCtrl.u16IRHighThr = 3700;
    pstTofInfo->stTofCtrl.u16DepthMax = 8000;
    pstTofInfo->stTofCtrl.u16DepthMin = 200;
    pstTofInfo->stTofCtrl.u8SpaNorm = 4;

CVE_EXIT:
    return s32Ret;
}

static AML_S32 SAMPLE_CVE_TofOpenFile(SAMPLE_CVE_TOF_INFO_T *pstTofInfo,
                                      AML_CHAR *pchSrcRawFileName, AML_CHAR *pchSrcFpnFileName,
                                      AML_CHAR *pchSrcCoefFileName, AML_CHAR *pchBpcFileName,
                                      AML_CHAR *pchDstStatFileName, AML_CHAR *pchDstIRFileName,
                                      AML_CHAR *pchDstDataFileName, AML_CHAR *pchDstHistFileName)
{
    AML_S32 s32Ret = AML_SUCCESS;

    CVE_OPEN_FILE(pstTofInfo->pFpSrcRaw, pchSrcRawFileName, "r+");
    CVE_OPEN_FILE(pstTofInfo->pFpSrcFpn, pchSrcFpnFileName, "r+");
    CVE_OPEN_FILE(pstTofInfo->pFpSrcCoef, pchSrcCoefFileName, "r+");
    CVE_OPEN_FILE(pstTofInfo->pFpBpc, pchBpcFileName, "r+");
    CVE_OPEN_FILE(pstTofInfo->pFpDstStatus, pchDstStatFileName, "w");
    CVE_OPEN_FILE(pstTofInfo->pFpDstIR, pchDstIRFileName, "w");
    CVE_OPEN_FILE(pstTofInfo->pFpDstData, pchDstDataFileName, "w");
    CVE_OPEN_FILE(pstTofInfo->pFpDstHist, pchDstHistFileName, "w");

    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Raw(&pstTofInfo->stSrcRaw, pstTofInfo->pFpSrcRaw);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src RAW Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Raw(&pstTofInfo->stSrcFpn, pstTofInfo->pFpSrcFpn);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src Fpn Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Mem(&pstTofInfo->stSrcCoef, pstTofInfo->pFpSrcCoef);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src Coef Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }
    s32Ret = SAMPLE_COMM_CVE_ReadFile_On_Mem(&pstTofInfo->stBpc, pstTofInfo->pFpBpc);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Read Src Coef Image failed!\n", s32Ret);
        goto CVE_EXIT;
    }

CVE_EXIT:
    return s32Ret;
}

static AML_S32 SAMPLE_CVE_TofProc(SAMPLE_CVE_TOF_INFO_T *pstTofInfo)
{
    AML_BOOL_E bInstant = AML_FALSE;
    AML_BOOL_E bFinish = AML_FALSE;
    CVE_HANDLE cveHandle;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret =
        CVE_TOF(&cveHandle, &pstTofInfo->stSrcRaw, &pstTofInfo->stSrcFpn, &pstTofInfo->stSrcCoef,
                &pstTofInfo->stBpc, &pstTofInfo->stDstStatus, &pstTofInfo->stDstIR,
                &pstTofInfo->stDstData, &pstTofInfo->stDstHist, &pstTofInfo->stTofCtrl, bInstant);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE Tof Proc error\n");
        return s32Ret;
    }
    s32Ret = CVE_Query(cveHandle, &bFinish, AML_TRUE);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("CVE Tof Query error\n");
        return s32Ret;
    }

    return s32Ret;
}

static AML_S32 SAMPLE_CVE_TofCloseFile(SAMPLE_CVE_TOF_INFO_T *pstTofInfo)
{
    AML_S32 s32Ret = 0;

    s32Ret = SAMPLE_COMM_CVE_WriteFile_From_Mem(&pstTofInfo->stDstStatus, pstTofInfo->pFpDstStatus);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Status Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile_From_Mem(&pstTofInfo->stDstIR, pstTofInfo->pFpDstIR);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Ir Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile_From_Mem(&pstTofInfo->stDstData, pstTofInfo->pFpDstData);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Data Image failed!\n", s32Ret);
    }
    s32Ret = SAMPLE_COMM_CVE_WriteFile_From_Mem(&pstTofInfo->stDstHist, pstTofInfo->pFpDstHist);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] Write Dst Data Image failed!\n", s32Ret);
    }

    CVE_CLOSE_FILE(pstTofInfo->pFpSrcRaw);
    CVE_CLOSE_FILE(pstTofInfo->pFpSrcFpn);
    CVE_CLOSE_FILE(pstTofInfo->pFpSrcCoef);
    CVE_CLOSE_FILE(pstTofInfo->pFpBpc);
    CVE_CLOSE_FILE(pstTofInfo->pFpDstStatus);
    CVE_CLOSE_FILE(pstTofInfo->pFpDstIR);
    CVE_CLOSE_FILE(pstTofInfo->pFpDstData);
    CVE_CLOSE_FILE(pstTofInfo->pFpDstHist);

    return s32Ret;
}

AML_S32 SAMPLE_CVE_TofCase(AML_U32 u32CaseIndex)
{
    AML_U32 u32Width = 320;
    AML_U32 u32Height = 240;
    AML_S32 s32Ret;
    AML_S32 i;
    CVE_RAW_MODE_E enSrcRawMode;
    CVE_TOF_CTRL_T *pstTofCtrl = &stTofInfo.stTofCtrl;
    AML_CHAR *pFpSrcFpnName = "/data/cve/FPN_package.data";
    AML_CHAR *pFpSrcCoefName = "/data/cve/coef_package_64bit.data";
    AML_CHAR *pFpSrcBpcName = "/data/cve/bad_pixel_lut_32bit.data";
    AML_CHAR pFpSrcRawName[64] = {0};
    AML_CHAR pFpDstStatusName[64] = {0};
    AML_CHAR pFpDstIrName[64] = {0};
    AML_CHAR pFpDstDataName[64] = {0};
    AML_CHAR pFpDstHistName[64] = {0};

    switch (u32CaseIndex) {
    case 0:
        TEST_PRT("[INFO] Tof CASE 0: Tof Raw mode Raw6, Fpn mode bypass\n");
        enSrcRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_BYPASS;
        break;
    case 1:
        TEST_PRT("[INFO] Tof CASE 1: Tof Raw mode Raw7, Fpn mode bypass\n");
        enSrcRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_BYPASS;
        break;
    case 2:
        TEST_PRT("[INFO] Tof CASE 2: Tof Raw mode Raw8, Fpn mode bypass\n");
        enSrcRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_BYPASS;
        break;
    case 3:
        TEST_PRT("[INFO] Tof CASE 3: Tof Raw mode Raw10, Fpn mode bypass\n");
        enSrcRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_BYPASS;
        break;
    case 4:
        TEST_PRT("[INFO] Tof CASE 4: Tof Raw mode Raw12, Fpn mode bypass\n");
        enSrcRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_BYPASS;
        break;
    case 5:
        TEST_PRT("[INFO] Tof CASE 5: Tof Raw mode Raw6, Fpn mode fpn.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FPN;
        break;
    case 6:
        TEST_PRT("[INFO] Tof CASE 6: Tof Raw mode Raw7, Fpn mode fpn.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FPN;
        break;
    case 7:
        TEST_PRT("[INFO] Tof CASE 7: Tof Raw mode Raw8, Fpn mode fpn.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FPN;
        break;
    case 8:
        TEST_PRT("[INFO] Tof CASE 8: Tof Raw mode Raw10, Fpn mode fpn.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FPN;
        break;
    case 9:
        TEST_PRT("[INFO] Tof CASE 9: Tof Raw mode Raw12, Fpn mode fpn.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FPN;
        break;
    case 10:
        TEST_PRT("[INFO] Tof CASE 10: Tof Raw mode Raw6, Fpn mode fd.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW6;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FD;
        break;
    case 11:
        TEST_PRT("[INFO] Tof CASE 11: Tof Raw mode Raw7, Fpn mode fd.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW7;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FD;
        break;
    case 12:
        TEST_PRT("[INFO] Tof CASE 12: Tof Raw mode Raw8, Fpn mode fd.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW8;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FD;
        break;
    case 13:
        TEST_PRT("[INFO] Tof CASE 13: Tof Raw mode Raw10, Fpn mode fd.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW10;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FD;
        break;
    case 14:
        TEST_PRT("[INFO] Tof CASE 14: Tof Raw mode Raw12, Fpn mode fd.\n");
        enSrcRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enRawMode = CVE_RAW_MODE_RAW12;
        pstTofCtrl->enFpnMode = CVE_TOF_FPN_MODE_FD;
        break;
    default:
        printf("the thresh case index is invaild! valid index:\n");
        SAMPLE_CVE_TofCaseList();
        return AML_FAILURE;
    }

    s32Ret = SAMPLE_CVE_TofInit(&stTofInfo, enSrcRawMode, u32Width, u32Height);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("[ERROR][%x] SAMPLE_CVE_TofInit failed!\n", s32Ret);
        return s32Ret;
    }

    i = 0;
    for (i = 0; i < 12; i++) {
        memset(pFpSrcRawName, 0, 64);
        memset(pFpDstStatusName, 0, 64);
        memset(pFpDstIrName, 0, 64);
        memset(pFpDstDataName, 0, 64);
        memset(pFpDstHistName, 0, 64);
        sprintf(pFpSrcRawName, "/data/cve/raw_package_%d.data", i);
        sprintf(pFpDstStatusName, "/mnt/tof/qvga/dst/raw%d_fpn%d_dst0_status_%d.data",
                pstTofCtrl->enRawMode, pstTofCtrl->enFpnMode, i);
        sprintf(pFpDstIrName, "/mnt/tof/qvga/dst/raw%d_fpn%d_dst1_ir_%d.data",
                pstTofCtrl->enRawMode, pstTofCtrl->enFpnMode, i);
        sprintf(pFpDstDataName, "/mnt/tof/qvga/dst/raw%d_fpn%d_dst2_data_%d.data",
                pstTofCtrl->enRawMode, pstTofCtrl->enFpnMode, i);
        sprintf(pFpDstHistName, "/mnt/tof/qvga/dst/raw%d_fpn%d_dst3_hist_%d.data",
                pstTofCtrl->enRawMode, pstTofCtrl->enFpnMode, i);
        printf("src raw file name   :%s\n", pFpSrcRawName);
        printf("src fpn file name   :%s\n", pFpSrcFpnName);
        printf("src Coef file name  :%s\n", pFpSrcCoefName);
        printf("src Bpc file name   :%s\n", pFpSrcBpcName);
        printf("dst Status file name:%s\n", pFpDstStatusName);
        printf("dst Ir file name    :%s\n", pFpDstIrName);
        printf("dst Data file name  :%s\n", pFpDstDataName);
        printf("dst Hist file name  :%s\n", pFpDstHistName);

        s32Ret = SAMPLE_CVE_TofOpenFile(&stTofInfo, pFpSrcRawName, pFpSrcFpnName, pFpSrcCoefName,
                                        pFpSrcBpcName, pFpDstStatusName, pFpDstIrName,
                                        pFpDstDataName, pFpDstHistName);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("[ERROR][%x] SAMPLE_CVE_TofOpenFile failed!\n", s32Ret);
            return s32Ret;
        }

        s32Ret = SAMPLE_CVE_TofProc(&stTofInfo);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("[ERROR][%x] SAMPLE_CVE_TofProc failed!\n", s32Ret);
        }

        s32Ret = SAMPLE_CVE_TofCloseFile(&stTofInfo);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("[ERROR][%x] SAMPLE_CVE_TofCloseFile failed!\n", s32Ret);
        }
    }
    SAMPLE_CVE_TofUninit(&stTofInfo);
    memset(&stTofInfo, 0, sizeof(SAMPLE_CVE_TOF_INFO_T));

    return s32Ret;
}
