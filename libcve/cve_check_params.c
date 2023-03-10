/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#include "cve_check_params.h"
#include "aml_cve.h"
#include "cve.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

AML_S32 cve_check_dma_param_user(CVE_HANDLE *pCveHandle, CVE_DATA_T *pstSrc, CVE_DST_DATA_T *pstDst,
                                 CVE_DMA_CTRL_T *pstDmaCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc != AML_NULL) && (pstDmaCtrl != AML_NULL)) {
            if (pstDmaCtrl->enMode <= CVE_DMA_MODE_INTERVAL_COPY) {
                if (pstDst == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
            }
        } else {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_luamStat_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                      CVE_DST_MEM_INFO_T *pstDst,
                                      const CVE_RECT_U16_T *pstCveLumaRect,
                                      CVE_LUMA_STAT_ARRAY_CTRL_T *pstLumaStatArrayCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstCveLumaRect == AML_NULL) ||
            (pstLumaStatArrayCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_filter_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_FILTER_CTRL_T *pstFltCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstFltCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_csc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_CSC_CTRL_T *pstCscCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstCscCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_filter_and_csc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                            CVE_DST_IMAGE_T *pstDst,
                                            CVE_FILTER_AND_CSC_CTRL_T *pstFltCscCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstFltCscCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_sobel_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDstH, CVE_DST_IMAGE_T *pstDstV,
                                   CVE_SOBEL_CTRL_T *pstSobelCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc != AML_NULL) && (pstSobelCtrl != AML_NULL)) {
            switch (pstSobelCtrl->enOutCtrl) {
            case CVE_SOBEL_OUT_CTRL_BOTH:
                if ((pstDstH == AML_NULL) || (pstDstV == AML_NULL)) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            case CVE_SOBEL_OUT_CTRL_HOR:
                if (pstDstH == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            case CVE_SOBEL_OUT_CTRL_VER:
                if (pstDstV == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            default:
                CVE_ERR_TRACE("cve sobel params not support, pstSobelCtrl->enOutCtrl = %d\n",
                              pstSobelCtrl->enOutCtrl);
                s32Ret = AML_ERR_CVE_NOT_SURPPORT;
                CVE_ERR_TRACE("cve sobel have Null handle\n");
                break;
            }
        } else {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_mag_and_ang_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                         CVE_DST_IMAGE_T *pstDstMag, CVE_DST_IMAGE_T *pstDstAng,
                                         CVE_MAG_AND_ANG_CTRL_T *pstMagAndAngCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if (pstSrc != AML_NULL) {
            switch (pstMagAndAngCtrl->enOutCtrl) {
            case CVE_MAG_AND_ANG_OUT_CTRL_MAG_AND_ANG:
                if ((pstDstMag == AML_NULL) || (pstDstAng == AML_NULL)) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            case CVE_MAG_AND_ANG_OUT_CTRL_MAG:
                if (pstDstMag == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            case CVE_MAG_AND_ANG_OUT_CTRL_HOG:
                if (pstDstMag == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            default:
                CVE_ERR_TRACE("cve mag and ang params not support, "
                              "pstMagAndAngCtrl->enOutCtrl = %d\n",
                              pstMagAndAngCtrl->enOutCtrl);
                s32Ret = AML_ERR_CVE_NOT_SURPPORT;
                break;
            }
        } else {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_match_bg_model_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                                            CVE_SRC_IMAGE_T *pstPreImg, CVE_MEM_INFO_T *pstBgModel,
                                            CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg,
                                            CVE_DST_IMAGE_T *pstCurDiffBg,
                                            CVE_DST_IMAGE_T *pstFrmDiff,
                                            CVE_DST_MEM_INFO_T *pstStatData,
                                            CVE_MATCH_BG_MODEL_CTRL_T *pstMatchBgModelCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstCurImg == AML_NULL) || (pstPreImg == AML_NULL) || (pstBgModel == AML_NULL) ||
            (pstFg == AML_NULL) || (pstBg == AML_NULL) || (pstCurDiffBg == AML_NULL) ||
            (pstFrmDiff == AML_NULL) || (pstStatData == AML_NULL) ||
            (pstMatchBgModelCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_update_bg_model_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                                             CVE_MEM_INFO_T *pstBgModel1,
                                             CVE_MEM_INFO_T *pstBgModel2,
                                             CVE_DST_MEM_INFO_T *pstStatData,
                                             CVE_UPDATE_BG_MODEL_CTRL_T *pstUpdateBgModelCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstCurImg == AML_NULL) || (pstBgModel1 == AML_NULL) || (pstBgModel2 == AML_NULL) ||
            (pstStatData == AML_NULL) || (pstUpdateBgModelCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_dilate_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_DILATE_CTRL_T *pstDilateCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstDilateCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_erode_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDst, CVE_ERODE_CTRL_T *pstErodeCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstErodeCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_thresh_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                    CVE_DST_IMAGE_T *pstDst, CVE_THRESH_CTRL_T *pstThrCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstThrCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_sub_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst,
                                 CVE_SUB_CTRL_T *pstSubCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL) ||
            (pstSubCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_or_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_and_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_xor_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_add_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_IMAGE_T *pstDst,
                                 CVE_ADD_CTRL_T *pstAddCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL) ||
            (pstAddCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_integ_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                   CVE_DST_IMAGE_T *pstDst, CVE_INTEG_CTRL_T *pstIntegCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstIntegCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_hist_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                  CVE_DST_MEM_INFO_T *pstDst)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_thresh_s16_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                        CVE_DST_IMAGE_T *pstDst,
                                        CVE_THRESH_S16_CTRL_T *pstThrS16Ctrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstThrS16Ctrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_thresh_u16_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                        CVE_DST_IMAGE_T *pstDst,
                                        CVE_THRESH_U16_CTRL_T *pstThrU16Ctrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstThrU16Ctrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_16bit_to_8bit_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                           CVE_DST_IMAGE_T *pstDst,
                                           CVE_16BIT_TO_8BIT_CTRL_T *pst16BitTo8BitCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pst16BitTo8BitCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_ord_stat_filter_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                             CVE_DST_IMAGE_T *pstDst,
                                             CVE_ORD_STAT_FILTER_CTRL_T *pstOrdStatFltCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstOrdStatFltCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_map_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_SRC_MEM_INFO_T *pstMap, CVE_DST_IMAGE_T *pstDst,
                                 CVE_MAP_CTRL_T *pstMapCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstMap == AML_NULL) ||
            (pstMapCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_equalize_hist_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                           CVE_DST_IMAGE_T *pstDst,
                                           CVE_EQUALIZE_HIST_CTRL_T *pstEqualizeHistCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstEqualizeHistCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_ncc_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1,
                                 CVE_SRC_IMAGE_T *pstSrc2, CVE_DST_MEM_INFO_T *pstDst,
                                 CVE_NCC_CTRL_T *pstNccCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstDst == AML_NULL) ||
            (pstNccCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_ccl_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_DST_MEM_INFO_T *pstBlob,
                                 CVE_CCL_CTRL_T *pstCclCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstBlob == AML_NULL) ||
            (pstCclCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_gmm_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_SRC_IMAGE_T *pstFactor, CVE_DST_IMAGE_T *pstFg,
                                 CVE_DST_IMAGE_T *pstBg, CVE_MEM_INFO_T *pstModel,
                                 CVE_GMM_CTRL_T *pstGmmCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstFactor == AML_NULL) || (pstFg == AML_NULL) ||
            (pstBg == AML_NULL) || (pstModel == AML_NULL) || (pstGmmCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_canny_hys_edge_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                            CVE_DST_IMAGE_T *pstEdge, CVE_DST_MEM_INFO_T *pstStack,
                                            CVE_CANNY_HYS_EDGE_CTRL_T *pstCannyHysEdgeCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstEdge == AML_NULL) || (pstStack == AML_NULL) ||
            (pstCannyHysEdgeCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32
cve_check_canny_edge_param_user(CVE_IMAGE_T *pstEdge, CVE_MEM_INFO_T *pstStack,
                                CVE_CANNY_EDGE_CTRL_T *pstCannyEdgeCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if ((pstEdge == AML_NULL) || (pstStack == AML_NULL) || (pstCannyEdgeCtrl == AML_NULL)) {
        s32Ret = AML_ERR_CVE_NULL_PTR;
    }

    if ((pstEdge->au64PhyAddr[0] == AML_NULL) || (pstEdge->au64VirAddr[0] == AML_NULL)) {
        CVE_ERR_TRACE("Invalid address\n");
        s32Ret = AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstStack->u64PhyAddr == AML_NULL) || (pstStack->u64VirAddr == AML_NULL)) {
        CVE_ERR_TRACE("Invalid address\n");
        s32Ret = AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstCannyEdgeCtrl->u32CannyCount > pstEdge->u32Width * pstEdge->u32Height) ||
        (pstCannyEdgeCtrl->u32CannyCount < 0)) {
        CVE_ERR_TRACE("[CANNY_EDGE] [pstCannyEdgeCtrl->u32CannyCount](%d) set "
                      "value error, value "
                      "must in[%d, %d]\n",
                      pstCannyEdgeCtrl->u32CannyCount, 1, pstEdge->u32Width * pstEdge->u32Height);
        return AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if (pstCannyEdgeCtrl->enOutputDataMode >= CVE_CANNY_EDGE_OUTPUT_DATA_MODE_BUTT) {
        CVE_ERR_TRACE("[CANNY_EDGE][pstCannyEdgeCtrl->enOutputDataMode] not "
                      "support this mode "
                      "[%d], valid range [0, %u]\n",
                      pstCannyEdgeCtrl->enOutputDataMode, CVE_CANNY_EDGE_OUTPUT_DATA_MODE_BUTT - 1);
        return AML_ERR_CVE_ILLEGAL_PARAM;
    }

    return s32Ret;
}

AML_S32 cve_check_lbp_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                 CVE_DST_IMAGE_T *pstDst, CVE_LBP_CTRL_T *pstLbpCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstDst == AML_NULL) || (pstLbpCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_norm_grad_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                       CVE_DST_IMAGE_T *pstDstH, CVE_DST_IMAGE_T *pstDstV,
                                       CVE_DST_IMAGE_T *pstDstHV,
                                       CVE_NORM_GRAD_CTRL_T *pstNormGradCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc != AML_NULL) && (pstNormGradCtrl != AML_NULL)) {
            switch (pstNormGradCtrl->enOutCtrl) {
            case CVE_NORM_GRAD_OUT_CTRL_HOR_AND_VER:
                if ((pstDstH == AML_NULL) || (pstDstV == AML_NULL)) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("norm grad params have Null handle.\n");
                }
                break;
            case CVE_NORM_GRAD_OUT_CTRL_HOR:
                if (pstDstH == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("norm grad params have Null handle.\n");
                }
                break;
            case CVE_NORM_GRAD_OUT_CTRL_VER:
                if (pstDstV == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("norm grad params have Null handle.\n");
                }
                break;
            case CVE_NORM_GRAD_OUT_CTRL_COMBINE:
                if (pstDstHV == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("norm grad params have Null handle.\n");
                }
                break;
            default:
                CVE_ERR_TRACE("norm grad params error.\n");
                s32Ret = AML_ERR_CVE_NOT_SURPPORT;
                break;
            }
        } else {
            CVE_ERR_TRACE("norm grad params have Null handle.\n");
            s32Ret = AML_ERR_CVE_NOT_SURPPORT;
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_buildlkoptionalflowpyr_param_user(
    CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrcPrevPyr,
    CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T *pstBuildLkOptiFlowPyrCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrcPrevPyr == AML_NULL) || (pstBuildLkOptiFlowPyrCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32
cve_check_lk_optical_flow_pyr_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_MEM_INFO_T *pstPrevPts,
                                         CVE_MEM_INFO_T *pstNextPts, CVE_DST_MEM_INFO_T *pstStatus,
                                         CVE_DST_MEM_INFO_T *pstErr,
                                         CVE_LK_OPTICAL_FLOW_PYR_CTRL_T *pstLkOptiFlowPyrCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstPrevPts != AML_NULL) && (pstNextPts != AML_NULL) && (pstStatus != AML_NULL) &&
            (pstLkOptiFlowPyrCtrl != AML_NULL)) {
            switch (pstLkOptiFlowPyrCtrl->enOutMode) {
            case CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_NONE:
                break;
            case CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_ERR:
                if (pstErr == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            case CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_BOTH:
                if (pstErr == AML_NULL) {
                    s32Ret = AML_ERR_CVE_NULL_PTR;
                    CVE_ERR_TRACE("pCve have Null handle\n");
                }
                break;
            default:
                CVE_ERR_TRACE("norm grad params error.\n");
                s32Ret = AML_ERR_CVE_NOT_SURPPORT;
                break;
            }
        } else {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_st_candi_corner_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                                             CVE_DST_IMAGE_T *pstLabel,
                                             CVE_DST_IMAGE_T *pstCandiCorner,
                                             CVE_DST_MEM_INFO_T *pstCorner,
                                             CVE_ST_CANDI_CORNER_CTRL_T *pstStCandiCornerCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc == AML_NULL) || (pstLabel == AML_NULL) || (pstCandiCorner == AML_NULL) ||
            (pstCorner == AML_NULL) || (pstStCandiCornerCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_st_corner_param_user(CVE_SRC_MEM_INFO_T *pstCandiCornerPoint,
                                       CVE_DST_MEM_INFO_T *pstCornerPoint,
                                       CVE_ST_CORNER_CTRL_T *pstStCornerCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if ((pstCandiCornerPoint == NULL) || (pstCornerPoint == NULL) || (pstStCornerCtrl == NULL)) {
        s32Ret = AML_ERR_CVE_NULL_PTR;
        CVE_ERR_TRACE("pCve have Null handle\n");
        return s32Ret;
    }

    if ((pstCandiCornerPoint->u64PhyAddr == AML_NULL) ||
        (pstCandiCornerPoint->u64VirAddr == AML_NULL)) {
        CVE_ERR_TRACE("Invalid address\n");
        s32Ret = AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstCornerPoint->u64PhyAddr == AML_NULL) || (pstCornerPoint->u64VirAddr == AML_NULL)) {
        CVE_ERR_TRACE("Invalid address\n");
        s32Ret = AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstStCornerCtrl->u32MinDist > 255) || (pstStCornerCtrl->u32MinDist < 1)) {
        CVE_ERR_TRACE("[ST_CORNER] [pstStCornerCtrl->u32MinDist](%d) set value error, value "
                      "must in[%d, %d]\n",
                      pstStCornerCtrl->u32MinDist, 1, 255);
        return AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstStCornerCtrl->u32MaxCornerNum > 500) || (pstStCornerCtrl->u32MaxCornerNum < 1)) {
        CVE_ERR_TRACE("[ST_CORNER] [pstStCornerCtrl->u32MaxCornerNum](%d) set "
                      "value error, value "
                      "must in[%d, %d]\n",
                      pstStCornerCtrl->u32MaxCornerNum, 1, 500);
        return AML_ERR_CVE_ILLEGAL_PARAM;
    }

    if ((pstStCornerCtrl->u32CornerNum > 500) || (pstStCornerCtrl->u32CornerNum < 1)) {
        CVE_ERR_TRACE("[ST_CORNER] [pstStCornerCtrl->u32CornerNum](%d) set value "
                      "error, value "
                      "must in[%d, %d]\n",
                      pstStCornerCtrl->u32CornerNum, 1, 500);
        return AML_ERR_CVE_ILLEGAL_PARAM;
    }
    return s32Ret;
}

AML_S32
cve_check_sad_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                         CVE_DST_IMAGE_T *pstSad, CVE_DST_IMAGE_T *pstThr,
                         CVE_SAD_CTRL_T *pstSadCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrc1 == AML_NULL) || (pstSrc2 == AML_NULL) || (pstSadCtrl == AML_NULL) ||
            (pstSad == AML_NULL) || (pstThr == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32 cve_check_grad_fg_param_user(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstFg,
                                     CVE_SRC_IMAGE_T *pstCurGrad, CVE_SRC_IMAGE_T *pstBgGrad,
                                     CVE_DST_IMAGE_T *pstGradFg, CVE_GRAD_FG_CTRL_T *pstGradFgCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstFg == AML_NULL) || (pstCurGrad == AML_NULL) || (pstBgGrad == AML_NULL) ||
            (pstGradFg == AML_NULL) || (pstGradFgCtrl == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}

AML_S32
cve_check_tof_user(CVE_HANDLE *pCveHandle, CVE_SRC_RAW_T *pstSrcRaw, CVE_SRC_RAW_T *pstSrcFpn,
                   CVE_SRC_MEM_INFO_T *pstSrcCoef, CVE_SRC_MEM_INFO_T *pstBpc,
                   CVE_DST_MEM_INFO_T *pstDtsStatus, CVE_DST_MEM_INFO_T *pstDtsIR,
                   CVE_DST_MEM_INFO_T *pstDtsData, CVE_DST_MEM_INFO_T *pstDstHist,
                   CVE_TOF_CTRL_T *pstTofCtrl)
{
    AML_S32 s32Ret = AML_SUCCESS;

    if (pCveHandle != AML_NULL) {
        if ((pstSrcRaw == AML_NULL) || (pstSrcFpn == AML_NULL) || (pstSrcCoef == AML_NULL) ||
            (pstDtsStatus == AML_NULL) || (pstDtsIR == AML_NULL) || (pstDtsData == AML_NULL) ||
            (pstTofCtrl == AML_NULL) || (pstBpc == AML_NULL) || (pstDstHist == AML_NULL)) {
            s32Ret = AML_ERR_CVE_NULL_PTR;
            CVE_ERR_TRACE("pCve have Null handle\n");
        }
    } else {
        CVE_ERR_TRACE("pCveHandle is NULL, CVE not init\n");
        s32Ret = AML_ERR_CVE_NOTREADY;
    }
    return s32Ret;
}
