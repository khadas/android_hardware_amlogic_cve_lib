/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#ifndef __SAMPLE_COMM_CVE_H__
#define __SAMPLE_COMM_CVE_H__

#include "aml_comm_cve.h"
#include "cve_alloc.h"
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define REG_SRC_ADDR 0x1000000
#define REG_SRC_ADDR1 0x2000000
#define REG_SRC_ADDR2 0x3000000
#define REG_SRC_ADDR3 0x4000000
#define REG_SRC_ADDR4 0x5000000
#define REG_SRC_ADDR5 0x6000000
#define REG_SRC_ADDR6 0x7000000
#define REG_SRC_ADDR7 0x8000000

#define REG_DST_ADDR 0xA000000
#define REG_DST_ADDR1 0xB000000
#define REG_DST_ADDR2 0xC000000
#define REG_DST_ADDR3 0xD000000
#define REG_DST_ADDR4 0xE000000
#define REG_DST_ADDR5 0xF000000

#define VIDEO_WIDTH 352
#define VIDEO_HEIGHT 288
#define CVE_ALIGN 16
#define CVE_CHAR_CALW 8
#define CVE_CHAR_CALH 8
#define CVE_CHAR_NUM (CVE_CHAR_CALW * CVE_CHAR_CALH)
#define CVE_FILE_NAME_LEN 256
#define CVE_RECT_NUM 64
#define VPSS_CHN_NUM 2

#define CVE_PMZ_FREE(dmafd, vir)                                                                   \
    do {                                                                                           \
        if ((0 != (dmafd)) && (0 != (vir))) {                                                      \
            cve_free_ion((dmafd), (AML_VOID *)(AML_UL)(vir));                                      \
            (dmafd) = 0;                                                                           \
            (vir) = 0;                                                                             \
        }                                                                                          \
    } while (0)

#define CVE_CLOSE_FILE(fp)                                                                         \
    do {                                                                                           \
        if (NULL != (fp)) {                                                                        \
            fclose((fp));                                                                          \
            (fp) = NULL;                                                                           \
        }                                                                                          \
    } while (0)

#define CVE_OPEN_FILE(fp, fname, fmode)                                                            \
    do {                                                                                           \
        fp = fopen((fname), fmode);                                                                \
        if (NULL == (fp)) {                                                                        \
            TEST_PRT("[ERROR] open file error.\n");                                                \
            return AML_FAILURE;                                                                    \
        }                                                                                          \
    } while (0)

#define TEST_PRT(fmt...)                                                                           \
    do {                                                                                           \
        printf("[%s][%d]: ", __FUNCTION__, __LINE__);                                              \
        printf(fmt);                                                                               \
    } while (0)

typedef struct {
    AML_S32 s32X;
    AML_S32 s32Y;
} POINT_T;

typedef struct {
    POINT_T astPoint[4];
} SAMPLE_IVE_RECT_T;

typedef struct {
    AML_U16 u16Num;
    SAMPLE_IVE_RECT_T astRect[CVE_RECT_NUM];
} SAMPLE_RECT_ARRAY_T;

typedef struct {
    AML_U16 label;
    AML_U16 area_l;
    AML_U16 area_h;
    AML_U16 left;
    AML_U16 right;
    AML_U16 top;
    AML_U16 bottom;
} CCL_Feature_T;

AML_VOID SAMPLE_COMM_CVE_CheckCveMpiInit(AML_VOID);
AML_U32 SAMPLE_CVE_CheckSum(AML_S32 buffersize, AML_U8 *buf, AML_S32 byte_width);
AML_S32 SAMPLE_CVE_CCL_Feature_Checksum(CCL_Feature_T *feature_buf, AML_S32 buff_len);
AML_U16 SAMPLE_COMM_CVE_CalcStride(AML_U32 u32Width, AML_U8 u8Align);
AML_S32 SAMPLE_COMM_CVE_CreateMemInfo(CVE_MEM_INFO_T *pstMemInfo, AML_U32 u32Size);
AML_S32 SAMPLE_COMM_CVE_Input_FileName(char *pFpName, AML_S32 size, char *DefaultName);
AML_S32 SAMPLE_COMM_CVE_Input_Index(void);
AML_S32 SAMPLE_COMM_CVE_ReadFile(CVE_IMAGE_T *pstImg, FILE *pFp);
AML_S32 SAMPLE_COMM_CVE_WriteFile(CVE_IMAGE_T *pstImg, FILE *pFp);
AML_S32 SAMPLE_COMM_CVE_CreateImage(CVE_IMAGE_T *pstImg, CVE_IMAGE_TYPE_E enType, AML_U32 u32Width,
                                    AML_U32 u32Height);
AML_S32 SAMPLE_COMM_CVE_CreateRawInfo(CVE_RAW_T *pstRaw, CVE_RAW_MODE_E RawType, AML_U32 u32Width,
                                      AML_U32 u32Height);
AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Mem(CVE_MEM_INFO_T *pstMem, FILE *pfp);
AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Raw(CVE_RAW_T *pstRaw, FILE *pfp);
AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Data(CVE_DATA_T *pstData, FILE *pfp);
AML_S32 SAMPLE_COMM_CVE_WriteFile_From_Data(CVE_DATA_T *pstData, FILE *pfp);
AML_S32 SAMPLE_COMM_CVE_CreateData(CVE_DATA_T *pstData, AML_U32 u32Width, AML_U32 u32Height);
AML_S32 SAMPLE_COMM_CVE_WriteFile_From_Mem(CVE_MEM_INFO_T *pstData, FILE *pfp);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __SAMPLE_COMM_CVE_H__ */
