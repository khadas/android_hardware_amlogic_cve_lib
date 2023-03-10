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

extern void SAMPLE_CVE_DmaCaseList(void);
#if 0
extern void SAMPLE_CVE_LumaStatCaseList(void);
extern void SAMPLE_CVE_CscCaseList(void);
extern void SAMPLE_CVE_FilterCaseList(void);
extern void SAMPLE_CVE_FilterCscCaseList(void);
extern void SAMPLE_CVE_SobelCaseList(void);
extern void SAMPLE_CVE_MagAngCaseList(void);
extern void SAMPLE_CVE_MatchBgModelCaseList(void);
extern void SAMPLE_CVE_ErodeDilateCaseList(void);
extern void SAMPLE_CVE_ThreshCaseList(void);
extern void SAMPLE_CVE_AluCaseList(void);
extern void SAMPLE_CVE_IntegCaseList(void);
extern void SAMPLE_CVE_HistCaseList(void);
extern void SAMPLE_CVE_ThreshS16CaseList(void);
extern void SAMPLE_CVE_ThreshU16CaseList(void);
extern void SAMPLE_CVE_16BitTo8BitCaseList(void);
extern void SAMPLE_CVE_OrdStatFilterCaseList(void);
extern void SAMPLE_CVE_MapCaseList(void);
extern void SAMPLE_CVE_EqualizeHistCaseList(void);
extern void SAMPLE_CVE_NccCaseList(void);
extern void SAMPLE_CVE_CclCaseList(void);
#endif
extern void SAMPLE_CVE_GmmCaseList(void);
#if 0
extern void SAMPLE_CVE_CannyHysEdgeCaseList(void);
extern void SAMPLE_CVE_LbpCaseList(void);
extern void SAMPLE_CVE_NormGradCaseList(void);
extern void SAMPLE_CVE_BuildLKOpticalFlowPyrCaseList(void);
extern void SAMPLE_CVE_LKOpticalFlowPyrCaseList(void);
extern void SAMPLE_CVE_StCaseList(void);
extern void SAMPLE_CVE_SadCaseList(void);
extern void SAMPLE_CVE_GradFgCaseList(void);
extern void SAMPLE_CVE_UpdateBgModelCaseList(void);
#endif
extern void SAMPLE_CVE_TofCaseList(void);
extern AML_S32 SAMPLE_CVE_DmaCase(AML_U32 u32CaseIndex);
#if 0
extern AML_S32 SAMPLE_CVE_LumaStatCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_CscCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_FilterCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_FilterCscCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_SobelCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_MagAngCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_MatchBgModelCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_ErodeDilateCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_ThreshCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_AluCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_IntegCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_HistCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_ThreshS16Case(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_ThreshU16Case(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_16BitTo8BitCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_OrdStatFilterCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_MapCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_EqualizeHistCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_NccCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_CclCase(AML_U32 u32CaseIndex);
#endif
extern AML_S32 SAMPLE_CVE_GmmCase(AML_U32 u32CaseIndex);
#if 0
extern AML_S32 SAMPLE_CVE_CannyHysEdgeCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_LbpCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_NormGradCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_BuildLKOpticalFlowPyrCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_LKOpticalFlowPyrCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_StCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_SadCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_GradFgCase(AML_U32 u32CaseIndex);
extern AML_S32 SAMPLE_CVE_UpdateBgModelCase(AML_U32 u32CaseIndex);
#endif
extern AML_S32 SAMPLE_CVE_TofCase(AML_U32 u32CaseIndex);

AML_U32 SAMPLE_CVE_TestOpIndex(void)
{
    AML_U32 getindex = 0;

    printf("\t  0 -- DMA:\n");
#if 0
    printf("\t  1 -- LUMA STAT:\n");
    printf("\t  2 -- FILTER:\n");
    printf("\t  3 -- CSC:\n");
    printf("\t  4 -- FILTER AND CSC:\n");
    printf("\t  5 -- SOBEL:\n");
    printf("\t  6 -- MAG AND ANG:\n");
    printf("\t  7 -- MATHC BG MODEL:\n");
    printf("\t  8 -- ERODE AND DILATE:\n");
    printf("\t  9 -- THRESH:\n");
    printf("\t  10 -- ALU:\n");
    printf("\t  11 -- INTEG:\n");
    printf("\t  12 -- HIST:\n");
    printf("\t  13 -- THRESH S16:\n");
    printf("\t  14 -- THRESH U16:\n");
    printf("\t  15 -- 16Bit TO 8Bit:\n");
    printf("\t  16 -- ORD STAT FILTER:\n");
    printf("\t  17 -- MAP:\n");
    printf("\t  18 -- EQUALIZE HIST:\n");
    printf("\t  19 -- NCC:\n");
    printf("\t  20 -- CCL:\n");
#endif
    printf("\t  21 -- GMM:\n");
#if 0
    printf("\t  22 -- CANNY EDGE:\n");
    printf("\t  23 -- LBP:\n");
    printf("\t  24 -- NORM GRAD:\n");
    printf("\t  25 -- BUILD LK OPTICAL FLOW PYR:\n");
    printf("\t  26 -- LK OPTICAL FLOW PYR:\n");
    printf("\t  27 -- ST Candi Corner:\n");
    printf("\t  28 -- SAD:\n");
    printf("\t  29 -- GRADFG:\n");
    printf("\t  30 -- UPDATE BG MODEL:\n");
#endif
    printf("\t  31 -- TOF:\n");
    printf("please input test op index:");
    getindex = SAMPLE_COMM_CVE_Input_Index();

    return getindex;
}

AML_S32 SAMPLE_CVE_TestCaseIndex(AML_U32 u32OpIndex, AML_BOOL_E help)
{
    AML_U32 u32CaseIndex = 0xFF;
    switch (u32OpIndex) {
    case 0:
        SAMPLE_CVE_DmaCaseList();
        break;
#if 0
    case 1:
        SAMPLE_CVE_LumaStatCaseList();
        break;
    case 2:
        SAMPLE_CVE_FilterCaseList();
        break;
    case 3:
        SAMPLE_CVE_CscCaseList();
        break;
    case 4:
        SAMPLE_CVE_FilterCscCaseList();
        break;
    case 5:
        SAMPLE_CVE_SobelCaseList();
        break;
    case 6:
        SAMPLE_CVE_MagAngCaseList();
        break;
    case 7:
        SAMPLE_CVE_MatchBgModelCaseList();
        break;
    case 8:
        SAMPLE_CVE_ErodeDilateCaseList();
        break;
    case 9:
        SAMPLE_CVE_ThreshCaseList();
        break;
    case 10:
        SAMPLE_CVE_AluCaseList();
        break;
    case 11:
        SAMPLE_CVE_IntegCaseList();
        break;
    case 12:
        SAMPLE_CVE_HistCaseList();
        break;
    case 13:
        SAMPLE_CVE_ThreshS16CaseList();
        break;
    case 14:
        SAMPLE_CVE_ThreshU16CaseList();
        break;
    case 15:
        SAMPLE_CVE_16BitTo8BitCaseList();
        break;
    case 16:
        SAMPLE_CVE_OrdStatFilterCaseList();
        break;
    case 17:
        SAMPLE_CVE_MapCaseList();
        break;
    case 18:
        SAMPLE_CVE_EqualizeHistCaseList();
        break;
    case 19:
        SAMPLE_CVE_NccCaseList();
        break;
    case 20:
        SAMPLE_CVE_CclCaseList();
        break;
#endif
    case 21:
        SAMPLE_CVE_GmmCaseList();
        break;
#if 0
    case 22:
        SAMPLE_CVE_CannyHysEdgeCaseList();
        break;
    case 23:
        SAMPLE_CVE_LbpCaseList();
        break;
    case 24:
        SAMPLE_CVE_NormGradCaseList();
        break;
    case 25:
        SAMPLE_CVE_BuildLKOpticalFlowPyrCaseList();
        break;
    case 26:
        SAMPLE_CVE_LKOpticalFlowPyrCaseList();
        break;
    case 27:
        SAMPLE_CVE_StCaseList();
        break;
    case 28:
        SAMPLE_CVE_SadCaseList();
        break;
    case 29:
        SAMPLE_CVE_GradFgCaseList();
        break;
    case 30:
        SAMPLE_CVE_UpdateBgModelCaseList();
        break;
#endif
    case 31:
        SAMPLE_CVE_TofCaseList();
        break;
    default:
        printf("not support case:%d\n", u32OpIndex);
    }
    if (help == AML_FALSE) {
        printf("please input test case index:");
        u32CaseIndex = SAMPLE_COMM_CVE_Input_Index();
    }
    return u32CaseIndex;
}

int main(int argc, char **argv)
{
    AML_S32 s32Ret = AML_SUCCESS;
    AML_U32 u32OpIndex;
    AML_U32 u32CaseIndex;

    if (argc > 1) {
        if (!strncmp(argv[1], "-h", 2)) {
            printf("show test case:\n");
            u32OpIndex = SAMPLE_CVE_TestOpIndex();
            u32CaseIndex = SAMPLE_CVE_TestCaseIndex(u32OpIndex, AML_TRUE);
            return AML_SUCCESS;
        }
    }

    u32OpIndex = SAMPLE_CVE_TestOpIndex();
    u32CaseIndex = SAMPLE_CVE_TestCaseIndex(u32OpIndex, AML_FALSE);
    SAMPLE_COMM_CVE_CheckCveMpiInit();
    TEST_PRT("[INFO] CVE OP:[%d] OP CASE[%d]\n", u32OpIndex, u32CaseIndex);
    switch (u32OpIndex) {
    case 0:
        s32Ret = SAMPLE_CVE_DmaCase(u32CaseIndex);
        break;
#if 0
    case 1:
        s32Ret = SAMPLE_CVE_LumaStatCase(u32CaseIndex);
        break;
    case 2:
        s32Ret = SAMPLE_CVE_FilterCase(u32CaseIndex);
        break;
    case 3:
        s32Ret = SAMPLE_CVE_CscCase(u32CaseIndex);
        break;
    case 4:
        s32Ret = SAMPLE_CVE_FilterCscCase(u32CaseIndex);
        break;
    case 5:
        s32Ret = SAMPLE_CVE_SobelCase(u32CaseIndex);
        break;
    case 6:
        s32Ret = SAMPLE_CVE_MagAngCase(u32CaseIndex);
        break;
    case 7:
        s32Ret = SAMPLE_CVE_MatchBgModelCase(u32CaseIndex);
        break;
    case 8:
        s32Ret = SAMPLE_CVE_ErodeDilateCase(u32CaseIndex);
        break;
    case 9:
        s32Ret = SAMPLE_CVE_ThreshCase(u32CaseIndex);
        break;
    case 10:
        s32Ret = SAMPLE_CVE_AluCase(u32CaseIndex);
        break;
    case 11:
        s32Ret = SAMPLE_CVE_IntegCase(u32CaseIndex);
        break;
    case 12:
        s32Ret = SAMPLE_CVE_HistCase(u32CaseIndex);
        break;
    case 13:
        s32Ret = SAMPLE_CVE_ThreshS16Case(u32CaseIndex);
        break;
    case 14:
        s32Ret = SAMPLE_CVE_ThreshU16Case(u32CaseIndex);
        break;
    case 15:
        s32Ret = SAMPLE_CVE_16BitTo8BitCase(u32CaseIndex);
        break;
    case 16:
        s32Ret = SAMPLE_CVE_OrdStatFilterCase(u32CaseIndex);
        break;
    case 17:
        s32Ret = SAMPLE_CVE_MapCase(u32CaseIndex);
        break;
    case 18:
        s32Ret = SAMPLE_CVE_EqualizeHistCase(u32CaseIndex);
        break;
    case 19:
        s32Ret = SAMPLE_CVE_NccCase(u32CaseIndex);
        break;
    case 20:
        s32Ret = SAMPLE_CVE_CclCase(u32CaseIndex);
        break;
#endif
    case 21:
        s32Ret = SAMPLE_CVE_GmmCase(u32CaseIndex);
        break;
#if 0
    case 22:
        s32Ret = SAMPLE_CVE_CannyHysEdgeCase(u32CaseIndex);
        break;
    case 23:
        s32Ret = SAMPLE_CVE_LbpCase(u32CaseIndex);
        break;
    case 24:
        s32Ret = SAMPLE_CVE_NormGradCase(u32CaseIndex);
        break;
    case 25:
        s32Ret = SAMPLE_CVE_BuildLKOpticalFlowPyrCase(u32CaseIndex);
        break;
    case 26:
        s32Ret = SAMPLE_CVE_LKOpticalFlowPyrCase(u32CaseIndex);
        break;
    case 27:
        s32Ret = SAMPLE_CVE_StCase(u32CaseIndex);
        break;
    case 28:
        s32Ret = SAMPLE_CVE_SadCase(u32CaseIndex);
        break;
    case 29:
        s32Ret = SAMPLE_CVE_GradFgCase(u32CaseIndex);
        break;
    case 30:
        s32Ret = SAMPLE_CVE_UpdateBgModelCase(u32CaseIndex);
        break;
#endif
    case 31:
        s32Ret = SAMPLE_CVE_TofCase(u32CaseIndex);
        break;
    default:
        printf("the index is invaild!\n");
        return AML_FAILURE;
    }

    if (AML_SUCCESS == s32Ret) {
        printf("program exit normally!\n");
    } else {
        printf("program exit abnormally!\n");
    }

    return s32Ret;
}
