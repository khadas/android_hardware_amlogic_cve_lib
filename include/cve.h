// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __CVE_H__
#define __CVE_H__

#include "aml_comm_cve.h"
#include "aml_common.h"
#include "aml_cve.h"
#include "aml_debug.h"

#define AML_MOD_CVE "cve"

#define CVE_EMERG_TRACE(fmt, ...)                                                                  \
    do {                                                                                           \
        AML_EMERG_TRACE("[Func]:%s [Line]:%d [Emerg]:" fmt, __FUNCTION__, __LINE__,                \
                        ##__VA_ARGS__);                                                            \
    } while (0)

#define CVE_ALERT_TRACE(fmt, ...)                                                                  \
    do {                                                                                           \
        AML_ALERT_TRACE("[Func]:%s [Line]:%d [Alert]:" fmt, __FUNCTION__, __LINE__,                \
                        ##__VA_ARGS__);                                                            \
    } while (0)

#define CVE_CRIT_TRACE(fmt, ...)                                                                   \
    do {                                                                                           \
        AML_CRIT_TRACE("[Func]:%s [Line]:%d [Crit]:" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
    } while (0)

#define CVE_ERR_TRACE(fmt, ...)                                                                    \
    do {                                                                                           \
        AML_ERR_TRACE("[Func]:%s [Line]:%d [Error]:" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
    } while (0)

#define CVE_WARN_TRACE(fmt, ...)                                                                   \
    do {                                                                                           \
        AML_WARN_TRACE("[Func]:%s [Line]:%d [Warning]:" fmt, __FUNCTION__, __LINE__,               \
                       ##__VA_ARGS__);                                                             \
    } while (0)

#define CVE_NOTICE_TRACE(fmt, ...)                                                                 \
    do {                                                                                           \
        AML_NOTICE_TRACE("[Func]:%s [Line]:%d [Notice]:" fmt, __FUNCTION__, __LINE__,              \
                         ##__VA_ARGS__);                                                           \
    } while (0)

#define CVE_INFO_TRACE(fmt, ...)                                                                   \
    do {                                                                                           \
        AML_INFO_TRACE("[Func]:%s [Line]:%d [Info]:" fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__);  \
    } while (0)

#define CVE_DEBUG_TRACE(fmt, ...)                                                                  \
    do {                                                                                           \
        AML_DEBUG_TRACE("[Func]:%s [Line]:%d [Debug]:" fmt, __FUNCTION__, __LINE__,                \
                        ##__VA_ARGS__);                                                            \
    } while (0)

#define PLATFORM_CVE_MINOR_BASE 17

#define CVE_ALIGN_DOWN(x, g) (((x) / (g)) * (g))
#define CVE_ALIGN_UP(x, g) ((((x) + (g)-1) / (g)) * (g))
#define CVE_ALIGN 16

#define CVE_REG_ADDR_OFFSET(reg) ((((reg)-CVE_REG_BASE) << 2))

#define HIST_OUTPUT_PROCESS_LUT (1 << 0)
#define NCC_OUTPUT_PROCESS_REG (1 << 1)
#define CCL_OUTPUT_PROCESS_REG (1 << 2)
#define MATCH_BG_MODEL_OUTPUT_PROCESS_REG (1 << 3)
#define UPDATE_BG_MODEL_OUTPUT_PROCESS_REG (1 << 4)
#define LK_OPTICAL_FLOWPYR_OUTPUT_PROCESS_REG (1 << 5)
#define STCORNER_OUTPUT_PROCESS_REG (1 << 6)
#define CANNY_OUTPUT_PROCESS_REG (1 << 7)
#define TOF_OUTPUT_PROCESS_LUT (1 << 8)

#define MAP_INPUT_PROCESS_LUT (1 << 0)
#define EQUALIZE_HIST_INPUT_PROCESS_LUT (1 << 1)
#define TOF_INPUT_PROCESS_LUT (1 << 2)

#define CVE_SRC_MAX 8
#define CVE_DST_MAX 5
#define CVE_LUMA_MULTI_CMD_MAX CVE_LUMA_RECT_MAX

#define IOC_TYPE_CVE 'F'
#define CVE_OP_DMA _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_DMA, CVE_OP_DMA_T)
#define CVE_OP_LUMA_STAT _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_LUMA_STAT, CVE_OP_LUAM_STAT_ARRAY_T)
#define CVE_OP_FILTER _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_FILTER, CVE_OP_FILTER_T)
#define CVE_OP_CSC _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_CSC, CVE_OP_CSC_T)
#define CVE_OP_FILTER_AND_CSC                                                                      \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_FILTER_AND_CSC, CVE_OP_FILTER_AND_CSC_T)
#define CVE_OP_DILATE _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_DILATE, CVE_OP_DILATE_T)
#define CVE_OP_ERODE _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_ERODE, CVE_OP_ERODE_T)
#define CVE_OP_THRESH _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_THRESH, CVE_OP_THRESH_T)
#define CVE_OP_SOBEL _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_SOBEL, CVE_OP_SOBEL_T)
#define CVE_OP_INTEG _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_INTEG, CVE_OP_INTEG_T)
#define CVE_OP_HIST _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_HIST, CVE_OP_HIST_T)
#define CVE_OP_NCC _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_NCC, CVE_OP_NCC_T)
#define CVE_OP_THRESH_S16 _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_THRESH_S16, CVE_OP_THRESH_S16_T)
#define CVE_OP_THRESH_U16 _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_THRESH_U16, CVE_OP_THRESH_U16_T)
#define CVE_OP_ORD_STAT_FILTER                                                                     \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_ORD_STAT_FILTER, CVE_OP_ORD_STAT_FILTER_T)
#define CVE_OP_16BIT_TO_8BIT                                                                       \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_16BIT_TO_8BIT, CVE_OP_16BIT_TO_8BIT_T)
#define CVE_OP_MATCH_BG_MODEL                                                                      \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_MATCH_BG_MODEL, CVE_OP_MATCH_BG_MODEL_T)
#define CVE_OP_UPDATE_BG_MODEL                                                                     \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_UPDATE_BG_MODEL, CVE_OP_UPDATE_BG_MODEL_T)
#define CVE_OP_GRAD_FG _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_GRAD_FG, CVE_OP_GRAD_FG_T)
#define CVE_OP_LBP _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_LBP, CVE_OP_LBP_T)
#define CVE_OP_GMM _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_GMM, CVE_OP_GMM_T)
#define CVE_OP_EQUALIZE_HIST                                                                       \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_EQUALIZE_HIST, CVE_OP_EQUALIZE_HIST_T)
#define CVE_OP_CCL _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_CCL, CVE_OP_CCL_T)
#define CVE_OP_CANNY_HYS_EDGE                                                                      \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_CANNY_HYS_EDGE, CVE_OP_CANNY_HYS_EDGE_T)
#define CVE_OP_ST_CANDI_CORNER                                                                     \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_ST_CANDI_CORNER, CVE_OP_ST_CANDI_CORNER_T)
#define CVE_OP_SAD _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_SAD, CVE_OP_SAD_T)
#define CVE_OP_LK_OPTICAL_FLOW_PYR                                                                 \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_LK_OPTICAL_FLOW_PYR, CVE_OP_LK_OPTICAL_FLOW_PYR_T)
#define CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR                                                           \
    _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR, CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR_T)
#define CVE_OP_MAP _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_MAP, CVE_OP_MAP_T)
#define CVE_OP_NORM_GRAD _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_NORM_GRAD, CVE_OP_NORM_GRAD_T)
#define CVE_OP_AND _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_AND, CVE_OP_AND_T)
#define CVE_OP_OR _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_OR, CVE_OP_OR_T)
#define CVE_OP_XOR _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_XOR, CVE_OP_XOR_T)
#define CVE_OP_SUB _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_SUB, CVE_OP_SUB_T)
#define CVE_OP_ADD _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_ADD, CVE_OP_ADD_T)
#define CVE_OP_MAG_AND_ANG _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_MAG_AND_ANG, CVE_OP_MAG_AND_ANG_T)
#define CVE_OP_TOF _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_TOF, CVE_OP_TOF_T)
#define CVE_OP_QUERY _IOWR(IOC_TYPE_CVE, IOC_NR_CVE_OP_QUERY, CVE_OP_QUERY_T)

#define CVE_CHECK_POINTER(ptr)                                                                     \
    do {                                                                                           \
        if (ptr == NULL) {                                                                         \
            AML_ERR_TRACE("Null Pointer!\n");                                                      \
            return AML_ERR_CVE_NULL_PTR;                                                           \
        }                                                                                          \
    } while (0)

typedef enum {
    IOC_NR_CVE_OP_DMA,
    IOC_NR_CVE_OP_LUMA_STAT,
    IOC_NR_CVE_OP_FILTER,
    IOC_NR_CVE_OP_CSC,
    IOC_NR_CVE_OP_FILTER_AND_CSC,
    IOC_NR_CVE_OP_DILATE,
    IOC_NR_CVE_OP_ERODE,
    IOC_NR_CVE_OP_THRESH,
    IOC_NR_CVE_OP_SOBEL,
    IOC_NR_CVE_OP_INTEG,
    IOC_NR_CVE_OP_HIST,
    IOC_NR_CVE_OP_NCC,
    IOC_NR_CVE_OP_THRESH_S16,
    IOC_NR_CVE_OP_THRESH_U16,
    IOC_NR_CVE_OP_ORD_STAT_FILTER,
    IOC_NR_CVE_OP_16BIT_TO_8BIT,
    IOC_NR_CVE_OP_MATCH_BG_MODEL,
    IOC_NR_CVE_OP_UPDATE_BG_MODEL,
    IOC_NR_CVE_OP_GRAD_FG,
    IOC_NR_CVE_OP_LBP,
    IOC_NR_CVE_OP_GMM,
    IOC_NR_CVE_OP_EQUALIZE_HIST,
    IOC_NR_CVE_OP_CCL,
    IOC_NR_CVE_OP_CANNY_HYS_EDGE,
    IOC_NR_CVE_OP_ST_CANDI_CORNER,
    IOC_NR_CVE_OP_SAD,
    IOC_NR_CVE_OP_LK_OPTICAL_FLOW_PYR,
    IOC_NR_CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR,
    IOC_NR_CVE_OP_MAP,
    IOC_NR_CVE_OP_NORM_GRAD,
    IOC_NR_CVE_OP_AND,
    IOC_NR_CVE_OP_OR,
    IOC_NR_CVE_OP_XOR,
    IOC_NR_CVE_OP_SUB,
    IOC_NR_CVE_OP_ADD,
    IOC_NR_CVE_OP_MAG_AND_ANG,
    IOC_NR_CVE_OP_TOF,
    IOC_NR_CVE_OP_QUERY,
} ioc_nr_cve_op_tpye_e;

typedef struct {
    unsigned int phys_start;
    unsigned long virt_start;
    unsigned int size;
    struct dma_buf *dma_buf;
    struct ion_buffer *ionbuffer;
} cve_ion_buffer_t;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_DATA_T stSrcDATA;
    CVE_DST_DATA_T stDstDATA;
    CVE_DMA_CTRL_T stDmaCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_DMA_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_MEM_INFO_T stDstMem;
    CVE_RECT_U16_T astCveLumaRect[CVE_LUMA_RECT_MAX];
    CVE_LUMA_STAT_ARRAY_CTRL_T stLumaStatArrayCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_LUAM_STAT_ARRAY_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_FILTER_CTRL_T stFilterCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_FILTER_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_CSC_CTRL_T stCscCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_CSC_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_FILTER_AND_CSC_CTRL_T stFilterCscCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_FILTER_AND_CSC_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_DILATE_CTRL_T stDilateCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_DILATE_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_ERODE_CTRL_T stErodeCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_ERODE_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_THRESH_CTRL_T stThreshCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_THRESH_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_EQUALIZE_HIST_CTRL_T stEqualizeHistCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_EQUALIZE_HIST_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_INTEG_CTRL_T stIntegCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_INTEG_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_MEM_INFO_T stDstMem;
    AML_BOOL_E bInstant;
} CVE_OP_HIST_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_DST_MEM_INFO_T stBlob;
    CVE_CCL_CTRL_T stCclCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_CCL_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrc;
    CVE_DST_IMAGE_T stLabel;
    CVE_DST_IMAGE_T stCandiCorner;
    CVE_DST_MEM_INFO_T stCandiCornerPoint;
    CVE_ST_CANDI_CORNER_CTRL_T stStCandiCornerCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_ST_CANDI_CORNER_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage1;
    CVE_SRC_IMAGE_T stSrcImage2;
    CVE_DST_MEM_INFO_T stDstmem;
    CVE_NCC_CTRL_T stNccCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_NCC_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_THRESH_S16_CTRL_T stThreshS16Ctrl;
    AML_BOOL_E bInstant;
} CVE_OP_THRESH_S16_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_THRESH_U16_CTRL_T stThreshU16Ctrl;
    AML_BOOL_E bInstant;
} CVE_OP_THRESH_U16_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_LBP_CTRL_T stLbpCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_LBP_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_ORD_STAT_FILTER_CTRL_T stOrdStatFltCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_ORD_STAT_FILTER_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstImage;
    CVE_16BIT_TO_8BIT_CTRL_T st16BitTo8BitCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_16BIT_TO_8BIT_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stCurImg;
    CVE_SRC_IMAGE_T stPreImg;
    CVE_MEM_INFO_T stBgModel;
    CVE_DST_IMAGE_T stFg;
    CVE_DST_IMAGE_T stBg;
    CVE_DST_IMAGE_T stCurDiffBg;
    CVE_DST_IMAGE_T stFrmDiff;
    CVE_DST_MEM_INFO_T stStatData;
    CVE_MATCH_BG_MODEL_CTRL_T stMatchBgModelCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_MATCH_BG_MODEL_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stCurImg;
    CVE_MEM_INFO_T stBgModel1;
    CVE_MEM_INFO_T stBgModel2;
    CVE_DST_MEM_INFO_T stStatData;
    CVE_UPDATE_BG_MODEL_CTRL_T stUpdateBgModelCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_UPDATE_BG_MODEL_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stFg;
    CVE_SRC_IMAGE_T stCurGrad;
    CVE_SRC_IMAGE_T stBgGrad;
    CVE_DST_IMAGE_T stGradFg;
    CVE_GRAD_FG_CTRL_T stGradFgCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_GRAD_FG_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_SRC_IMAGE_T stFactor;
    CVE_DST_IMAGE_T stFg;
    CVE_DST_IMAGE_T stBg;
    CVE_MEM_INFO_T stModel;
    CVE_GMM_CTRL_T stGmmCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_GMM_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stEdge;
    CVE_DST_MEM_INFO_T stStack;
    CVE_CANNY_HYS_EDGE_CTRL_T stCannyHysEdgeCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_CANNY_HYS_EDGE_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage1;
    CVE_SRC_IMAGE_T stSrcImage2;
    CVE_DST_IMAGE_T stSad;
    CVE_DST_IMAGE_T stThr;
    CVE_SAD_CTRL_T stSadCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_SAD_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T astSrcPrevPyr[4];
    CVE_SRC_IMAGE_T astSrcNextPyr[4];
    CVE_SRC_MEM_INFO_T stPrevPts;
    CVE_MEM_INFO_T stNextPts;
    CVE_DST_MEM_INFO_T stStatus;
    CVE_DST_MEM_INFO_T stErr;
    CVE_LK_OPTICAL_FLOW_PYR_CTRL_T stLkOptiFlowPyrCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_LK_OPTICAL_FLOW_PYR_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcPyr;
    CVE_DST_IMAGE_T astDstPyr[4];
    CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T stLkBuildOptiFlowPyrCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_BUILD_LK_OPTICAL_FLOW_PYR_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_SRC_MEM_INFO_T stMap;
    CVE_DST_IMAGE_T stDstImage;
    CVE_MAP_CTRL_T stMapCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_MAP_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstMag;
    CVE_DST_IMAGE_T stDstAng;
    CVE_MAG_AND_ANG_CTRL_T stMagAndAngCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_MAG_AND_ANG_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage1;
    CVE_SRC_IMAGE_T stSrcImage2;
    CVE_DST_IMAGE_T stDst;
    AML_BOOL_E bInstant;
} CVE_OP_AND_T;

typedef CVE_OP_AND_T CVE_OP_OR_T;
typedef CVE_OP_AND_T CVE_OP_XOR_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage1;
    CVE_SRC_IMAGE_T stSrcImage2;
    CVE_DST_IMAGE_T stDst;
    CVE_SUB_CTRL_T stSubCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_SUB_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage1;
    CVE_SRC_IMAGE_T stSrcImage2;
    CVE_DST_IMAGE_T stDst;
    CVE_ADD_CTRL_T stAddCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_ADD_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstH;
    CVE_DST_IMAGE_T stDstV;
    CVE_DST_IMAGE_T stDstHV;
    CVE_NORM_GRAD_CTRL_T stNormGradCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_NORM_GRAD_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_IMAGE_T stSrcImage;
    CVE_DST_IMAGE_T stDstH;
    CVE_DST_IMAGE_T stDstV;
    CVE_SOBEL_CTRL_T stSobelCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_SOBEL_T;

typedef struct {
    CVE_HANDLE cveHandle;
    CVE_SRC_RAW_T stSrcRaw;
    CVE_SRC_RAW_T stSrcFpn;
    CVE_SRC_MEM_INFO_T stSrcCoef;
    CVE_SRC_MEM_INFO_T stBpc;
    CVE_DST_MEM_INFO_T stDtsStatus;
    CVE_DST_MEM_INFO_T stDtsIR;
    CVE_DST_MEM_INFO_T stDtsData;
    CVE_DST_MEM_INFO_T stDstHist;
    CVE_TOF_CTRL_T stTofCtrl;
    AML_BOOL_E bInstant;
} CVE_OP_TOF_T;

typedef struct {
    CVE_HANDLE cveHandle;
    AML_BOOL_E bBlock;
    AML_BOOL_E bFinish;
} CVE_OP_QUERY_T;

#endif /* __CVE_H__ */
