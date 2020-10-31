/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UBINOS_TYPE_H_
#define UBINOS_TYPE_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file type.h
 *
 * @brief ubinos basic data type
 *
 * ubinos 기본 자료 형을 정의합니다.
 */

#include <ubinos_config.h>

#if (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM)

#ifndef __ASSEMBLY__

/*! 바이트 형 정의 (8비트) */
typedef unsigned char byte_t;

/*! 워드 형 정의 (16비트) */
typedef unsigned short word_t;

/*! 더블 워드 형 정의 (32비트) */
typedef unsigned int dword_t;

#endif /* __ASSEMBLY__ */

#ifndef NULL
/*! NULL 정의 */
#define NULL 0
#endif

#ifndef EOF
/*! EOF (End of File) 정의 */
#define	EOF (-1)
#endif

#ifndef __SIZE_TYPE__
/*! SIZE_TYPE 정의 */
#define __SIZE_TYPE__ long unsigned int
#endif

#ifndef __ASSEMBLY__

/*! size_t 형 정의 */
typedef __SIZE_TYPE__ size_t;

#endif /* __ASSEMBLY__ */

/*! size_t 형을 unsigned integer 형으로 변환하는 매크로 */
#define SIZETOUINT(a) (a)

/*! unsigned integer 형을 size_t 형으로 변환하는 매크로 */
#define UINTTOSIZE(a) (a)

#ifndef INT_MIN
/*! 정수 형 최소 값 */
#define INT_MIN 0x80000000L // -2147483648
#endif

#ifndef INT_MAX
/*! 정수형 최대 값 */
#define INT_MAX 0x7FFFFFFFL // 2147483647
#endif

#ifndef UINT_MAX
/*! 무부호 정수형 최대 값 */
#define UINT_MAX 0xFFFFFFFFL // 4294967295
#endif

#ifndef	INT_SIZE
/*! 정수형 크기 */
#define INT_SIZE 4
#endif

#ifndef INT16_MIN
/*! 16 비트 정수 형 최소 값 */
#define INT16_MIN 0x8000 // -32768
#endif

#ifndef INT16_MAX
/*! 16 비트 정수형 최대 값 */
#define INT16_MAX 0x7FFF // 32767
#endif

#ifndef UINT16_MAX
/*! 16 비트 무부호 정수형 최대 값 */
#define UINT16_MAX 0xFFFF // 65535
#endif

/*! 메모리 정렬 단위 */
#define MEM_ALIGNMENT INT_SIZE

/*! 메모리 정렬 마스크 (Memory Align Mask) */
#define MEM_ALIGNMASK (MEM_ALIGNMENT - 1)

/*! 메모리 정렬 매크로 */
#define MEM_ALIGN(a) ((((unsigned int) (a)) + MEM_ALIGNMASK) & (~MEM_ALIGNMASK))

#else

#error "Unsupported UBINOS__BSP__CPU_ARCH"

#endif /* (UBINOS__BSP__CPU_ARCH == ... */

#ifndef __ASSEMBLY__

#include <stdint.h>

#include <ubinos/objtype.h>

/*! ubinos error code  */
typedef enum {
    UBI_ERR_OK = 0, /*!< No error */
    UBI_ERR_INTERNAL, /*!< Internal error */
    UBI_ERR_UNKNOWN, /*!< Unknown error */
    UBI_ERR_TIMEOUT, /*!< Timeout */
    UBI_ERR_BUSY, /*!< Busy */
    UBI_ERR_NO_MEM, /*!< No memory */
    UBI_ERR_BUF_FULL, /*!< Buffer full */
    UBI_ERR_BUF_EMPTY, /*!< Buffer empty */
    UBI_ERR_NOT_FOUND, /*!< Not found */
    UBI_ERR_NOT_SUPPORTED, /*!< Not supported */
    UBI_ERR_INVALID_PARAM, /*!< Invalid parameter */
    UBI_ERR_INVALID_DATA, /*!< Invalid data */
    UBI_ERR_INVALID_LENGTH, /*!< Invalid length */
    UBI_ERR_INVALID_ADDR, /*!< Invalid address */
    UBI_ERR_INVALID_STATE, /*!< Invalid state */
    UBI_ERR_NULL, /*!< Null pointer */
    UBI_ERR_HEAP, /*!< Heap error */
} ubi_err_t;

#endif /* __ASSEMBLY__ */

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_TYPE_H_ */

