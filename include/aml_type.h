/*
 *
 * Copyright (C) 2021 by Amlogic, Inc.
 *
 */

#ifndef _AML_TYPE_H_
#define _AML_TYPE_H_

//#include <linux/types.h>

#include <stdint.h>
#ifndef NULL
#define NULL (void *)0L
#endif

#define AML_NULL 0L
#define AML_SUCCESS 0
#define AML_FAILURE (-1)

#define AML_VOID void
#define AML_UNUSED(x) ((x) = (x))

typedef enum mbp_bool_e {
    AML_FALSE = 0,
    AML_TRUE = 1,
} AML_BOOL_E;

typedef unsigned char AML_UCHAR;
typedef unsigned char AML_U8;
typedef unsigned short AML_U16;
typedef unsigned int AML_U32;
typedef unsigned long AML_UL;
typedef AML_UL AML_ULONG;
typedef uintptr_t AML_UINTPTR_T;

typedef char AML_CHAR;
typedef signed char AML_S8;
typedef short AML_S16;
typedef int AML_S32;
typedef long AML_SL;

typedef float AML_FLOAT;
typedef double AML_DOUBLE;

typedef unsigned long long AML_U64;
typedef long long AML_S64;

typedef unsigned long AML_SIZE_T;
typedef unsigned long AML_LENGTH_T;
typedef unsigned long int AML_PHYS_ADDR_T;

typedef unsigned int AML_HANDLE;

#endif /* _AML_TYPE_H_ */
