/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#include "aml_cve.h"
#include "cve.h"
#include "cve_check_params.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define CVE_MIN(a, b) ((a) < (b) ? (a) : (b))
#define CVE_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CVE_CLIP3(low, high, x) (CVE_MAX(CVE_MIN(x, high), low))

#define CVE_DEV "/dev/cve"
static pthread_mutex_t g_stCveMutex = PTHREAD_MUTEX_INITIALIZER;
static AML_S32 g_s32CveFd = -1;

static AML_S32 cve_check_fd_open()
{
    AML_S32 s32Ret = AML_SUCCESS;

    pthread_mutex_lock(&g_stCveMutex);
    if (g_s32CveFd < 0) {
        g_s32CveFd = open(CVE_DEV, O_RDWR);
        if (g_s32CveFd < 0) {
            CVE_ERR_TRACE("cve dev open failed\n");
            s32Ret = AML_ERR_CVE_NOTREADY;
        }
    }
    pthread_mutex_unlock(&g_stCveMutex);

    return s32Ret;
}

static AML_S32 cve_norm_grad(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                             CVE_DST_IMAGE_T *pstDstH, CVE_DST_IMAGE_T *pstDstV,
                             CVE_DST_IMAGE_T *pstDstHV, CVE_NORM_GRAD_CTRL_T *pstNormGradCtrl,
                             AML_BOOL_E bInstant)
{
    CVE_OP_NORM_GRAD_T stOpNormGrad;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_norm_grad_param_user(pCveHandle, pstSrc, pstDstH, pstDstV, pstDstHV,
                                            pstNormGradCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check NormGrad parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpNormGrad, 0, sizeof(CVE_OP_NORM_GRAD_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpNormGrad.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));

    switch (pstNormGradCtrl->enOutCtrl) {
    case CVE_NORM_GRAD_OUT_CTRL_HOR_AND_VER:
        memcpy(&stOpNormGrad.stDstH, pstDstH, sizeof(CVE_DST_IMAGE_T));
        memcpy(&stOpNormGrad.stDstV, pstDstV, sizeof(CVE_DST_IMAGE_T));
        break;
    case CVE_NORM_GRAD_OUT_CTRL_HOR:
        memcpy(&stOpNormGrad.stDstH, pstDstH, sizeof(CVE_DST_IMAGE_T));
        break;
    case CVE_NORM_GRAD_OUT_CTRL_VER:
        memcpy(&stOpNormGrad.stDstV, pstDstV, sizeof(CVE_DST_IMAGE_T));
        break;
    case CVE_NORM_GRAD_OUT_CTRL_COMBINE:
        memcpy(&stOpNormGrad.stDstHV, pstDstHV, sizeof(CVE_DST_IMAGE_T));
        break;
    default:
        break;
    }

    memcpy(&stOpNormGrad.stNormGradCtrl, pstNormGradCtrl, sizeof(CVE_NORM_GRAD_CTRL_T));

    stOpNormGrad.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_NORM_GRAD, &stOpNormGrad);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpNormGrad.cveHandle;

    return s32Ret;
}

AML_S32 CVE_DMA(CVE_HANDLE *pCveHandle, CVE_DATA_T *pstSrc, CVE_DST_DATA_T *pstDst,
                CVE_DMA_CTRL_T *pstDmaCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_DMA_T stOpDMA;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_dma_param_user(pCveHandle, pstSrc, pstDst, pstDmaCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check DMA parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpDMA, 0, sizeof(CVE_OP_DMA_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    if ((pstDmaCtrl->enMode <= CVE_DMA_MODE_INTERVAL_COPY) ||
        (pstDmaCtrl->enMode == CVE_DMA_MODE_NOT)) {
        memcpy(&stOpDMA.stSrcDATA, pstSrc, sizeof(CVE_DATA_T));
    }
    memcpy(&stOpDMA.stDstDATA, pstDst, sizeof(CVE_DST_DATA_T));
    memcpy(&stOpDMA.stDmaCtrl, pstDmaCtrl, sizeof(CVE_DMA_CTRL_T));
    stOpDMA.bInstant = bInstant;
    s32Ret = ioctl(g_s32CveFd, CVE_OP_DMA, &stOpDMA);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpDMA.cveHandle;

    return s32Ret;
}

AML_S32 CVE_LumaStatArray(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                          CVE_DST_MEM_INFO_T *pstDst, const CVE_RECT_U16_T astCveLumaRect[],
                          CVE_LUMA_STAT_ARRAY_CTRL_T *pstLumaStatArrayCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_LUAM_STAT_ARRAY_T stOpLuamStat;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_luamStat_param_user(pCveHandle, pstSrc, pstDst, astCveLumaRect,
                                           pstLumaStatArrayCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check LuamStat parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpLuamStat, 0, sizeof(CVE_OP_LUAM_STAT_ARRAY_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpLuamStat.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpLuamStat.stDstMem, pstDst, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpLuamStat.stLumaStatArrayCtrl, pstLumaStatArrayCtrl,
           sizeof(CVE_LUMA_STAT_ARRAY_CTRL_T));
    memcpy(stOpLuamStat.astCveLumaRect, astCveLumaRect,
           sizeof(CVE_RECT_U16_T) * pstLumaStatArrayCtrl->u8MaxLumaRect);
    stOpLuamStat.bInstant = bInstant;
    s32Ret = ioctl(g_s32CveFd, CVE_OP_LUMA_STAT, &stOpLuamStat);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpLuamStat.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Filter(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_FILTER_CTRL_T *pstFltCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_FILTER_T stOpFilter;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_filter_param_user(pCveHandle, pstSrc, pstDst, pstFltCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Filter parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }
    memset((void *)&stOpFilter, 0, sizeof(CVE_OP_FILTER_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpFilter.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpFilter.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpFilter.stFilterCtrl, pstFltCtrl, sizeof(CVE_FILTER_CTRL_T));
    stOpFilter.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_FILTER, &stOpFilter);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpFilter.cveHandle;

    return s32Ret;
}

AML_S32 CVE_CSC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_CSC_CTRL_T *pstCscCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_CSC_T stOpCsc;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_csc_param_user(pCveHandle, pstSrc, pstDst, pstCscCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check CSC parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpCsc, 0, sizeof(CVE_OP_CSC_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpCsc.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpCsc.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpCsc.stCscCtrl, pstCscCtrl, sizeof(CVE_CSC_CTRL_T));
    stOpCsc.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_CSC, &stOpCsc);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpCsc.cveHandle;

    return s32Ret;
}

AML_S32 CVE_FilterAndCSC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                         CVE_FILTER_AND_CSC_CTRL_T *pstFltCscCtrl, AML_BOOL_E bInstant)
{

    CVE_OP_FILTER_AND_CSC_T stOpFilterAndCsc;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_filter_and_csc_param_user(pCveHandle, pstSrc, pstDst, pstFltCscCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check FilterAndCSC parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpFilterAndCsc, 0, sizeof(CVE_OP_FILTER_AND_CSC_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpFilterAndCsc.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpFilterAndCsc.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpFilterAndCsc.stFilterCscCtrl, pstFltCscCtrl, sizeof(CVE_FILTER_AND_CSC_CTRL_T));
    stOpFilterAndCsc.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_FILTER_AND_CSC, &stOpFilterAndCsc);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpFilterAndCsc.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Sobel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstH,
                  CVE_DST_IMAGE_T *pstDstV, CVE_SOBEL_CTRL_T *pstSobelCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_SOBEL_T stOpSobel;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_sobel_param_user(pCveHandle, pstSrc, pstDstH, pstDstV, pstSobelCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Sobel parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpSobel, 0, sizeof(CVE_OP_SOBEL_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpSobel.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    switch (pstSobelCtrl->enOutCtrl) {
    case CVE_SOBEL_OUT_CTRL_BOTH:
        memcpy(&stOpSobel.stDstH, pstDstH, sizeof(CVE_DST_IMAGE_T));
        memcpy(&stOpSobel.stDstV, pstDstV, sizeof(CVE_DST_IMAGE_T));
        break;
    case CVE_SOBEL_OUT_CTRL_HOR:
        memcpy(&stOpSobel.stDstH, pstDstH, sizeof(CVE_DST_IMAGE_T));
        break;
    case CVE_SOBEL_OUT_CTRL_VER:
        memcpy(&stOpSobel.stDstV, pstDstV, sizeof(CVE_DST_IMAGE_T));
        break;
    default:
        break;
    }

    memcpy(&stOpSobel.stSobelCtrl, pstSobelCtrl, sizeof(CVE_SOBEL_CTRL_T));
    stOpSobel.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_SOBEL, &stOpSobel);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpSobel.cveHandle;

    return s32Ret;
}

AML_S32 CVE_MagAndAng(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstMag,
                      CVE_DST_IMAGE_T *pstDstAng, CVE_MAG_AND_ANG_CTRL_T *pstMagAndAngCtrl,
                      AML_BOOL_E bInstant)
{
    CVE_OP_MAG_AND_ANG_T stOpMagAndAng;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_mag_and_ang_param_user(pCveHandle, pstSrc, pstDstMag, pstDstAng,
                                              pstMagAndAngCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check MagAndAng parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpMagAndAng, 0, sizeof(CVE_OP_MAG_AND_ANG_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpMagAndAng.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    if ((pstMagAndAngCtrl->enOutCtrl == CVE_MAG_AND_ANG_OUT_CTRL_MAG_AND_ANG) ||
        (pstMagAndAngCtrl->enOutCtrl == CVE_MAG_AND_ANG_OUT_CTRL_HOG)) {
        memcpy(&stOpMagAndAng.stDstMag, pstDstMag, sizeof(CVE_DST_IMAGE_T));
        memcpy(&stOpMagAndAng.stDstAng, pstDstAng, sizeof(CVE_DST_IMAGE_T));
    } else {
        memcpy(&stOpMagAndAng.stDstMag, pstDstMag, sizeof(CVE_DST_IMAGE_T));
    }
    memcpy(&stOpMagAndAng.stMagAndAngCtrl, pstMagAndAngCtrl, sizeof(CVE_MAG_AND_ANG_CTRL_T));
    stOpMagAndAng.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_MAG_AND_ANG, &stOpMagAndAng);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpMagAndAng.cveHandle;

    return s32Ret;
}

AML_S32 CVE_MatchBgModel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                         CVE_SRC_IMAGE_T *pstPreImg, CVE_MEM_INFO_T *pstBgModel,
                         CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg,
                         CVE_DST_IMAGE_T *pstCurDiffBg, CVE_DST_IMAGE_T *pstFrmDiff,
                         CVE_DST_MEM_INFO_T *pstStatData,
                         CVE_MATCH_BG_MODEL_CTRL_T *pstMatchBgModelCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_MATCH_BG_MODEL_T stOpMatchBgModel;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_match_bg_model_param_user(pCveHandle, pstCurImg, pstPreImg, pstBgModel,
                                                 pstFg, pstBg, pstCurDiffBg, pstFrmDiff,
                                                 pstStatData, pstMatchBgModelCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check MatchBgModel parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpMatchBgModel, 0, sizeof(CVE_OP_MATCH_BG_MODEL_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpMatchBgModel.stCurImg, pstCurImg, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpMatchBgModel.stPreImg, pstPreImg, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpMatchBgModel.stBgModel, pstBgModel, sizeof(CVE_MEM_INFO_T));
    memcpy(&stOpMatchBgModel.stFg, pstFg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpMatchBgModel.stBg, pstBg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpMatchBgModel.stCurDiffBg, pstCurDiffBg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpMatchBgModel.stFrmDiff, pstFrmDiff, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpMatchBgModel.stStatData, pstStatData, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpMatchBgModel.stMatchBgModelCtrl, pstMatchBgModelCtrl,
           sizeof(CVE_MATCH_BG_MODEL_CTRL_T));
    stOpMatchBgModel.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_MATCH_BG_MODEL, &stOpMatchBgModel);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpMatchBgModel.cveHandle;

    return s32Ret;
}

AML_S32 CVE_UpdateBgModel(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstCurImg,
                          CVE_MEM_INFO_T *pstBgModel1, CVE_MEM_INFO_T *pstBgModel2,
                          CVE_DST_MEM_INFO_T *pstStatData,
                          CVE_UPDATE_BG_MODEL_CTRL_T *pstUpdateBgModelCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_UPDATE_BG_MODEL_T stOpUpdateBgModel;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_update_bg_model_param_user(pCveHandle, pstCurImg, pstBgModel1, pstBgModel2,
                                                  pstStatData, pstUpdateBgModelCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check UpdateBgModel parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpUpdateBgModel, 0, sizeof(CVE_OP_UPDATE_BG_MODEL_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }
    memcpy(&stOpUpdateBgModel.stCurImg, pstCurImg, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpUpdateBgModel.stBgModel1, pstBgModel1, sizeof(CVE_MEM_INFO_T));
    memcpy(&stOpUpdateBgModel.stBgModel2, pstBgModel2, sizeof(CVE_MEM_INFO_T));
    memcpy(&stOpUpdateBgModel.stStatData, pstStatData, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpUpdateBgModel.stUpdateBgModelCtrl, pstUpdateBgModelCtrl,
           sizeof(CVE_UPDATE_BG_MODEL_CTRL_T));
    stOpUpdateBgModel.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_UPDATE_BG_MODEL, &stOpUpdateBgModel);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpUpdateBgModel.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Dilate(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_DILATE_CTRL_T *pstDilateCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_DILATE_T stOpDilate;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_dilate_param_user(pCveHandle, pstSrc, pstDst, pstDilateCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Dilate parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpDilate, 0, sizeof(CVE_OP_DILATE_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpDilate.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpDilate.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpDilate.stDilateCtrl, pstDilateCtrl, sizeof(CVE_DILATE_CTRL_T));
    stOpDilate.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_DILATE, &stOpDilate);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpDilate.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Erode(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                  CVE_ERODE_CTRL_T *pstErodeCtrl, AML_BOOL_E bInstant)
{

    CVE_OP_ERODE_T stOpErode;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_erode_param_user(pCveHandle, pstSrc, pstDst, pstErodeCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Erode parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpErode, 0, sizeof(CVE_OP_ERODE_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpErode.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpErode.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpErode.stErodeCtrl, pstErodeCtrl, sizeof(CVE_ERODE_CTRL_T));
    stOpErode.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_ERODE, &stOpErode);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpErode.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Thresh(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                   CVE_THRESH_CTRL_T *pstThrCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_THRESH_T stOpThresh;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_thresh_param_user(pCveHandle, pstSrc, pstDst, pstThrCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Thresh parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpThresh, 0, sizeof(CVE_OP_THRESH_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpThresh.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpThresh.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpThresh.stThreshCtrl, pstThrCtrl, sizeof(CVE_THRESH_CTRL_T));
    stOpThresh.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_THRESH, &stOpThresh);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpThresh.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Sub(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, CVE_SUB_CTRL_T *pstSubCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_SUB_T stOpSub;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_sub_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst, pstSubCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Sub parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpSub, 0, sizeof(CVE_OP_SUB_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpSub.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpSub.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpSub.stDst, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpSub.stSubCtrl, pstSubCtrl, sizeof(CVE_SUB_CTRL_T));
    stOpSub.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_SUB, &stOpSub);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpSub.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Or(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
               CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant)
{
    CVE_OP_OR_T stOpOr;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_or_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst);
    if (s32Ret) {
        CVE_ERR_TRACE("check Or parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpOr, 0, sizeof(CVE_OP_OR_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpOr.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpOr.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpOr.stDst, pstDst, sizeof(CVE_DST_IMAGE_T));
    stOpOr.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_OR, &stOpOr);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpOr.cveHandle;

    return s32Ret;
}

AML_S32 CVE_And(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant)
{

    CVE_OP_AND_T stOpAnd;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_and_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst);
    if (s32Ret) {
        CVE_ERR_TRACE("check And parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpAnd, 0, sizeof(CVE_OP_AND_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpAnd.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpAnd.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpAnd.stDst, pstDst, sizeof(CVE_DST_IMAGE_T));
    stOpAnd.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_AND, &stOpAnd);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpAnd.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Xor(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, AML_BOOL_E bInstant)
{
    CVE_OP_XOR_T stOpXor;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_xor_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst);
    if (s32Ret) {
        CVE_ERR_TRACE("check Xor parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpXor, 0, sizeof(CVE_OP_XOR_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpXor.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpXor.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpXor.stDst, pstDst, sizeof(CVE_DST_IMAGE_T));
    stOpXor.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_XOR, &stOpXor);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpXor.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Add(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstDst, CVE_ADD_CTRL_T *pstAddCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_ADD_T stOpAdd;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_add_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst, pstAddCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Add parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpAdd, 0, sizeof(CVE_OP_ADD_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpAdd.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpAdd.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpAdd.stDst, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpAdd.stAddCtrl, pstAddCtrl, sizeof(CVE_ADD_CTRL_T));
    stOpAdd.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_ADD, &stOpAdd);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpAdd.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Integ(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                  CVE_INTEG_CTRL_T *pstIntegCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_INTEG_T stOpInteg;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_integ_param_user(pCveHandle, pstSrc, pstDst, pstIntegCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Integ parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpInteg, 0, sizeof(CVE_OP_INTEG_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpInteg.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpInteg.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpInteg.stIntegCtrl, pstIntegCtrl, sizeof(CVE_INTEG_CTRL_T));
    stOpInteg.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_INTEG, &stOpInteg);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpInteg.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Hist(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_MEM_INFO_T *pstDst,
                 AML_BOOL_E bInstant)
{
    CVE_OP_HIST_T stOpHist;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_hist_param_user(pCveHandle, pstSrc, pstDst);
    if (s32Ret) {
        CVE_ERR_TRACE("check Hist parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpHist, 0, sizeof(CVE_OP_HIST_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpHist.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpHist.stDstMem, pstDst, sizeof(CVE_DST_MEM_INFO_T));
    stOpHist.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_HIST, &stOpHist);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpHist.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Thresh_S16(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                       CVE_THRESH_S16_CTRL_T *pstThrS16Ctrl, AML_BOOL_E bInstant)
{
    CVE_OP_THRESH_S16_T stOpThreshS16;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_thresh_s16_param_user(pCveHandle, pstSrc, pstDst, pstThrS16Ctrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Thresh_S16 parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpThreshS16, 0, sizeof(CVE_OP_THRESH_S16_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpThreshS16.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpThreshS16.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpThreshS16.stThreshS16Ctrl, pstThrS16Ctrl, sizeof(CVE_THRESH_S16_CTRL_T));
    stOpThreshS16.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_THRESH_S16, &stOpThreshS16);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpThreshS16.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Thresh_U16(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                       CVE_THRESH_U16_CTRL_T *pstThrU16Ctrl, AML_BOOL_E bInstant)
{
    CVE_OP_THRESH_U16_T stOpThreshU16;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_thresh_u16_param_user(pCveHandle, pstSrc, pstDst, pstThrU16Ctrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Thresh_U16 parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpThreshU16, 0, sizeof(CVE_OP_THRESH_U16_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpThreshU16.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpThreshU16.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpThreshU16.stThreshU16Ctrl, pstThrU16Ctrl, sizeof(CVE_THRESH_U16_CTRL_T));
    stOpThreshU16.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_THRESH_U16, &stOpThreshU16);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpThreshU16.cveHandle;

    return s32Ret;
}

AML_S32 CVE_16BitTo8Bit(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                        CVE_16BIT_TO_8BIT_CTRL_T *pst16BitTo8BitCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_16BIT_TO_8BIT_T stOp16bitTo8bit;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_16bit_to_8bit_param_user(pCveHandle, pstSrc, pstDst, pst16BitTo8BitCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check 16BitTo8Bit parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOp16bitTo8bit, 0, sizeof(CVE_OP_16BIT_TO_8BIT_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOp16bitTo8bit.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOp16bitTo8bit.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOp16bitTo8bit.st16BitTo8BitCtrl, pst16BitTo8BitCtrl,
           sizeof(CVE_16BIT_TO_8BIT_CTRL_T));
    stOp16bitTo8bit.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_16BIT_TO_8BIT, &stOp16bitTo8bit);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOp16bitTo8bit.cveHandle;

    return s32Ret;
}

AML_S32 CVE_OrdStatFilter(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                          CVE_ORD_STAT_FILTER_CTRL_T *pstOrdStatFltCtrl, AML_BOOL_E bInstant)
{

    CVE_OP_ORD_STAT_FILTER_T stOpOrdStatFilter;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_ord_stat_filter_param_user(pCveHandle, pstSrc, pstDst, pstOrdStatFltCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check OrdStatFilter parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpOrdStatFilter, 0, sizeof(CVE_OP_ORD_STAT_FILTER_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpOrdStatFilter.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpOrdStatFilter.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpOrdStatFilter.stOrdStatFltCtrl, pstOrdStatFltCtrl,
           sizeof(CVE_ORD_STAT_FILTER_CTRL_T));
    stOpOrdStatFilter.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_ORD_STAT_FILTER, &stOpOrdStatFilter);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpOrdStatFilter.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Map(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_SRC_MEM_INFO_T *pstMap,
                CVE_DST_IMAGE_T *pstDst, CVE_MAP_CTRL_T *pstMapCtrl, AML_BOOL_E bInstant)
{

    CVE_OP_MAP_T stOpMap;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_map_param_user(pCveHandle, pstSrc, pstMap, pstDst, pstMapCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check Map parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpMap, 0, sizeof(CVE_OP_MAP_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpMap.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpMap.stMap, pstMap, sizeof(CVE_SRC_MEM_INFO_T));
    memcpy(&stOpMap.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpMap.stMapCtrl, pstMapCtrl, sizeof(CVE_MAP_CTRL_T));
    stOpMap.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_MAP, &stOpMap);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpMap.cveHandle;

    return s32Ret;
}

AML_S32 CVE_EqualizeHist(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                         CVE_EQUALIZE_HIST_CTRL_T *pstEqualizeHistCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_EQUALIZE_HIST_T stOpEqualizeHist;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_equalize_hist_param_user(pCveHandle, pstSrc, pstDst, pstEqualizeHistCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check EqulizeHist parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpEqualizeHist, 0, sizeof(CVE_OP_EQUALIZE_HIST_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpEqualizeHist.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpEqualizeHist.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpEqualizeHist.stEqualizeHistCtrl, pstEqualizeHistCtrl,
           sizeof(CVE_EQUALIZE_HIST_CTRL_T));
    stOpEqualizeHist.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_EQUALIZE_HIST, &stOpEqualizeHist);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpEqualizeHist.cveHandle;

    return s32Ret;
}

AML_S32 CVE_NCC(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_MEM_INFO_T *pstDst, CVE_NCC_CTRL_T *pstNccCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_NCC_T stOpNcc;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_ncc_param_user(pCveHandle, pstSrc1, pstSrc2, pstDst, pstNccCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check NCC parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpNcc, 0, sizeof(CVE_OP_NCC_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpNcc.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpNcc.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpNcc.stDstmem, pstDst, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpNcc.stNccCtrl, pstNccCtrl, sizeof(CVE_NCC_CTRL_T));
    stOpNcc.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_NCC, &stOpNcc);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpNcc.cveHandle;

    return s32Ret;
}

AML_S32 CVE_CCL(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_DST_MEM_INFO_T *pstBlob, CVE_CCL_CTRL_T *pstCclCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_CCL_T stOpCcl;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_ccl_param_user(pCveHandle, pstSrc, pstDst, pstBlob, pstCclCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check CCL parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpCcl, 0, sizeof(CVE_OP_CCL_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpCcl.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpCcl.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpCcl.stBlob, pstBlob, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpCcl.stCclCtrl, pstCclCtrl, sizeof(CVE_CCL_CTRL_T));
    stOpCcl.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_CCL, &stOpCcl);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpCcl.cveHandle;

    return s32Ret;
}

AML_S32 CVE_GMM(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_SRC_IMAGE_T *pstFactor,
                CVE_DST_IMAGE_T *pstFg, CVE_DST_IMAGE_T *pstBg, CVE_MEM_INFO_T *pstModel,
                CVE_GMM_CTRL_T *pstGmmCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_GMM_T stOpGmm;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret =
        cve_check_gmm_param_user(pCveHandle, pstSrc, pstFactor, pstFg, pstBg, pstModel, pstGmmCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check GMM parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpGmm, 0, sizeof(CVE_OP_GMM_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpGmm.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpGmm.stFactor, pstFactor, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpGmm.stFg, pstFg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpGmm.stBg, pstBg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpGmm.stModel, pstModel, sizeof(CVE_MEM_INFO_T));
    memcpy(&stOpGmm.stGmmCtrl, pstGmmCtrl, sizeof(CVE_GMM_CTRL_T));
    stOpGmm.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_GMM, &stOpGmm);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpGmm.cveHandle;

    return s32Ret;
}

AML_S32 CVE_CannyHysEdge(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstEdge,
                         CVE_DST_MEM_INFO_T *pstStack,
                         CVE_CANNY_HYS_EDGE_CTRL_T *pstCannyHysEdgeCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_CANNY_HYS_EDGE_T stOpCannyHysEdge;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_canny_hys_edge_param_user(pCveHandle, pstSrc, pstEdge, pstStack,
                                                 pstCannyHysEdgeCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check CCL parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpCannyHysEdge, 0, sizeof(CVE_OP_CANNY_HYS_EDGE_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }
    memcpy(&stOpCannyHysEdge.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpCannyHysEdge.stEdge, pstEdge, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpCannyHysEdge.stStack, pstStack, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpCannyHysEdge.stCannyHysEdgeCtrl, pstCannyHysEdgeCtrl,
           sizeof(CVE_CANNY_HYS_EDGE_CTRL_T));
    stOpCannyHysEdge.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_CANNY_HYS_EDGE, &stOpCannyHysEdge);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpCannyHysEdge.cveHandle;

    return s32Ret;
}

AML_S32 CVE_CannyEdge(CVE_IMAGE_T *pstEdge, CVE_MEM_INFO_T *pstStack,
                      CVE_CANNY_EDGE_CTRL_T *pstCannyEdgeCtrl)
{
    CVE_POINT_U16_T *pstStackPoints;
    AML_U16 au16Xi[3];
    AML_U16 au16Yi[3];
    AML_U8 *ps32Edge;
    AML_S32 i, j, m, n, num;
    AML_U16 s32Row;
    AML_U16 s32Col;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_canny_edge_param_user(pstEdge, pstStack, pstCannyEdgeCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check cannyEdge parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    ps32Edge = (AML_U8 *)(AML_UINTPTR_T)pstEdge->au64VirAddr[0];
    pstStackPoints = (CVE_POINT_U16_T *)(AML_UINTPTR_T)pstStack->u64VirAddr;
    num = pstCannyEdgeCtrl->u32CannyCount;

    for (i = 0; i < num; i++) {
        s32Row = pstStackPoints[i].u16X;
        s32Col = pstStackPoints[i].u16Y;

        for (j = -1; j <= 1; ++j) {
            au16Yi[j + 1] = CVE_CLIP3(0, pstEdge->u32Height - 1, j + s32Row);
        }

        for (j = -1; j <= 1; ++j) {
            au16Xi[j + 1] = CVE_CLIP3(0, pstEdge->u32Width - 1, j + s32Col);
        }

        for (m = 0; m < 3; m++) {
            for (n = 0; n < 3; n++) {
                if ((m == 1) && (n == 1))
                    continue;
                if (ps32Edge[au16Yi[m] * pstEdge->au32Stride[0] + au16Xi[n]] == 0) {
                    ps32Edge[au16Yi[m] * pstEdge->au32Stride[0] + au16Xi[n]] = 2;
                    pstStackPoints[num].u16X = au16Yi[m];
                    pstStackPoints[num].u16Y = au16Xi[n];
                    num++;
                }
            }
        }
    }

    for (i = 0; i < pstEdge->u32Height * pstEdge->au32Stride[0]; i++) {
        if (ps32Edge[i] == 2)
            ps32Edge[i] = (pstCannyEdgeCtrl->enOutputDataMode == CVE_CANNY_EDGE_OUTPUT_DATA_MODE_U1)
                              ? 1
                              : 255;
        else
            ps32Edge[i] = 0;
    }

    return s32Ret;
}

AML_S32 CVE_LBP(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDst,
                CVE_LBP_CTRL_T *pstLbpCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_LBP_T stOpLbp;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_lbp_param_user(pCveHandle, pstSrc, pstDst, pstLbpCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check LBP parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpLbp, 0, sizeof(CVE_OP_LBP_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpLbp.stSrcImage, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpLbp.stDstImage, pstDst, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpLbp.stLbpCtrl, pstLbpCtrl, sizeof(CVE_LBP_CTRL_T));
    stOpLbp.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_LBP, &stOpLbp);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpLbp.cveHandle;

    return s32Ret;
}

AML_S32 CVE_NormGrad(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc, CVE_DST_IMAGE_T *pstDstH,
                     CVE_DST_IMAGE_T *pstDstV, CVE_DST_IMAGE_T *pstDstHV,
                     CVE_NORM_GRAD_CTRL_T *pstNormGradCtrl, AML_BOOL_E bInstant)
{
    return cve_norm_grad(pCveHandle, pstSrc, pstDstH, pstDstV, pstDstHV, pstNormGradCtrl, bInstant);
}

AML_S32 CVE_BuildLKOpticalFlowPyr(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrcPrevPyr,
                                  CVE_DST_IMAGE_T astDstPyr[],
                                  CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T *pstBuildLkOptiFlowPyrCtrl,
                                  AML_BOOL_E bInstant)
{
    CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR_T stOpBuildLkOpticalFlowPyr;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_buildlkoptionalflowpyr_param_user(pCveHandle, pstSrcPrevPyr,
                                                         pstBuildLkOptiFlowPyrCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check LKOpticalFlowPyr parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpBuildLkOpticalFlowPyr, 0, sizeof(CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpBuildLkOpticalFlowPyr.stSrcPyr, pstSrcPrevPyr, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpBuildLkOpticalFlowPyr.astDstPyr, astDstPyr,
           (pstBuildLkOptiFlowPyrCtrl->u8MaxLevel + 1) * sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpBuildLkOpticalFlowPyr.stLkBuildOptiFlowPyrCtrl, pstBuildLkOptiFlowPyrCtrl,
           sizeof(CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T));

    stOpBuildLkOpticalFlowPyr.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR, &stOpBuildLkOpticalFlowPyr);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpBuildLkOpticalFlowPyr.cveHandle;

    return s32Ret;
}

AML_S32 CVE_LKOpticalFlowPyr(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T astSrcPrevPyr[],
                             CVE_SRC_IMAGE_T astSrcNextPyr[], CVE_SRC_MEM_INFO_T *pstPrevPts,
                             CVE_MEM_INFO_T *pstNextPts, CVE_DST_MEM_INFO_T *pstStatus,
                             CVE_DST_MEM_INFO_T *pstErr,
                             CVE_LK_OPTICAL_FLOW_PYR_CTRL_T *pstLkOptiFlowPyrCtrl,
                             AML_BOOL_E bInstant)
{
    CVE_OP_LK_OPTICAL_FLOW_PYR_T stOpLkOpticalFlowPyr;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_lk_optical_flow_pyr_param_user(pCveHandle, pstPrevPts, pstNextPts, pstStatus,
                                                      pstErr, pstLkOptiFlowPyrCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check LKOpticalFlowPyr parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpLkOpticalFlowPyr, 0, sizeof(CVE_OP_LK_OPTICAL_FLOW_PYR_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpLkOpticalFlowPyr.astSrcPrevPyr, astSrcPrevPyr,
           (pstLkOptiFlowPyrCtrl->u8MaxLevel + 1) * sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpLkOpticalFlowPyr.astSrcNextPyr, astSrcNextPyr,
           (pstLkOptiFlowPyrCtrl->u8MaxLevel + 1) * sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpLkOpticalFlowPyr.stPrevPts, pstPrevPts, sizeof(CVE_SRC_MEM_INFO_T));
    memcpy(&stOpLkOpticalFlowPyr.stNextPts, pstNextPts, sizeof(CVE_SRC_MEM_INFO_T));
    memcpy(&stOpLkOpticalFlowPyr.stStatus, pstStatus, sizeof(CVE_DST_MEM_INFO_T));
    if ((pstLkOptiFlowPyrCtrl->enOutMode == CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_ERR) ||
        (pstLkOptiFlowPyrCtrl->enOutMode == CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_BOTH)) {
        memcpy(&stOpLkOpticalFlowPyr.stErr, pstErr, sizeof(CVE_DST_MEM_INFO_T));
    }
    memcpy(&stOpLkOpticalFlowPyr.stLkOptiFlowPyrCtrl, pstLkOptiFlowPyrCtrl,
           sizeof(CVE_LK_OPTICAL_FLOW_PYR_CTRL_T));

    stOpLkOpticalFlowPyr.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_LK_OPTICAL_FLOW_PYR, &stOpLkOpticalFlowPyr);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpLkOpticalFlowPyr.cveHandle;

    return s32Ret;
}

AML_S32 CVE_STCandiCorner(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc,
                          CVE_DST_IMAGE_T *pstLabel, CVE_DST_IMAGE_T *pstCandiCorner,
                          CVE_DST_MEM_INFO_T *pstCandiCornerPoint,
                          CVE_ST_CANDI_CORNER_CTRL_T *pstStCandiCornerCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_ST_CANDI_CORNER_T stOpSTCandiCorner;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_st_candi_corner_param_user(pCveHandle, pstSrc, pstLabel, pstCandiCorner,
                                                  pstCandiCornerPoint, pstStCandiCornerCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check STCandiCorner parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpSTCandiCorner, 0, sizeof(CVE_OP_ST_CANDI_CORNER_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpSTCandiCorner.stSrc, pstSrc, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpSTCandiCorner.stLabel, pstLabel, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpSTCandiCorner.stCandiCorner, pstCandiCorner, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpSTCandiCorner.stCandiCornerPoint, pstCandiCornerPoint, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpSTCandiCorner.stStCandiCornerCtrl, pstStCandiCornerCtrl,
           sizeof(CVE_ST_CANDI_CORNER_CTRL_T));
    stOpSTCandiCorner.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_ST_CANDI_CORNER, &stOpSTCandiCorner);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpSTCandiCorner.cveHandle;

    return s32Ret;
}

AML_S32 CVE_STCorner(CVE_SRC_MEM_INFO_T *pstCandiCornerPoint, CVE_DST_MEM_INFO_T *pstCornerPoint,
                     CVE_ST_CORNER_CTRL_T *pstStCornerCtrl)
{
    CVE_POINT_U16_T *pstCorner = (CVE_POINT_U16_T *)(AML_UINTPTR_T)pstCornerPoint->u64VirAddr;
    CVE_POINT_U16_T *ptrCandiCorner =
        (CVE_POINT_U16_T *)(AML_UINTPTR_T)pstCandiCornerPoint->u64VirAddr;
    int i, dist, cnt = 0, point = 0;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_st_corner_param_user(pstCandiCornerPoint, pstCornerPoint, pstStCornerCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check STCorner parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    while ((cnt < pstStCornerCtrl->u32MaxCornerNum) && (point < pstStCornerCtrl->u32CornerNum)) {
        for (i = 0; i < cnt; i++) {
            dist = (pstCorner[i].u16X - ptrCandiCorner[point].u16X) *
                       (pstCorner[i].u16X - ptrCandiCorner[point].u16X) +
                   (pstCorner[i].u16Y - ptrCandiCorner[point].u16Y) *
                       (pstCorner[i].u16Y - ptrCandiCorner[point].u16Y);
            if (dist < pstStCornerCtrl->u32MinDist)
                break;
        }

        if (i == cnt) {
            pstCorner[cnt].u16X = ptrCandiCorner[point].u16X;
            pstCorner[cnt].u16Y = ptrCandiCorner[point].u16Y;
            cnt++;
        }
        point++;
    }

    return s32Ret;
}

AML_S32 CVE_SAD(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstSrc1, CVE_SRC_IMAGE_T *pstSrc2,
                CVE_DST_IMAGE_T *pstSad, CVE_DST_IMAGE_T *pstThr, CVE_SAD_CTRL_T *pstSadCtrl,
                AML_BOOL_E bInstant)
{
    CVE_OP_SAD_T stOpSad;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_sad_param_user(pCveHandle, pstSrc1, pstSrc2, pstSad, pstThr, pstSadCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check SAD parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpSad, 0, sizeof(CVE_OP_SAD_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpSad.stSrcImage1, pstSrc1, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpSad.stSrcImage2, pstSrc2, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpSad.stSad, pstSad, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpSad.stThr, pstThr, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpSad.stSadCtrl, pstSadCtrl, sizeof(CVE_SAD_CTRL_T));

    stOpSad.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_SAD, &stOpSad);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpSad.cveHandle;

    return s32Ret;
}

AML_S32 CVE_GradFg(CVE_HANDLE *pCveHandle, CVE_SRC_IMAGE_T *pstFg, CVE_SRC_IMAGE_T *pstCurGrad,
                   CVE_SRC_IMAGE_T *pstBgGrad, CVE_DST_IMAGE_T *pstGradFg,
                   CVE_GRAD_FG_CTRL_T *pstGradFgCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_GRAD_FG_T stOpGradFg;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_grad_fg_param_user(pCveHandle, pstFg, pstCurGrad, pstBgGrad, pstGradFg,
                                          pstGradFgCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check GradFg parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpGradFg, 0, sizeof(CVE_OP_GRAD_FG_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpGradFg.stFg, pstFg, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpGradFg.stCurGrad, pstCurGrad, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpGradFg.stBgGrad, pstBgGrad, sizeof(CVE_SRC_IMAGE_T));
    memcpy(&stOpGradFg.stGradFg, pstGradFg, sizeof(CVE_DST_IMAGE_T));
    memcpy(&stOpGradFg.stGradFgCtrl, pstGradFgCtrl, sizeof(CVE_GRAD_FG_CTRL_T));
    stOpGradFg.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_GRAD_FG, &stOpGradFg);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpGradFg.cveHandle;

    return s32Ret;
}

AML_S32 CVE_TOF(CVE_HANDLE *pCveHandle, CVE_SRC_RAW_T *pstSrcRaw, CVE_SRC_RAW_T *pstSrcFpn,
                CVE_SRC_MEM_INFO_T *pstSrcCoef, CVE_SRC_MEM_INFO_T *pstBpc,
                CVE_DST_MEM_INFO_T *pstDtsStatus, CVE_DST_MEM_INFO_T *pstDtsIR,
                CVE_DST_MEM_INFO_T *pstDtsData, CVE_DST_MEM_INFO_T *pstDstHist,
                CVE_TOF_CTRL_T *pstTofCtrl, AML_BOOL_E bInstant)
{
    CVE_OP_TOF_T stOpTof;
    AML_S32 s32Ret = AML_SUCCESS;

    s32Ret = cve_check_tof_user(pCveHandle, pstSrcRaw, pstSrcFpn, pstSrcCoef, pstBpc, pstDtsStatus,
                                pstDtsIR, pstDtsData, pstDstHist, pstTofCtrl);
    if (s32Ret) {
        CVE_ERR_TRACE("check tof parameters failed! error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    memset((void *)&stOpTof, 0, sizeof(CVE_OP_TOF_T));

    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    memcpy(&stOpTof.stSrcRaw, pstSrcRaw, sizeof(CVE_SRC_RAW_T));
    memcpy(&stOpTof.stSrcFpn, pstSrcFpn, sizeof(CVE_SRC_RAW_T));
    memcpy(&stOpTof.stSrcCoef, pstSrcCoef, sizeof(CVE_SRC_MEM_INFO_T));
    memcpy(&stOpTof.stBpc, pstBpc, sizeof(CVE_SRC_MEM_INFO_T));
    memcpy(&stOpTof.stDtsStatus, pstDtsStatus, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpTof.stDtsIR, pstDtsIR, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpTof.stDtsData, pstDtsData, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpTof.stDstHist, pstDstHist, sizeof(CVE_DST_MEM_INFO_T));
    memcpy(&stOpTof.stTofCtrl, pstTofCtrl, sizeof(CVE_TOF_CTRL_T));
    stOpTof.bInstant = bInstant;

    s32Ret = ioctl(g_s32CveFd, CVE_OP_TOF, &stOpTof);
    if (s32Ret) {
        *pCveHandle = AML_INVALID_HANDLE;
    }

    *pCveHandle = stOpTof.cveHandle;

    return s32Ret;
}

AML_S32 CVE_Query(CVE_HANDLE cveHandle, AML_BOOL_E *pbFinish, AML_BOOL_E bBlock)
{
    CVE_OP_QUERY_T stQuery;
    AML_S32 s32Ret = AML_SUCCESS;

    if (bBlock > 1) {
        CVE_ERR_TRACE("block (%d) must be AML_TRUE or AML_FALSE!\n", bBlock);
        return -1608679421;
    }

    if (pbFinish == NULL) {
        CVE_ERR_TRACE("pbFinish is NULL\n");
        return -1608679418;
    }

    if (cveHandle > 0xFFFFFFE) {
        CVE_ERR_TRACE("Error,cveHandle(%d) must be (%d,%d)\n", cveHandle, -1, 0xFFFFFFF);
        return -1608679421;
    }
    s32Ret = cve_check_fd_open();
    if (s32Ret) {
        return s32Ret;
    }

    stQuery.cveHandle = cveHandle;
    stQuery.bBlock = bBlock;
    s32Ret = ioctl(g_s32CveFd, CVE_OP_QUERY, &stQuery);
    if (!s32Ret) {
        *pbFinish = stQuery.bFinish;
    }

    return s32Ret;
}
