/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __AML_CVE_H__
#define __AML_CVE_H__

#include "aml_comm_cve.h"
#include "aml_common.h"

#define CVE_LUMA_RECT_MAX 64
#define CVE_HIST_NUM 256
#define CVE_MAP_NUM 256
#define CVE_MAX_REGION_NUM 384
#define CVE_ST_MAX_CORNER_NUM 500

typedef enum {
    CVE_DMA_MODE_DIRECT_COPY = 0x0,
    CVE_DMA_MODE_INTERVAL_COPY = 0x1,
    CVE_DMA_MODE_SET_3BYTE = 0x2,
    CVE_DMA_MODE_SET_8BYTE = 0x3,
    CVE_DMA_MODE_NOT = 0x4,
    CVE_DMA_MODE_BUTT
} CVE_DMA_MODE_E;

typedef struct {
    CVE_DMA_MODE_E enMode;
    AML_U64 u64Val;
    AML_U8 u8HorSegSize;
    AML_U8 u8ElemSize;
    AML_U8 u8VerSegRows;
} CVE_DMA_CTRL_T;

typedef enum {
    CVE_LUMA_STAT_MODE_STEP_0 = 0x0,
    CVE_LUMA_STAT_MODE_STEP_1 = 0x1,
    CVE_LUMA_STAT_MODE_STEP_2 = 0x2,
    CVE_LUMA_STAT_MODE_STEP_3 = 0x3,

    CVE_LUMA_STAT_MODE_BUTT
} CVE_LUMA_STAT_MODE_E;

typedef struct {
    CVE_LUMA_STAT_MODE_E enMode;
    AML_U8 u8MaxLumaRect;
} CVE_LUMA_STAT_ARRAY_CTRL_T;

typedef struct {
    AML_S8 as8Mask[25];
    AML_U8 u8Norm;
} CVE_FILTER_CTRL_T;

typedef enum {
    CVE_CSC_MODE_PIC_BT601_YUV2RGB = 0x0,
    CVE_CSC_MODE_PIC_BT601_YUV2BGR = 0x1,
    CVE_CSC_MODE_PIC_BT601_YUV2HSV = 0x2,
    CVE_CSC_MODE_PIC_BT601_YUV2LAB = 0x3,
    CVE_CSC_MODE_PIC_BT601_RGB2YUV = 0x4,
    CVE_CSC_MODE_PIC_BT601_BGR2YUV = 0x5,
    CVE_CSC_MODE_PIC_BT601_RGB2HSV = 0x6,
    CVE_CSC_MODE_PIC_BT601_RGB2LAB = 0x7,
    CVE_CSC_MODE_PIC_BT601_RGB2BGR = 0x8,
    CVE_CSC_MODE_PIC_BT601_BGR2RGB = 0x9,
    CVE_CSC_MODE_BUTT
} CVE_CSC_MODE_E;

typedef struct {
    CVE_CSC_MODE_E enMode;
} CVE_CSC_CTRL_T;

typedef struct {
    CVE_CSC_MODE_E enMode;
    AML_S8 as8Mask[25];
    AML_U8 u8Norm;
} CVE_FILTER_AND_CSC_CTRL_T;

typedef enum {
    CVE_SOBEL_OUT_CTRL_BOTH = 0x0,
    CVE_SOBEL_OUT_CTRL_HOR = 0x1,
    CVE_SOBEL_OUT_CTRL_VER = 0x2,
    CVE_SOBEL_OUT_CTRL_BUTT
} CVE_SOBEL_OUT_CTRL_E;

typedef struct {
    CVE_SOBEL_OUT_CTRL_E enOutCtrl;
    AML_S8 as8Mask[25];
} CVE_SOBEL_CTRL_T;

typedef enum {
    CVE_MAG_AND_ANG_OUT_CTRL_MAG = 0x0,
    CVE_MAG_AND_ANG_OUT_CTRL_MAG_AND_ANG = 0x1,
    CVE_MAG_AND_ANG_OUT_CTRL_HOG = 0x2,
    CVE_MAG_AND_ANG_OUT_CTRL_BUTT
} CVE_MAG_AND_ANG_OUT_CTRL_E;

typedef struct {
    CVE_MAG_AND_ANG_OUT_CTRL_E enOutCtrl;
    AML_U16 u16Thr;
    AML_S8 as8Mask[25];
} CVE_MAG_AND_ANG_CTRL_T;

typedef struct {
    AML_U8 au8Mask[25];
} CVE_DILATE_CTRL_T;

typedef struct {
    AML_U8 au8Mask[25];
} CVE_ERODE_CTRL_T;

typedef enum {
    CVE_THRESH_MODE_BINARY = 0x0,
    CVE_THRESH_MODE_TRUNC = 0x1,
    CVE_THRESH_MODE_TO_MINVAL = 0x2,
    CVE_THRESH_MODE_MIN_MID_MAX = 0x3,
    CVE_THRESH_MODE_ORI_MID_MAX = 0x4,
    CVE_THRESH_MODE_MIN_MID_ORI = 0x5,
    CVE_THRESH_MODE_MIN_ORI_MAX = 0x6,
    CVE_THRESH_MODE_ORI_MID_ORI = 0x7,
    CVE_THRESH_MODE_BUTT
} CVE_THRESH_MODE_E;

typedef struct {
    CVE_THRESH_MODE_E enMode;
    AML_U8 u8LowThr;
    AML_U8 u8HighThr;
    AML_U8 u8MinVal;
    AML_U8 u8MidVal;
    AML_U8 u8MaxVal;
} CVE_THRESH_CTRL_T;

typedef enum {
    CVE_SUB_MODE_ABS = 0x0,
    CVE_SUB_MODE_SHIFT = 0x1,
    CVE_SUB_MODE_THRESH = 0x2,
    CVE_SUB_MODE_BUTT
} CVE_SUB_MODE_E;

typedef struct {
    CVE_SUB_MODE_E enMode;
    AML_U16 u16ThreshRatio;
} CVE_SUB_CTRL_T;

typedef enum {
    CVE_INTEG_OUT_CTRL_COMBINE = 0x0,
    CVE_INTEG_OUT_CTRL_TUM = 0x1,
    CVE_INTEG_OUT_CTRL_TQSUM = 0x2,
    CVE_INTEG_OUT_CTRL_BUTT
} CVE_INTEG_OUT_CTRL_E;

typedef struct {
    CVE_INTEG_OUT_CTRL_E enOutCtrl;
} CVE_INTEG_CTRL_T;

typedef enum {
    CVE_THRESH_S16_MODE_S16_TO_S8_MIN_MID_MAX = 0x0,
    CVE_THRESH_S16_MODE_S16_TO_S8_MIN_ORI_MAX = 0x1,
    CVE_THRESH_S16_MODE_S16_TO_U8_MIN_MID_MAX = 0x2,
    CVE_THRESH_S16_MODE_S16_TO_U8_MIN_ORI_MAX = 0x3,
    CVE_THRESH_S16_MODE_BUTT
} CVE_THRESH_S16_MODE_E;

typedef struct {
    CVE_THRESH_S16_MODE_E enMode;
    AML_S16 s16LowThr;
    AML_S16 s16HighThr;
    CVE_8BIT_U un8MinVal;
    CVE_8BIT_U un8MidVal;
    CVE_8BIT_U un8MaxVal;
} CVE_THRESH_S16_CTRL_T;

typedef enum {
    CVE_THRESH_U16_MODE_U16_TO_U8_MIN_MID_MAX = 0x0,
    CVE_THRESH_U16_MODE_U16_TO_U8_MIN_ORI_MAX = 0x1,

    CVE_THRESH_U16_MODE_BUTT
} CVE_THRESH_U16_MODE_E;

typedef struct {
    CVE_THRESH_U16_MODE_E enMode;
    AML_U16 u16LowThr;
    AML_U16 u16HighThr;
    AML_U8 u8MinVal;
    AML_U8 u8MidVal;
    AML_U8 u8MaxVal;
} CVE_THRESH_U16_CTRL_T;

typedef enum {
    CVE_16BIT_TO_8BIT_MODE_S16_TO_S8 = 0x0,
    CVE_16BIT_TO_8BIT_MODE_S16_TO_U8_ABS = 0x1,
    CVE_16BIT_TO_8BIT_MODE_S16_TO_U8_BIAS = 0x2,
    CVE_16BIT_TO_8BIT_MODE_U16_TO_U8 = 0x3,

    CVE_16BIT_TO_8BIT_MODE_BUTT
} CVE_16BIT_TO_8BIT_MODE_E;

typedef struct {
    CVE_16BIT_TO_8BIT_MODE_E enMode;
    AML_U16 u16Denominator;
    AML_U8 u8Numerator;
    AML_S8 s8Bias;
} CVE_16BIT_TO_8BIT_CTRL_T;

typedef enum {
    CVE_ORD_STAT_FILTER_MODE_MIN = 0x0,
    CVE_ORD_STAT_FILTER_MODE_MEDIAN = 0x1,
    CVE_ORD_STAT_FILTER_MODE_MAX = 0x2,

    CVE_ORD_STAT_FILTER_MODE_BUTT
} CVE_ORD_STAT_FILTER_MODE_E;

typedef struct {
    CVE_ORD_STAT_FILTER_MODE_E enMode;

} CVE_ORD_STAT_FILTER_CTRL_T;

typedef enum {
    CVE_MAP_MODE_U8 = 0x0,
    CVE_MAP_MODE_S16 = 0x1,
    CVE_MAP_MODE_U16 = 0x2,

    CVE_MAP_MODE_BUTT
} CVE_MAP_MODE_E;

typedef struct {
    CVE_MAP_MODE_E enMode;
} CVE_MAP_CTRL_T;

typedef struct {
    AML_U8 au8Map[CVE_MAP_NUM];
} CVE_MAP_U8BIT_LUT_MEM_T;

typedef struct {
    AML_U16 au16Map[CVE_MAP_NUM];
} CVE_MAP_U16BIT_LUT_MEM_T;

typedef struct {
    AML_S16 as16Map[CVE_MAP_NUM];
} CVE_MAP_S16BIT_LUT_MEM_T;

typedef struct {
    AML_U32 au32Hist[CVE_HIST_NUM];
    AML_U8 au8Map[CVE_MAP_NUM];
} CVE_EQUALIZE_HIST_CTRL_MEM_T;

typedef struct {
    CVE_MEM_INFO_T stMem;
} CVE_EQUALIZE_HIST_CTRL_T;

typedef struct {
    AML_U0Q16 u0q16X;
    AML_U0Q16 u0q16Y;
} CVE_ADD_CTRL_T;

typedef struct {
    AML_U64 u64Numerator;
    AML_U64 u64QuadSum1;
    AML_U64 u64QuadSum2;
    AML_U8 u8Reserved[8];
} CVE_NCC_DST_MEM_T;

typedef struct {
    AML_U32 u32Area;
    AML_U16 u16Left;
    AML_U16 u16Right;
    AML_U16 u16Top;
    AML_U16 u16Bottom;
    AML_U16 u16label;
} CVE_REGION_T;

typedef struct {
    CVE_REGION_T astRegion[CVE_MAX_REGION_NUM];
    AML_U16 u16RegionNum;
} CVE_CCBLOB_T;

typedef enum {
    CVE_NCC_MODE_COM = 0x0,
    CVE_NCC_MODE_SIMILAR = 0x1,

    CVE_NCC_MODE_BUTT
} CVE_NCC_MODE_E;

typedef struct {
    CVE_NCC_MODE_E enMode;
    AML_U8 u8Src1Offset;
    AML_U8 u8Src0Offset;
} CVE_NCC_CTRL_T;

typedef enum {
    CVE_CCL_INPUT_DATA_MODE_U8 = 0x0,
    CVE_CCL_INPUT_DATA_MODE_U1 = 0x1,

    CVE_CCL_INPUT_DATA_MODE_BUTT
} CVE_CCL_INPUT_DATA_MODE_E;

typedef struct {
    CVE_CCL_INPUT_DATA_MODE_E enInputDataMode;
} CVE_CCL_CTRL_T;

typedef enum {
    CVE_GMM_OUTPUT_MODE_FG = 0x0,
    CVE_GMM_OUTPUT_MODE_FG_AND_BG = 0x1,

    CVE_GMM_OUTPUT_MODE_BUTT
} CVE_GMM_OUTPUT_MODE_E;

typedef enum {
    CVE_GMM_SNS_FACTOR_MODE_GLB = 0x0,
    CVE_GMM_SNS_FACTOR_MODE_PIX = 0x1,

    CVE_GMM_SNS_FACTOR_MODE_BUTT
} CVE_GMM_SNS_FACTOR_MODE_E;

typedef enum {
    CVE_GMM_DURATION_UPDATE_FACTOR_MODE_GLB = 0x0,
    CVE_GMM_DURATION_UPDATE_FACTOR_MODE_PIX = 0x1,

    CVE_GMM_DURATION_UPDATE_FACTOR_MODE_BUTT
} CVE_GMM_DURATION_UPDATE_FACTOR_MODE_E;

typedef enum {
    CVE_GMM_DOWN_SCALE_MODE_DISABLE = 0x0,
    CVE_GMM_DOWN_SCALE_MODE_2X2 = 0x1,
    CVE_GMM_DOWN_SCALE_MODE_4X4 = 0x2,

    CVE_GMM_DOWN_SCALE_MODE_BUTT
} CVE_GMM_DOWN_SCALE_MODE_E;

typedef enum {
    CVE_GMM_OUTPUT_DATA_MODE_U8 = 0x0,
    CVE_GMM_OUTPUT_DATA_MODE_U1 = 0x1,

    CVE_GMM_OUTPUT_DATA_MODE_BUTT
} CVE_GMM_OUTPUT_DATA_MODE_E;

typedef struct {
    CVE_GMM_OUTPUT_MODE_E enOutputMode;
    CVE_GMM_SNS_FACTOR_MODE_E enSnsFactorMode;
    CVE_GMM_DURATION_UPDATE_FACTOR_MODE_E
    enDurationUpdateFactorMode;
    CVE_GMM_DOWN_SCALE_MODE_E enDownScaleMode;
    CVE_GMM_OUTPUT_DATA_MODE_E enOutputDataMode;
    AML_U10Q6 u10q6NoiseVar;
    AML_U10Q6 u10q6MaxVar;
    AML_U10Q6 u10q6MinVar;
    AML_U0Q16 u0q16LearnRate;
    AML_U0Q16 u0q16InitWeight;
    AML_U0Q16 u0q16WeightThr;
    AML_U8 u8ModelNum;
    AML_U3Q7 u3q7SigmaScale;
    AML_BOOL_E enFastLearn;
} CVE_GMM_CTRL_T;

typedef struct {
    CVE_MEM_INFO_T stMem;
    AML_BOOL_E bGauss;
    AML_U16 u16LowThr;
    AML_U16 u16HighThr;
    AML_S8 as8Mask[25];
} CVE_CANNY_HYS_EDGE_CTRL_T;

typedef enum {
    CVE_CANNY_EDGE_OUTPUT_DATA_MODE_U8 = 0x0,
    CVE_CANNY_EDGE_OUTPUT_DATA_MODE_U1 = 0x1,

    CVE_CANNY_EDGE_OUTPUT_DATA_MODE_BUTT
} CVE_CANNY_EDGE_OUTPUT_DATA_MODE_E;

typedef struct {
    CVE_CANNY_EDGE_OUTPUT_DATA_MODE_E enOutputDataMode;
    AML_U32 u32CannyCount;
} CVE_CANNY_EDGE_CTRL_T;

typedef enum {
    CVE_LBP_CMP_MODE_NORMAL = 0x0,
    CVE_LBP_CMP_MODE_ABS = 0x1,

    CVE_LBP_CMP_MODE_BUTT
} CVE_LBP_CMP_MODE_E;

typedef struct {
    CVE_LBP_CMP_MODE_E enMode;
    CVE_8BIT_U un8BitThr;
} CVE_LBP_CTRL_T;

typedef enum {
    CVE_NORM_GRAD_OUT_CTRL_HOR_AND_VER = 0x0,
    CVE_NORM_GRAD_OUT_CTRL_HOR = 0x1,
    CVE_NORM_GRAD_OUT_CTRL_VER = 0x2,
    CVE_NORM_GRAD_OUT_CTRL_COMBINE = 0x3,

    CVE_NORM_GRAD_OUT_CTRL_BUTT
} CVE_NORM_GRAD_OUT_CTRL_E;

typedef struct {
    CVE_NORM_GRAD_OUT_CTRL_E enOutCtrl;
    AML_S8 as8Mask[25];
    AML_U8 u8Norm;
} CVE_NORM_GRAD_CTRL_T;

typedef enum {
    CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_NONE = 0,
    CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_ERR = 1,
    CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_BOTH = 2,

    CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_BUTT
} CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_E;

typedef struct {
    AML_U8 u8MaxLevel;
} CVE_BUILD_LK_OPTICAL_FLOW_PYR_CTRL_T;

typedef struct {
    CVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_E enOutMode;
    AML_BOOL_E bUseInitFlow;
    AML_U16 u16PtsNum;
    AML_U8 u8MaxLevel;
    AML_U8 u8IterCnt;
    AML_U0Q8 u0q8Eps;
} CVE_LK_OPTICAL_FLOW_PYR_CTRL_T;

typedef enum {
    CVE_ST_CANDI_CORNER_OUTPUT_DATA_MODE_U8 = 0x0,
    CVE_ST_CANDI_CORNER_OUTPUT_DATA_MODE_U1 = 0x1,

    CVE_ST_CANDI_CORNER_OUTPUT_DATA_MODE_BUTT
} CVE_ST_CANDI_CORNER_OUTPUT_DATA_MODE_E;

typedef struct {
    CVE_ST_CANDI_CORNER_OUTPUT_DATA_MODE_E enOutputDataMode;
    CVE_MEM_INFO_T stMem;
} CVE_ST_CANDI_CORNER_CTRL_T;

typedef struct {
    CVE_POINT_U16_T astCorner[CVE_ST_MAX_CORNER_NUM];
    AML_U16 u16CornerNum;
} CVE_ST_CORNER_INFO_T;

typedef struct {
    AML_U32 u32CornerNum;
    AML_U16 u32MaxCornerNum;
    AML_U16 u32MinDist;
} CVE_ST_CORNER_CTRL_T;

typedef enum {
    CVE_GRAD_FG_MODE_DIRECT = 0x0,
    CVE_GRAD_FG_MODE_THR = 0x1,
    CVE_GRAD_FG_MODE_THR_FG = 0x2,
    CVE_GRAD_FG_MODE_FG = 0x3,

    CVE_GRAD_FG_MODE_BUTT
} CVE_GRAD_FG_MODE_E;

typedef struct {
    CVE_GRAD_FG_MODE_E enMode;
    AML_U8 u8MinMagDiff;
} CVE_GRAD_FG_CTRL_T;

typedef struct {
    AML_U8Q4F4 u8q4f4Mean;
    AML_U16 u16StartTime;
    AML_U16 u16SumAccessTime;
    AML_U16 u16ShortKeepTime;
    AML_U8 u8ChgCond;
    AML_U8 u8PotenBgLife;
} CVE_CANDI_BG_PIX_T;

typedef struct {
    AML_U8Q4F4 u8q4f4Mean;
    AML_U16 u16AccTime;
    AML_U8 u8PreGray;
    AML_U5Q3 u5q3DiffThr;
    AML_U8 u8AccFlag;
    AML_U8 u8BgGray[3];
} CVE_WORK_BG_PIX_T;

typedef struct {
    AML_U8 u8WorkBgLife[3];
    AML_U8 u8CandiBgLife;
} CVE_BG_LIFE_T;

typedef struct {
    CVE_WORK_BG_PIX_T stWorkBgPixel;
    CVE_CANDI_BG_PIX_T stCandiPixel;
    CVE_BG_LIFE_T stBgLife;
} CVE_BG_MODEL_PIX_T;

typedef struct {
    AML_U32 u32PixNum;
    AML_U32 u32SumLum;
} CVE_FG_STAT_DATA_T;

typedef struct {
    AML_U32 u32PixNum;
    AML_U32 u32SumLum;
} CVE_BG_STAT_DATA_T;

typedef enum {
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_FG = 0x0,
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_FG_AND_BG = 0x1,
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_FG_AND_BG_AND_CURDIFFBG = 0x2,
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_ALL = 0x3,
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_BUTT
} CVE_MATCH_BG_MODEL_OUTPUT_MODE_E;

typedef enum {
    CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_DISABLE = 0x0,
    CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_2X2 = 0x1,
    CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_4X4 = 0x2,

    CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_BUTT
} CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_E;

typedef struct {
    CVE_MATCH_BG_MODEL_OUTPUT_MODE_E enOutputMode;
    CVE_MATCH_BG_MODEL_DOWN_SCALE_MODE_E enDownScaleMode;
    AML_U8Q4 u8q4DistThr;
    AML_U8 u8GrayThr;
} CVE_MATCH_BG_MODEL_CTRL_T;

typedef enum {
    CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_DISABLE = 0x0,
    CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_2X2 = 0x1,
    CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_4X4 = 0x2,

    CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_BUTT
} CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_E;

typedef struct {
    CVE_UPDATE_BG_MODEL_DOWN_SCALE_MODE_E enDownScaleMode;
    AML_U16 u16DelThr;
    AML_U16 u16FrqThr;
    AML_U16 u16IntervalThr;
    AML_U0Q16 u0q16LearnRate;

} CVE_UPDATE_BG_MODEL_CTRL_T;

typedef enum {
    CVE_ANN_MLP_ACTIV_FUNC_IDENTITY = 0x0,
    CVE_ANN_MLP_ACTIV_FUNC_SIGMOID_SYM = 0x1,
    CVE_ANN_MLP_ACTIV_FUNC_GAUSSIAN = 0x2,

    CVE_ANN_MLP_ACTIV_FUNC_BUTT
} CVE_ANN_MLP_ACTIV_FUNC_E;
typedef enum {
    CVE_ANN_MLP_ACCURATE_SRC16_WGT16 = 0x0,
    CVE_ANN_MLP_ACCURATE_SRC14_WGT20 = 0x1,

    CVE_ANN_MLP_ACCURATE_BUTT
} CVE_ANN_MLP_ACCURATE_E;

typedef struct {
    CVE_ANN_MLP_ACTIV_FUNC_E enActivFunc;
    CVE_ANN_MLP_ACCURATE_E enAccurate;
    CVE_MEM_INFO_T stWeight;
    AML_U32 u32TotalWeightSize;

    AML_U16 au16LayerCount[8];
    AML_U16 u16MaxCount;
    AML_U8 u8LayerNum;
    AML_U8 u8Reserved;
} CVE_ANN_MLP_MODEL_T;

typedef enum {
    CVE_SVM_TYPE_C_SVC = 0x0,
    CVE_SVM_TYPE_NU_SVC = 0x1,

    CVE_SVM_TYPE_BUTT
} CVE_SVM_TYPE_E;

typedef enum {
    CVE_SVM_KERNEL_TYPE_LINEAR = 0x0,
    CVE_SVM_KERNEL_TYPE_POLY = 0x1,
    CVE_SVM_KERNEL_TYPE_RBF = 0x2,
    CVE_SVM_KERNEL_TYPE_SIGMOID = 0x3,

    CVE_SVM_KERNEL_TYPE_BUTT
} CVE_SVM_KERNEL_TYPE_E;

typedef struct {
    CVE_SVM_TYPE_E enType;
    CVE_SVM_KERNEL_TYPE_E enKernelType;

    CVE_MEM_INFO_T stSv;
    CVE_MEM_INFO_T stDf;
    AML_U32 u32TotalDfSize;

    AML_U16 u16FeatureDim;
    AML_U16 u16SvTotal;
    AML_U8 u8ClassCount;
} CVE_SVM_MODEL_T;

typedef enum {
    CVE_SAD_MODE_MB_4X4 = 0x0,
    CVE_SAD_MODE_MB_8X8 = 0x1,
    CVE_SAD_MODE_MB_16X16 = 0x2,

    CVE_SAD_MODE_BUTT
} CVE_SAD_MODE_E;

typedef struct {
    CVE_SAD_MODE_E enMode;
    AML_U16 u16Thr;
    AML_U8 u8MinVal;
    AML_U8 u8MaxVal;
} CVE_SAD_CTRL_T;

typedef enum {
    CVE_RESIZE_MODE_LINEAR = 0x0,

    CVE_RESIZE_MODE_BUTT
} CVE_RESIZE_MODE_E;

typedef struct {
    CVE_RESIZE_MODE_E enMode;
    CVE_MEM_INFO_T stMem;
    AML_U16 u16Num;
} CVE_RESIZE_CTRL_T;

typedef enum {
    CVE_CNN_ACTIV_FUNC_NONE = 0x0,
    CVE_CNN_ACTIV_FUNC_RELU = 0x1,
    CVE_CNN_ACTIV_FUNC_SIGMOID = 0x2,

    CVE_CNN_ACTIV_FUNC_BUTT
} CVE_CNN_ACTIV_FUNC_E;

typedef enum {
    CVE_CNN_POOLING_NONE = 0x0,
    CVE_CNN_POOLING_MAX = 0x1,
    CVE_CNN_POOLING_AVG = 0x2,

    CVE_CNN_POOLING_BUTT
} CVE_CNN_POOLING_E;

typedef struct {
    CVE_CNN_ACTIV_FUNC_E enActivFunc;
    CVE_CNN_POOLING_E enPooling;

    AML_U8 u8FeatureMapNum;
    AML_U8 u8KernelSize;
    AML_U8 u8ConvStep;

    AML_U8 u8PoolSize;
    AML_U8 u8PoolStep;
    AML_U8 u8Reserved[3];

} CVE_CNN_CONV_POOLING_T;

typedef struct {
    AML_U16 au16LayerCnt[8];
    AML_U16 u16MaxCnt;
    AML_U8 u8LayerNum;
    AML_U8 u8Reserved;
} CVE_CNN_FULL_CONNECT_T;

typedef struct {
    CVE_CNN_CONV_POOLING_T astConvPool[8];
    CVE_CNN_FULL_CONNECT_T stFullConnect;
    CVE_MEM_INFO_T stConvKernelBias;
    AML_U32 u32ConvKernelBiasSize;
    CVE_MEM_INFO_T stFCLWgtBias;
    AML_U32 u32FCLWgtBiasSize;
    AML_U32 u32TotalMemSize;
    CVE_IMAGE_TYPE_E enType;
    AML_U32 u32Width;
    AML_U32 u32Height;
    AML_U16 u16ClassCount;
    AML_U8 u8ConvPoolLayerNum;
    AML_U8 u8Reserved;
} CVE_CNN_MODEL_T;

typedef struct {
    CVE_MEM_INFO_T stMem;
    AML_U32 u32Num;
} CVE_CNN_CTRL_T;

typedef struct {
    AML_S32 s32ClassIdx;
    AML_S32 s32Confidence;
} CVE_CNN_RESULT_T;

typedef enum {
    CVE_PERSP_TRANS_ALG_MODE_NR_SIM = 0x0,
    CVE_PERSP_TRANS_ALG_MODE_SIM = 0x1,
    CVE_PERSP_TRANS_ALG_MODE_AFFINE = 0x2,

    CVE_PERSP_TRANS_ALG_MODE_BUTT
} CVE_PERSP_TRANS_ALG_MODE_E;

typedef enum {
    CVE_PERSP_TRANS_CSC_MODE_NONE = 0x0,
    CVE_PERSP_TRANS_CSC_MODE_VIDEO_BT601_YUV2RGB = 0x1,
    CVE_PERSP_TRANS_CSC_MODE_VIDEO_BT709_YUV2RGB = 0x2,
    CVE_PERSP_TRANS_CSC_MODE_PIC_BT601_YUV2RGB = 0x3,
    CVE_PERSP_TRANS_CSC_MODE_PIC_BT709_YUV2RGB = 0x4,

    CVE_PERSP_TRANS_CSC_MODE_BUTT
} CVE_PERSP_TRANS_CSC_MODE_E;

typedef struct {
    CVE_PERSP_TRANS_ALG_MODE_E enAlgMode;
    CVE_PERSP_TRANS_CSC_MODE_E enCscMode;
    AML_U16 u16RoiNum;
    AML_U16 u16PointPairNum;
} CVE_PERSP_TRANS_CTRL_T;

typedef enum {
    CVE_TOF_FPN_MODE_BYPASS = 0x0,
    CVE_TOF_FPN_MODE_FPN = 0x1,
    CVE_TOF_FPN_MODE_FD = 0x2,

    CVE_TOF_FPN_MODE_BUTT
} CVE_TOF_FPN_MODE_E;

typedef struct {
    CVE_RAW_MODE_E enRawMode;
    CVE_TOF_FPN_MODE_E enFpnMode;
    AML_BOOL_E bRawShift;
    AML_BOOL_E bBypass;
    AML_BOOL_E bSpa1En;
    AML_BOOL_E bSpa2En;
    AML_S21Q3 as32PCoef[5];
    AML_S16 as16TCoef1[4];
    AML_U16 u16HistXstart;
    AML_U16 u16HistYstart;
    AML_U16 u16HistXend;
    AML_U16 u16HistYend;
    AML_U16 u16Q1HighThr;
    AML_U16 u16Q23HighThr;
    AML_U16 u16IRHighThr;
    AML_U16 u16IRLowThr;
    AML_U16 u16DepthMax;
    AML_U16 u16DepthMin;
    AML_U8 u8SpaNorm;
    AML_U8 u8BadPointNum;
    AML_S8 s8IntTemp;
    AML_S8 s8ExtTemp;
} CVE_TOF_CTRL_T;

#endif /* __AML_CVE_H__ */
