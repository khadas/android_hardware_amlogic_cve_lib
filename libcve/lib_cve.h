/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#ifndef __CVE_H__
#define __CVE_H__

#include "aml_comm_cve.h"
#include "aml_common.h"
#include "aml_cve.h"
#include "aml_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct {
    CVE_HANDLE CveHandle;
    CVE_SRC_IMAGE_T *pstSrcImage;
    CVE_SRC_IMAGE_T *pstFactor;
    CVE_DST_IMAGE_T *pstFg;
    CVE_DST_IMAGE_T *pstBg;
    CVE_MEM_INFO_T *pstModel;
    CVE_GMM_CTRL_T *pstGmmCtrl;
    AML_BOOL_E bInstant;
} CVE_GMM_T;

typedef struct {
    CVE_HANDLE CveHandle;
    CVE_SRC_IMAGE_T *pstSrc;
    CVE_DST_IMAGE_T *pstDst;
    CVE_DST_MEM_INFO_T *pstBlob;
    CVE_CCL_CTRL_T *pstCclCtrl;
    AML_BOOL_E bInstant;
} CVE_CCL_T;

AML_S32 CVE_DMA(CVE_HANDLE *pCveHandle, CVE_DATA_T *pstSrc, CVE_DST_DATA_T *pstDst,
                CVE_DMA_CTRL_T *pstDmaCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_LumaStatArray(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                          CVE_DST_MEM_INFO_T *pstDst, const CVE_RECT_U16_T astCveLumaRect[],
                          CVE_LUMA_STAT_ARRAY_CTRL_T *pstLumaStatArrayCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Filter(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_FILTER_CTRL_T *pstFltCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_CSC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_CSC_CTRL_T *pstCscCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_FilterAndCSC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                         CVE_FILTER_AND_CSC_CTRL_T *pstFltCscCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Dilate(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_DILATE_CTRL_T *pstDilateCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Erode(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                  CVE_ERODE_CTRL_T *pstErodeCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Thresh(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_THRESH_CTRL_T *pstThrCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Sobel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstH,
                  CVE_DST_IMAGE_T *pstDstV, CVE_SOBEL_CTRL_T *pstSobelCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_MagAndAng(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstMag,
                      CVE_DST_IMAGE_T *pstDstAng, CVE_MAG_AND_ANG_CTRL_T *pstMagAndAngCtrl,
                      AML_BOOL_E bInstant);
AML_S32 CVE_Integ(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                  CVE_INTEG_CTRL_T *pstIntegCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Hist(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_MEM_INFO_T *pstDst,
                 AML_BOOL_E bInstant);
AML_S32 CVE_Query(CVE_HANDLE cveHandle, AML_BOOL_E *pbFinish, AML_BOOL_E bBlock);
AML_S32 CVE_NCC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_MEM_INFO_T *pstDst, CVE_NCC_CTRL_T *pstNccCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_NormGrad(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstH,
                     CVE_DST_IMAGE_T *pstDstV, CVE_DST_IMAGE_T *pstDstHV,
                     CVE_NORM_GRAD_CTRL_T *pstNormGradCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Thresh_S16(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                       CVE_THRESH_S16_CTRL_T *pstThrS16Ctrl, AML_BOOL_E bInstant);
AML_S32 CVE_Thresh_U16(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                       CVE_THRESH_U16_CTRL_T *pstThrU16Ctrl, AML_BOOL_E bInstant);
AML_S32 CVE_OrdStatFilter(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                          CVE_ORD_STAT_FILTER_CTRL_T *pstOrdStatFltCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_16BitTo8Bit(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                        CVE_16BIT_TO_8BIT_CTRL_T *pst16BitTo8BitCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_MatchBgModel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                         CVE_SRC_IMAGE_T *pstPreImg, CVE_MEM_INFO_T *pstBgModel,
                         CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg,
                         CVE_DST_IMAGE_T *pstCurDiffBg, CVE_DST_IMAGE_T *pstFrmDiff,
                         CVE_DST_MEM_INFO_T *pstStatData,
                         CVE_MATCH_BG_MODEL_CTRL_T *pstMatchBgModelCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_UpdateBgModel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                          CVE_MEM_INFO_T *pstBgModel1, CVE_MEM_INFO_T *pstBgModel2,
                          CVE_DST_MEM_INFO_T *pstStatData,
                          CVE_UPDATE_BG_MODEL_CTRL_T *pstUpdateBgModelCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_GradFg(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstFg, CVE_SRC_IMAGE_T *pstCurGrad,
                   CVE_SRC_IMAGE_T *pstBgGrad, CVE_DST_IMAGE_T *pstGradFg,
                   CVE_GRAD_FG_CTRL_T *pstGradFgCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_LBP(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_LBP_CTRL_T *pstLbpCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_EqualizeHist(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                         CVE_EQUALIZE_HIST_CTRL_T *pstEqualizeHistCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_CCL(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_DST_MEM_INFO_T *pstBlob, CVE_CCL_CTRL_T *pstCclCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_GMM(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_SRC_IMAGE_T *pstFactor,
                CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg, CVE_MEM_INFO_T *pstModel,
                CVE_GMM_CTRL_T *pstGmmCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_CannyHysEdge(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstEdge,
                         CVE_DST_MEM_INFO_T *pstStack,
                         CVE_CANNY_HYS_EDGE_CTRL_T *pstCannyHysEdgeCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_CannyEdge(CVE_IMAGE_T *pstEdge, CVE_MEM_INFO_T *pstStack,
                      CVE_CANNY_EDGE_CTRL_T *pstCannyEdgeCtrl);
AML_S32 CVE_STCandiCorner(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                          CVE_DST_IMAGE_T *pstLabel, CVE_DST_IMAGE_T *pstCandiCorner,
                          CVE_DST_MEM_INFO_T *pstCandiCornerPoint,
                          CVE_ST_CANDI_CORNER_CTRL_T *pstStCandiCornerCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_STCorner(CVE_SRC_MEM_INFO_T *pstCandiCornerPoint, CVE_DST_MEM_INFO_T *pstCornerPoint,
                     CVE_ST_CORNER_CTRL_T *pstStCornerCtrl);
AML_S32 CVE_SAD(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstSad, CVE_DST_IMAGE_T *pstThr, CVE_SAD_CTRL_T *pstSadCtrl,
                AML_BOOL_E bInstant);
AML_S32 CVE_BuildLKOpticalFlowPyr(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrcPrevPyr,
                                  CVE_DST_IMAGE_T astDstPyr[],
                                  CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T *pstBuildLkOptiFlowPyrCtrl,
                                  AML_BOOL_E bInstant);
AML_S32 CVE_LKOpticalFlowPyr(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T astSrcPrevPyr[],
                             CVE_SRC_IMAGE_T astSrcNextPyr[], CVE_SRC_MEM_INFO_T *pstPrevPts,
                             CVE_MEM_INFO_T *pstNextPts, CVE_DST_MEM_INFO_T *pstStatus,
                             CVE_DST_MEM_INFO_T *pstErr,
                             CVE_LK_OPTICAL_FLOW_PYR_CTRL_T *pstLkOptiFlowPyrCtrl,
                             AML_BOOL_E bInstant);
AML_S32 CVE_Map(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_SRC_MEM_INFO_T *pstMap,
                CVE_DST_IMAGE_T *pstDst, CVE_MAP_CTRL_T *pstMapCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_And(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant);
AML_S32 CVE_Sub(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, CVE_SUB_CTRL_T *pstSubCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_Or(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
               CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant);
AML_S32 CVE_Xor(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant);
AML_S32 CVE_Add(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, CVE_ADD_CTRL_T *pstAddCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_TOF(CVE_HANDLE *pCveHandle, CVE_SRC_RAW_T *pstSrcRaw, CVE_SRC_RAW_T *pstSrcFpn,
                CVE_SRC_MEM_INFO_T *pstSrcCoef, CVE_SRC_MEM_INFO_T *pstBpc,
                CVE_DST_MEM_INFO_T *pstDtsStatus, CVE_DST_MEM_INFO_T *pstDtsIR,
                CVE_DST_MEM_INFO_T *pstDtsData, CVE_DST_MEM_INFO_T *pstDstHist,
                CVE_TOF_CTRL_T *pstTofCtrl, AML_BOOL_E bInstant);
AML_S32 CVE_GmmCcl(CVE_GMM_T *pstGmm, CVE_CCL_T *pstCcl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __CVE_H__ */
