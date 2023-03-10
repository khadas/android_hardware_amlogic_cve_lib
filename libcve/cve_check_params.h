/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#ifndef __CVE_CHECK_H__
#define __CVE_CHECK_H__

#include "aml_comm_cve.h"
#include "aml_common.h"
#include "aml_cve.h"
#include "aml_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

AML_S32 cve_check_dma_param_user(CVE_HANDLE *pCveHandle, CVE_DATA_T *pstSrc, CVE_DST_DATA_T *pstDst,
                                 CVE_DMA_CTRL_T *pstDmaCtrl);
AML_S32
cve_check_luamStat_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                              CVE_DST_MEM_INFO_T *pstDst, const CVE_RECT_U16_T *pstCveLumaRect,
                              CVE_LUMA_STAT_ARRAY_CTRL_T *pstLumaStatArrayCtrl);
AML_S32 cve_check_filter_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_FILTER_CTRL_T *pstFltCtrl);
AML_S32 cve_check_csc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_CSC_CTRL_T *pstCscCtrl);
AML_S32 cve_check_filter_and_csc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                            CVE_DST_IMAGE_T *pstDst,
                                            CVE_FILTER_AND_CSC_CTRL_T *pstFltCscCtrl);
AML_S32 cve_check_sobel_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDstH, CVE_DST_IMAGE_T *pstDstV,
                                   CVE_SOBEL_CTRL_T *pstSobelCtrl);
AML_S32 cve_check_mag_and_ang_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                         CVE_DST_IMAGE_T *pstDstMag, CVE_DST_IMAGE_T *pstDstAng,
                                         CVE_MAG_AND_ANG_CTRL_T *pstMagAndAngCtrl);
AML_S32 cve_check_match_bg_model_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                                            CVE_SRC_IMAGE_T *pstPreImg, CVE_MEM_INFO_T *pstBgModel,
                                            CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg,
                                            CVE_DST_IMAGE_T *pstCurDiffBg,
                                            CVE_DST_IMAGE_T *pstFrmDiff,
                                            CVE_DST_MEM_INFO_T *pstStatData,
                                            CVE_MATCH_BG_MODEL_CTRL_T *pstMatchBgModelCtrl);
AML_S32 cve_check_update_bg_model_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                                             CVE_MEM_INFO_T *pstBgModel1,
                                             CVE_MEM_INFO_T *pstBgModel2,
                                             CVE_DST_MEM_INFO_T *pstStatData,
                                             CVE_UPDATE_BG_MODEL_CTRL_T *pstUpdateBgModelCtrl);
AML_S32 cve_check_dilate_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_DILATE_CTRL_T *pstDilateCtrl);
AML_S32 cve_check_erode_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDst, CVE_ERODE_CTRL_T *pstErodeCtrl);
AML_S32 cve_check_thresh_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_THRESH_CTRL_T *pstThrCtrl);
AML_S32 cve_check_sub_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst,
                                 CVE_SUB_CTRL_T *pstSubCtrl);
AML_S32 cve_check_or_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst);
AML_S32 cve_check_and_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst);
AML_S32 cve_check_xor_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst);
AML_S32 cve_check_add_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst,
                                 CVE_ADD_CTRL_T *pstAddCtrl);
AML_S32 cve_check_integ_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDst, CVE_INTEG_CTRL_T *pstIntegCtrl);
AML_S32 cve_check_hist_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                  CVE_DST_MEM_INFO_T *pstDst);
AML_S32 cve_check_thresh_s16_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                        CVE_DST_IMAGE_T *pstDst,
                                        CVE_THRESH_S16_CTRL_T *pstThrS16Ctrl);
AML_S32 cve_check_thresh_u16_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                        CVE_DST_IMAGE_T *pstDst,
                                        CVE_THRESH_U16_CTRL_T *pstThrU16Ctrl);
AML_S32 cve_check_16bit_to_8bit_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                           CVE_DST_IMAGE_T *pstDst,
                                           CVE_16BIT_TO_8BIT_CTRL_T *pst16BitTo8BitCtrl);
AML_S32 cve_check_ord_stat_filter_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                             CVE_DST_IMAGE_T *pstDst,
                                             CVE_ORD_STAT_FILTER_CTRL_T *pstOrdStatFltCtrl);
AML_S32 cve_check_map_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_SRC_MEM_INFO_T *pstMap, CVE_DST_IMAGE_T *pstDst,
                                 CVE_MAP_CTRL_T *pstMapCtrl);
AML_S32 cve_check_equalize_hist_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                           CVE_DST_IMAGE_T *pstDst,
                                           CVE_EQUALIZE_HIST_CTRL_T *pstEqualizeHistCtrl);
AML_S32 cve_check_ncc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_MEM_INFO_T *pstDst,
                                 CVE_NCC_CTRL_T *pstNccCtrl);
AML_S32 cve_check_ccl_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_DST_MEM_INFO_T *pstBlob,
                                 CVE_CCL_CTRL_T *pstCclCtrl);
AML_S32 cve_check_gmm_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_SRC_IMAGE_T *pstFactor, CVE_DST_IMAGE_T *pstFg,
                                 CVE_DST_IMAGE_T *pstBg, CVE_MEM_INFO_T *pstModel,
                                 CVE_GMM_CTRL_T *pstGmmCtrl);
AML_S32 cve_check_canny_hys_edge_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                            CVE_DST_IMAGE_T *pstEdge, CVE_DST_MEM_INFO_T *pstStack,
                                            CVE_CANNY_HYS_EDGE_CTRL_T *pstCannyHysEdgeCtrl);
AML_S32
cve_check_canny_edge_param_user(CVE_IMAGE_T *pstEdge, CVE_MEM_INFO_T *pstStack,
                                CVE_CANNY_EDGE_CTRL_T *pstCannyEdgeCtrl);
AML_S32 cve_check_lbp_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_LBP_CTRL_T *pstLbpCtrl);
AML_S32 cve_check_norm_grad_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                       CVE_DST_IMAGE_T *pstDstH, CVE_DST_IMAGE_T *pstDstV,
                                       CVE_DST_IMAGE_T *pstDstHV,
                                       CVE_NORM_GRAD_CTRL_T *pstNormGradCtrl);
AML_S32 cve_check_buildlkoptionalflowpyr_param_user(
    CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrcPrevPyr,
    CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T *pstBuildLkOptiFlowPyrCtrl);
AML_S32
cve_check_lk_optical_flow_pyr_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_MEM_INFO_T *pstPrevPts,
                                         CVE_MEM_INFO_T *pstNextPts, CVE_DST_MEM_INFO_T *pstStatus,
                                         CVE_DST_MEM_INFO_T *pstErr,
                                         CVE_LK_OPTICAL_FLOW_PYR_CTRL_T *pstLkOptiFlowPyrCtrl);
AML_S32 cve_check_st_candi_corner_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                             CVE_DST_IMAGE_T *pstLabel,
                                             CVE_DST_IMAGE_T *pstCandiCorner,
                                             CVE_DST_MEM_INFO_T *pstCorner,
                                             CVE_ST_CANDI_CORNER_CTRL_T *pstStCandiCornerCtrl);
AML_S32 cve_check_st_corner_param_user(CVE_SRC_MEM_INFO_T *pstCandiCornerPoint,
                                       CVE_DST_MEM_INFO_T *pstCornerPoint,
                                       CVE_ST_CORNER_CTRL_T *pstStCornerCtrl);
AML_S32
cve_check_sad_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                         CVE_DST_IMAGE_T *pstSad, CVE_DST_IMAGE_T *pstThr,
                         CVE_SAD_CTRL_T *pstSadCtrl);
AML_S32 cve_check_grad_fg_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstFg,
                                     CVE_SRC_IMAGE_T *pstCurGrad, CVE_SRC_IMAGE_T *pstBgGrad,
                                     CVE_DST_IMAGE_T *pstGradFg, CVE_GRAD_FG_CTRL_T *pstGradFgCtrl);
AML_S32
cve_check_tof_user(CVE_HANDLE *pCveHandle, CVE_SRC_RAW_T *pstSrcRaw, CVE_SRC_RAW_T *pstSrcFpn,
                   CVE_SRC_MEM_INFO_T *pstSrcCoef, CVE_SRC_MEM_INFO_T *pstBpc,
                   CVE_DST_MEM_INFO_T *pstDtsStatus, CVE_DST_MEM_INFO_T *pstDtsIR,
                   CVE_DST_MEM_INFO_T *pstDtsData, CVE_DST_MEM_INFO_T *pstDstHist,
                   CVE_TOF_CTRL_T *pstTofCtrl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __CVE_H__ */
