/*
 * Copyright (C) 2019-2024 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 */
#include "sample_comm_cve.h"
#include "cve_alloc.h"
#include "lib_cve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static AML_BOOL_E bMpiInit = AML_FALSE;

AML_U16 SAMPLE_COMM_CVE_CalcStride(AML_U32 u32Width, AML_U8 u8Align)
{
    return (u32Width + (u8Align - u32Width % u8Align) % u8Align);
}
static AML_S32 SAMPLE_CVE_Init(AML_VOID)
{

    init_ion_buffer();
#if 0
    AML_S32 s32Ret;
    MBI_SYS_Exit();

    s32Ret = MBI_SYS_Init();
    if (AML_SUCCESS != s32Ret) {
        TEST_PRT("MBI_SYS_Init fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
#endif
    return AML_SUCCESS;
}

AML_VOID SAMPLE_COMM_CVE_CheckCveMpiInit(AML_VOID)
{
    if (AML_FALSE == bMpiInit) {
        if (SAMPLE_CVE_Init()) {
            TEST_PRT("Cve mpi init failed!\n");
            exit(-1);
        }
        bMpiInit = AML_TRUE;
    }
}

static AML_U32 cve_check_u8(AML_U32 len, AML_U8 *dst_addr)
{
    AML_U32 i;
    AML_U32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return sum;
}

static AML_U32 cve_check_u16(AML_U32 len, AML_U16 *dst_addr)
{
    AML_U32 i;
    AML_U32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return sum;
}

static AML_U32 cve_check_u32(AML_U32 len, AML_U32 *dst_addr)
{
    AML_U32 i;
    AML_U32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return sum;
}
#if 0
static AML_U64 cve_check_u64(AML_U32 len, AML_U64 *dst_addr)
{
    AML_U32 i;
    AML_U64 sum = 0;
    for (i = 0; i< len; i++)
    {
        sum += dst_addr[i];
    }
    return sum;
}
#endif
static AML_U32 cve_check_s8(AML_U32 len, AML_S8 *dst_addr)
{
    AML_U32 i;
    AML_S32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return (AML_U32)sum;
}

static AML_U32 cve_check_s16(AML_U32 len, AML_S16 *dst_addr)
{
    AML_U32 i;
    AML_S32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return (AML_U32)sum;
}

static AML_U32 cve_check_s32(AML_U32 len, AML_S32 *dst_addr)
{
    AML_U32 i;
    AML_S32 sum = 0;
    for (i = 0; i < len; i++) {
        sum += dst_addr[i];
    }
    return (AML_U32)sum;
}

AML_U32 SAMPLE_CVE_CheckSum(AML_S32 buffersize, AML_U8 *buf, AML_S32 type)
{
    AML_U32 u32CheckSum = 0;

    if (type == 0) {
        u32CheckSum = cve_check_u8(buffersize, buf);
    } else if (type == 1) {
        u32CheckSum = cve_check_s8(buffersize, (AML_S8 *)buf);
    } else if (type == 2) {
        u32CheckSum = cve_check_u16(buffersize, (AML_U16 *)buf);
    } else if (type == 3) {
        u32CheckSum = cve_check_s16(buffersize, (AML_S16 *)buf);
    } else if (type == 4) {
        u32CheckSum = cve_check_u32(buffersize, (AML_U32 *)buf);
    } else if (type == 5) {
        // u32CheckSum = cve_check_u64(buffersize, (AML_S16 *)buf);
    } else if (type == 6) {
        u32CheckSum = cve_check_s32(buffersize, (AML_S32 *)buf);
    } else {
        u32CheckSum = 0;
    }

    return u32CheckSum;
}

AML_S32 SAMPLE_CVE_CCL_Feature_Checksum(CCL_Feature_T *feature_buf, AML_S32 buff_len)
{
    AML_S32 sum;
    AML_S32 i;
    AML_U32 area;

    sum = 0;
    area = 0;
    for (i = 0; i < buff_len; i++) {
        area = feature_buf[i].area_l + (feature_buf[i].area_h << 16);
        sum += feature_buf[i].label + area + feature_buf[i].left + feature_buf[i].right +
               feature_buf[i].top + feature_buf[i].bottom;
    }

    return sum;
}

AML_S32 SAMPLE_COMM_CVE_Input_FileName(char *pFpName, AML_S32 size, char *DefaultName)
{
    char *get = NULL;
    fgets(pFpName, size, stdin);
    get = strchr(pFpName, '\n');
    if (get) {
        *get = '\0';
    }
    if (strlen(pFpName) == 0) {
        strcpy(pFpName, DefaultName);
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_Input_Index(void)
{
    AML_S32 index = 0;
    char pFpIndex[4] = {0};
    fgets(pFpIndex, 4, stdin);
    index = atoi(pFpIndex);
    return index;
}

AML_S32 SAMPLE_COMM_CVE_ReadFile(CVE_IMAGE_T *pstImg, FILE *pFp)
{
    AML_U16 y;
    AML_U8 *pU8;
    AML_U16 height;
    AML_U16 width;
    AML_U16 loop;
    AML_S32 s32Ret;

    (AML_VOID) fgetc(pFp);
    if (feof(pFp)) {
        TEST_PRT("end of file!\n");
        s32Ret = fseek(pFp, 0, SEEK_SET);
        if (0 != s32Ret) {
            TEST_PRT("fseek failed!\n");
            return s32Ret;
        }

    } else {
        s32Ret = fseek(pFp, -1, SEEK_CUR);
        if (0 != s32Ret) {
            TEST_PRT("fseek failed!\n");
            return s32Ret;
        }
    }

    height = pstImg->u32Height;
    width = pstImg->u32Width;

    switch (pstImg->enType) {
    case CVE_IMAGE_TYPE_U8C1:
    case CVE_IMAGE_TYPE_S8C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420SP: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height / 2; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV422SP:
    case CVE_IMAGE_TYPE_S8C2_PLANAR: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420P: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height / 2; y++) {
            if (1 != fread(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[2];
        for (y = 0; y < height / 2; y++) {
            if (1 != fread(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[2];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV422P: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[2];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[2];
        }

    } break;
    case CVE_IMAGE_TYPE_U8C3_PACKAGE: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fread(pU8, width * 3, 1, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * 3;
        }

    } break;
    case CVE_IMAGE_TYPE_U8C3_PLANAR: {
        for (loop = 0; loop < 3; loop++) {
            pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[loop];
            for (y = 0; y < height; y++) {
                if (1 != fread(pU8, width, 1, pFp)) {
                    TEST_PRT("Read file fail\n");
                    return AML_FAILURE;
                }

                pU8 += pstImg->au32Stride[loop];
            }
        }

    } break;
    case CVE_IMAGE_TYPE_S8C2_PACKAGE:
    case CVE_IMAGE_TYPE_S16C1:
    case CVE_IMAGE_TYPE_U16C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (width != fread(pU8, sizeof(AML_U16), width, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U16);
        }
    } break;
    case CVE_IMAGE_TYPE_S32C1:
    case CVE_IMAGE_TYPE_U32C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (width != fread(pU8, sizeof(AML_U32), width, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U32);
        }
    } break;
    case CVE_IMAGE_TYPE_S64C1:
    case CVE_IMAGE_TYPE_U64C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (width != fread(pU8, sizeof(AML_U64), width, pFp)) {
                TEST_PRT("Read file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U64);
        }
    } break;
    default:
        break;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_WriteFile(CVE_IMAGE_T *pstImg, FILE *pFp)
{
    AML_U16 y;
    AML_U8 *pU8;
    AML_U16 height;
    AML_U16 width;
    AML_U16 loop;

    height = pstImg->u32Height;
    width = pstImg->u32Width;

    switch (pstImg->enType) {
    case CVE_IMAGE_TYPE_U8C1:
    case CVE_IMAGE_TYPE_S8C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420SP: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height / 2; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV422SP:
    case CVE_IMAGE_TYPE_S8C2_PLANAR: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420P: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height / 2; y++) {
            if (1 != fwrite(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[2];
        for (y = 0; y < height / 2; y++) {
            if (1 != fwrite(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[2];
        }
    } break;

    case CVE_IMAGE_TYPE_YUV422P: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[1];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[1];
        }

        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[2];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width / 2, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[2];
        }
    } break;
    case CVE_IMAGE_TYPE_U8C3_PACKAGE: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (1 != fwrite(pU8, width * 3, 1, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * 3;
        }
    } break;
    case CVE_IMAGE_TYPE_U8C3_PLANAR: {
        for (loop = 0; loop < 3; loop++) {
            pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[loop];
            for (y = 0; y < height; y++) {
                if (1 != fwrite(pU8, width, 1, pFp)) {
                    TEST_PRT("Write file fail\n");
                    return AML_FAILURE;
                }

                pU8 += pstImg->au32Stride[loop];
            }
        }
    } break;
    case CVE_IMAGE_TYPE_S8C2_PACKAGE:
    case CVE_IMAGE_TYPE_S16C1:
    case CVE_IMAGE_TYPE_U16C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (sizeof(AML_U16) != fwrite(pU8, width, sizeof(AML_U16), pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U16);
        }
    } break;
    case CVE_IMAGE_TYPE_S32C1:
    case CVE_IMAGE_TYPE_U32C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (width != fwrite(pU8, sizeof(AML_U32), width, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U32);
        }
    } break;
    case CVE_IMAGE_TYPE_S64C1:
    case CVE_IMAGE_TYPE_U64C1: {
        pU8 = (AML_U8 *)(AML_UL)pstImg->au64VirAddr[0];
        for (y = 0; y < height; y++) {
            if (width != fwrite(pU8, sizeof(AML_U64), width, pFp)) {
                TEST_PRT("Write file fail\n");
                return AML_FAILURE;
            }

            pU8 += pstImg->au32Stride[0] * sizeof(AML_U64);
        }
    } break;
    default:
        break;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_CreateImage(CVE_IMAGE_T *pstImg, CVE_IMAGE_TYPE_E enType, AML_U32 u32Width,
                                    AML_U32 u32Height)
{
    AML_U32 u32Size = 0;
    AML_S32 s32Ret;
    if (NULL == pstImg) {
        TEST_PRT("pstImg is null\n");
        return AML_FAILURE;
    }

    pstImg->enType = enType;
    pstImg->u32Width = u32Width;
    pstImg->u32Height = u32Height;
    pstImg->au32Stride[0] = SAMPLE_COMM_CVE_CalcStride(pstImg->u32Width, CVE_ALIGN);

    switch (enType) {
    case CVE_IMAGE_TYPE_U8C1:
    case CVE_IMAGE_TYPE_S8C1: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height;
        s32Ret = cve_alloc_ion(&(pstImg->dmafd), (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420SP: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * 3 / 2;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
        pstImg->au32Stride[1] = pstImg->au32Stride[0];
        pstImg->au64PhyAddr[1] =
            pstImg->au64PhyAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;
        pstImg->au64VirAddr[1] =
            pstImg->au64VirAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;

    } break;
    case CVE_IMAGE_TYPE_YUV422SP:
    case CVE_IMAGE_TYPE_S8C2_PLANAR: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * 2;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
        pstImg->au32Stride[1] = pstImg->au32Stride[0];
        pstImg->au64PhyAddr[1] =
            pstImg->au64PhyAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;
        pstImg->au64VirAddr[1] =
            pstImg->au64VirAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;

    } break;
    case CVE_IMAGE_TYPE_YUV420P: {
        pstImg->au32Stride[1] = SAMPLE_COMM_CVE_CalcStride(pstImg->u32Width / 2, CVE_ALIGN);
        pstImg->au32Stride[2] = pstImg->au32Stride[1];

        u32Size =
            pstImg->au32Stride[0] * pstImg->u32Height + pstImg->au32Stride[1] * pstImg->u32Height;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }

        pstImg->au64PhyAddr[1] = pstImg->au64PhyAddr[0] + pstImg->au32Stride[0] * pstImg->u32Height;
        pstImg->au64VirAddr[1] = pstImg->au64VirAddr[0] + pstImg->au32Stride[0] * pstImg->u32Height;
        pstImg->au64PhyAddr[2] =
            pstImg->au64PhyAddr[1] + pstImg->au32Stride[1] * pstImg->u32Height / 2;
        pstImg->au64VirAddr[2] =
            pstImg->au64VirAddr[1] + pstImg->au32Stride[1] * pstImg->u32Height / 2;
    } break;
    case CVE_IMAGE_TYPE_YUV422P: {
        pstImg->au32Stride[1] = SAMPLE_COMM_CVE_CalcStride(pstImg->u32Width / 2, CVE_ALIGN);
        pstImg->au32Stride[2] = pstImg->au32Stride[1];
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height +
                  pstImg->au32Stride[1] * pstImg->u32Height * 2;

        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }

        pstImg->au64PhyAddr[1] = pstImg->au64PhyAddr[0] + pstImg->au32Stride[0] * pstImg->u32Height;
        pstImg->au64VirAddr[1] = pstImg->au64VirAddr[0] + pstImg->au32Stride[0] * pstImg->u32Height;
        pstImg->au64PhyAddr[2] = pstImg->au64PhyAddr[1] + pstImg->au32Stride[1] * pstImg->u32Height;
        pstImg->au64VirAddr[2] = pstImg->au64VirAddr[1] + pstImg->au32Stride[1] * pstImg->u32Height;
    } break;
    case CVE_IMAGE_TYPE_S8C2_PACKAGE: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * 2;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
        pstImg->au32Stride[1] = pstImg->au32Stride[0];
        pstImg->au64VirAddr[1] = pstImg->au64VirAddr[0] + 1;
        pstImg->au64PhyAddr[1] = pstImg->au64PhyAddr[0] + 1;
    } break;
    case CVE_IMAGE_TYPE_S16C1:
    case CVE_IMAGE_TYPE_U16C1: {

        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U16);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_U8C3_PACKAGE: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * 3;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
        pstImg->au64VirAddr[1] = pstImg->au64VirAddr[0] + 1;
        pstImg->au64VirAddr[2] = pstImg->au64VirAddr[1] + 1;
        pstImg->au64PhyAddr[1] = pstImg->au64PhyAddr[0] + 1;
        pstImg->au64PhyAddr[2] = pstImg->au64PhyAddr[1] + 1;
        pstImg->au32Stride[1] = pstImg->au32Stride[0];
        pstImg->au32Stride[2] = pstImg->au32Stride[0];
    } break;
    case CVE_IMAGE_TYPE_U8C3_PLANAR:
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * 3;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
        pstImg->au32Stride[1] = pstImg->au32Stride[0];
        pstImg->au32Stride[2] = pstImg->au32Stride[0];
        pstImg->au64VirAddr[1] =
            pstImg->au64VirAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;
        pstImg->au64VirAddr[2] =
            pstImg->au64VirAddr[1] + (AML_U64)pstImg->au32Stride[1] * (AML_U64)pstImg->u32Height;
        pstImg->au64PhyAddr[1] =
            pstImg->au64PhyAddr[0] + (AML_U64)pstImg->au32Stride[0] * (AML_U64)pstImg->u32Height;
        pstImg->au64PhyAddr[2] =
            pstImg->au64PhyAddr[1] + (AML_U64)pstImg->au32Stride[1] * (AML_U64)pstImg->u32Height;
        break;
    case CVE_IMAGE_TYPE_S32C1:
    case CVE_IMAGE_TYPE_U32C1: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U32);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_S64C1:
    case CVE_IMAGE_TYPE_U64C1: {

        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U64);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    default:
        break;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_CreateMemInfo(CVE_MEM_INFO_T *pstMemInfo, AML_U32 u32Size)
{
    AML_S32 s32Ret;

    if (NULL == pstMemInfo) {
        TEST_PRT("pstMemInfo is null\n");
        return AML_FAILURE;
    }
    pstMemInfo->u32Size = u32Size;
    s32Ret = cve_alloc_ion(&pstMemInfo->dmafd, (AML_VOID **)&pstMemInfo->u64VirAddr, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
        return AML_FAILURE;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_CreateRawInfo(CVE_RAW_T *pstRaw, CVE_RAW_MODE_E RawType, AML_U32 u32Width,
                                      AML_U32 u32Height)
{
    AML_U32 u32Size = 0;
    AML_S32 s32Ret;

    if (NULL == pstRaw) {
        TEST_PRT("pstRaw is null\n");
        return AML_FAILURE;
    }
    pstRaw->enMode = RawType;
    pstRaw->u32Width = u32Width;
    pstRaw->u32Height = u32Height;
    pstRaw->u32Stride = SAMPLE_COMM_CVE_CalcStride(pstRaw->u32Width, CVE_ALIGN);
    switch (RawType) {
    case CVE_RAW_MODE_RAW6:
    case CVE_RAW_MODE_RAW7:
    case CVE_RAW_MODE_RAW8: {
        u32Size = pstRaw->u32Stride * pstRaw->u32Height * 3;
    } break;
    case CVE_RAW_MODE_RAW10: {
        u32Size = pstRaw->u32Stride * 5 / 4 * pstRaw->u32Height * 3;
    } break;
    case CVE_RAW_MODE_RAW12: {
        u32Size = pstRaw->u32Stride * 3 / 2 * pstRaw->u32Height * 3;
    } break;
    case CVE_RAW_MODE_RAW14: {
        u32Size = pstRaw->u32Stride * 2 * pstRaw->u32Height * 3;
    } break;
    default:
        break;
    }
    s32Ret = cve_alloc_ion(&pstRaw->dmafd, (AML_VOID **)&pstRaw->u64VirAddr, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
        return AML_FAILURE;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_CreateImageByCached(CVE_IMAGE_T *pstImg, CVE_IMAGE_TYPE_E enType,
                                            AML_U32 u32Width, AML_U32 u32Height)
{
    AML_U32 u32Size = 0;
    AML_S32 s32Ret;
    if (NULL == pstImg) {
        TEST_PRT("pstImg is null\n");
        return AML_FAILURE;
    }

    pstImg->enType = enType;
    pstImg->u32Width = u32Width;
    pstImg->u32Height = u32Height;
    pstImg->au32Stride[0] = SAMPLE_COMM_CVE_CalcStride(pstImg->u32Width, CVE_ALIGN);

    switch (enType) {
    case CVE_IMAGE_TYPE_U8C1:
    case CVE_IMAGE_TYPE_S8C1: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height;
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_YUV420SP:
        break;
    case CVE_IMAGE_TYPE_YUV422SP:
        break;
    case CVE_IMAGE_TYPE_YUV420P:
        break;
    case CVE_IMAGE_TYPE_YUV422P:
        break;
    case CVE_IMAGE_TYPE_S8C2_PACKAGE:
        break;
    case CVE_IMAGE_TYPE_S8C2_PLANAR:
        break;
    case CVE_IMAGE_TYPE_S16C1:
    case CVE_IMAGE_TYPE_U16C1: {

        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U16);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_U8C3_PACKAGE:
        break;
    case CVE_IMAGE_TYPE_U8C3_PLANAR:
        break;
    case CVE_IMAGE_TYPE_S32C1:
    case CVE_IMAGE_TYPE_U32C1: {
        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U32);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    case CVE_IMAGE_TYPE_S64C1:
    case CVE_IMAGE_TYPE_U64C1: {

        u32Size = pstImg->au32Stride[0] * pstImg->u32Height * sizeof(AML_U64);
        s32Ret = cve_alloc_ion(&pstImg->dmafd, (AML_VOID **)&pstImg->au64VirAddr[0], u32Size);
        if (s32Ret != AML_SUCCESS) {
            TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
            return s32Ret;
        }
    } break;
    default:
        break;
    }

    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Mem(CVE_MEM_INFO_T *pstMem, FILE *pfp)
{
    AML_U32 u32Read;
    AML_U8 *pU8;
    pU8 = (AML_U8 *)(AML_UINTPTR_T)pstMem->u64VirAddr;
    if (feof(pfp)) {
        TEST_PRT("[WARN] File length not enongh length.\n");
        return AML_FAILURE;
    }
    u32Read = fread(pU8, 1, pstMem->u32Size, pfp);
    if (u32Read != pstMem->u32Size) {
        printf("[WARN] File length not enongh, read length:%d, need length:%d.\n", u32Read,
               pstMem->u32Size);
        return AML_FAILURE;
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Raw(CVE_RAW_T *pstRaw, FILE *pfp)
{
    AML_U32 u32Read;
    AML_U8 *pU8;
    AML_U32 i;
    pU8 = (AML_U8 *)(AML_UINTPTR_T)pstRaw->u64VirAddr;
    if (feof(pfp)) {
        TEST_PRT("[WARN] File length not enongh length.\n");
        return AML_FAILURE;
    }
    switch (pstRaw->enMode) {
    case CVE_RAW_MODE_RAW6:
    case CVE_RAW_MODE_RAW7:
    case CVE_RAW_MODE_RAW8: {
        for (i = 0; i < pstRaw->u32Height * 3; i++) {
            u32Read = fread(pU8, pstRaw->u32Width, 1, pfp);
            if (u32Read != 1) {
                TEST_PRT("[WARN] Raw File length not enongh, read:%d.\n", u32Read);
                return AML_FAILURE;
            }
            pU8 = pU8 + pstRaw->u32Width;
        }
    } break;
    case CVE_RAW_MODE_RAW10: {
        for (i = 0; i < pstRaw->u32Height * 3; i++) {
            u32Read = fread(pU8, pstRaw->u32Width * 5 / 4, 1, pfp);
            if (u32Read != 1) {
                TEST_PRT("[WARN] Raw File length not enongh, read:%d.\n", u32Read);
                return AML_FAILURE;
            }
            pU8 = pU8 + pstRaw->u32Width * 5 / 4;
        }
    } break;

    case CVE_RAW_MODE_RAW12: {
        for (i = 0; i < pstRaw->u32Height * 3; i++) {
            u32Read = fread(pU8, pstRaw->u32Width * 3 / 2, 1, pfp);
            if (u32Read != 1) {
                TEST_PRT("[WARN] Raw File length not enongh, read:%d.\n", u32Read);
                return AML_FAILURE;
            }
            pU8 = pU8 + pstRaw->u32Width * 3 / 2;
        }
    } break;
    case CVE_RAW_MODE_RAW14: {
        for (i = 0; i < pstRaw->u32Height * 3; i++) {
            u32Read = fread(pU8, pstRaw->u32Width * 2, 1, pfp);
            if (u32Read != 1) {
                TEST_PRT("[WARN] Raw File length not enongh, read:%d.\n", u32Read);
                return AML_FAILURE;
            }
            pU8 = pU8 + pstRaw->u32Width * 2;
        }
    } break;
    default:
        break;
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_ReadFile_On_Data(CVE_DATA_T *pstData, FILE *pfp)
{
    AML_U32 u32Loop;
    AML_U32 u32Read;
    AML_U8 *pU8;
    pU8 = (AML_U8 *)(AML_UINTPTR_T)pstData->u64VirAddr;
    for (u32Loop = 0; u32Loop < pstData->u32Height; u32Loop++) {
        if (feof(pfp)) {
            TEST_PRT("[WARN] File length not enongh length.\n");
            return AML_FAILURE;
        }
        u32Read = fread(pU8, 1, pstData->u32Width, pfp);
        if (u32Read != pstData->u32Width) {
            printf("[WARN] File length not enongh, read width:%d, need width:%d.\n", u32Read,
                   pstData->u32Width);
            return AML_FAILURE;
        }
        pU8 += pstData->u32Stride;
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_WriteFile_From_Data(CVE_DATA_T *pstData, FILE *pfp)
{
    AML_U32 u32Loop;
    AML_U32 u32Write;
    AML_U8 *pU8;
    pU8 = (AML_U8 *)(AML_UINTPTR_T)pstData->u64VirAddr;
    fseek(pfp, 0, SEEK_SET);
    for (u32Loop = 0; u32Loop < pstData->u32Height; u32Loop++) {
        u32Write = fwrite(pU8, 1, pstData->u32Width, pfp);
        if (u32Write != pstData->u32Width) {
            TEST_PRT("[WARN] not enough memory save data.\n");
            return AML_FAILURE;
        }
        pU8 += pstData->u32Stride;
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_CreateData(CVE_DATA_T *pstData, AML_U32 u32Width, AML_U32 u32Height)
{
    AML_S32 s32Ret;
    AML_U32 u32Size;

    if (NULL == pstData) {
        TEST_PRT("pstData is null\n");
        return AML_FAILURE;
    }
    pstData->u32Width = u32Width;
    pstData->u32Height = u32Height;
    pstData->u32Stride = SAMPLE_COMM_CVE_CalcStride(pstData->u32Width, CVE_ALIGN);
    u32Size = pstData->u32Stride * pstData->u32Height;
    s32Ret = cve_alloc_ion(&pstData->dmafd, (AML_VOID **)&pstData->u64VirAddr, u32Size);
    if (s32Ret != AML_SUCCESS) {
        TEST_PRT("Pmz Alloc fail,Error(%#x)\n", s32Ret);
        return AML_FAILURE;
    }
    return AML_SUCCESS;
}

AML_S32 SAMPLE_COMM_CVE_WriteFile_From_Mem(CVE_MEM_INFO_T *pstData, FILE *pfp)
{
    AML_U32 u32Write;
    AML_U8 *pU8;
    pU8 = (AML_U8 *)(AML_UINTPTR_T)pstData->u64VirAddr;
    u32Write = fwrite(pU8, 1, pstData->u32Size, pfp);
    if (u32Write != pstData->u32Size) {
        TEST_PRT("[WARN] not enough memory save data.\n");
        return AML_FAILURE;
    }
    return AML_SUCCESS;
}
