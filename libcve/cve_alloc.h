/*
 *  mbi_alloc.h
 *
 */

#ifndef __SYS_MBI_ION_H
#define __SYS_MBI_ION_H

#include "aml_type.h"
#include "test_dma_api.h"

struct cve_ion_buffer {
    int used;
    int dmafd;
    struct usr_ctx_s *ctx;
    AML_U32 size;
    AML_U64 viraddr;
};

int init_ion_buffer(void);
int cve_alloc_ion(int *dmafd, AML_VOID **u64VirAddr, AML_U32 len);
int cve_free_ion(int dmafd, AML_VOID *u64VirAddr);

#endif /* __SYS_MBI_ION_H */
