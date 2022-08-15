/*
 *  mbi_alloc.c
 *
 * Memory Allocator functions for ion
 *
 */
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "aml_type.h"
#include "cve.h"
#include "cve_alloc.h"
#include "test_dma_api.h"

#define ION_BUFF_NUM 32

struct cve_ion_buffer ion_buffer[ION_BUFF_NUM];
struct usr_ctx_s *ctx = NULL;

int init_ion_buffer(void)
{
    memset(ion_buffer, 0, sizeof(ion_buffer));
    ctx = (struct usr_ctx_s *)malloc(sizeof(struct usr_ctx_s) * ION_BUFF_NUM);
    return 0;
}

static int find_empty_buffer(void)
{
    int i;

    for (i = 0; i < ION_BUFF_NUM; i++) {
        if (ion_buffer[i].used == AML_FALSE) {
            ion_buffer[i].used = AML_TRUE;
            break;
        }
    }
    if (i == ION_BUFF_NUM) {
        i = -1;
    }
    ion_buffer[i].ctx = &ctx[i];
    if (create_ctx(ion_buffer[i].ctx)) {
        return -1;
    }
    return i;
}

static int find_used_buffer(AML_U64 *u64VirAddr)
{
    int i;
    for (i = 0; i < ION_BUFF_NUM; i++) {
        if (ion_buffer[i].viraddr == *u64VirAddr) {
            break;
        }
    }
    if (i == ION_BUFF_NUM) {
        i = -1;
    }
    return i;
}

int cve_alloc_ion(int *dmafd, AML_VOID **u64VirAddr, AML_U32 len)
{
    int ret;
    int num;

    num = find_empty_buffer();
    if (num == -1) {
        return AML_FAILURE;
    }
    ion_buffer[num].size = len;

    ret = alloc_dma_buffer(ion_buffer[num].ctx, INPUT_BUFF_TYPE, len);
    if (ret < 0)
        return AML_FAILURE;
    ion_buffer[num].dmafd = ret;
    *u64VirAddr = (AML_VOID *)ion_buffer[num].ctx->i_buff[0];
    *dmafd = ret;
    return AML_SUCCESS;
}

int cve_free_ion(int dmafd, AML_VOID *u64VirAddr)
{
    int num;

    num = find_used_buffer((AML_U64 *)u64VirAddr);
    if (num == -1) {
        return AML_FAILURE;
    }
    destroy_ctx(ion_buffer[num].ctx);
    dmafd = 0;

    memset(&ion_buffer[num], 0, sizeof(struct cve_ion_buffer));
    return 0;
}
