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

#define MEM_ALIGNMASK_16 (16 - 1)

#define MEM_ALIGN_16(a) ((((unsigned int) (a)) + MEM_ALIGNMASK_16) & (~MEM_ALIGNMASK_16))

#elif (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__LOCAL)

#ifndef NULL
/*! NULL 정의 */
#define NULL 0
#endif

/*! size_t 형 정의 */
typedef __SIZE_TYPE__ size_t;

#else

#error "Unsupported UBINOS__BSP__CPU_ARCH"

#endif /* (UBINOS__BSP__CPU_ARCH == ... */

#ifndef __ASSEMBLY__

#include <stdint.h>
#include <assert.h>

#include <ubinos/objtype.h>

/*! ubinos status code  */
typedef enum {
    UBI_ST_OK                       =   0, /*!< No error */
    UBI_ST_ERR                      =   1, /*!< Error */
    UBI_ST_BUSY                     =   2, /*!< Busy */
    UBI_ST_TIMEOUT                  =   3, /*!< Timeout */
    UBI_ST_CANCEL                   =   4, /*!< Canceled (normal) */
    UBI_ST_CANCEL_2                 =   5, /*!< Canceled (type 2) */

    UBI_ST_ERR_UNKNOWN              =  10, /*!< Unknown error */
    UBI_ST_ERR_NULL                 =  11, /*!< Null pointer error */
    UBI_ST_ERR_NO_MEM               =  12, /*!< No memory error */
    UBI_ST_ERR_BUF_FULL             =  13, /*!< Buffer full error */
    UBI_ST_ERR_BUF_EMPTY            =  14, /*!< Buffer empty error */
    UBI_ST_ERR_NOT_FOUND            =  15, /*!< Not found error */
    UBI_ST_ERR_NOT_SUPPORTED        =  16, /*!< Not supported error */
    UBI_ST_ERR_INVALID_PARAM        =  17, /*!< Invalid parameter error */
    UBI_ST_ERR_INVALID_DATA         =  18, /*!< Invalid data error */
    UBI_ST_ERR_INVALID_LENGTH       =  19, /*!< Invalid length error */
    UBI_ST_ERR_INVALID_ADDR         =  20, /*!< Invalid address error */
    UBI_ST_ERR_INVALID_STATE        =  21, /*!< Invalid state error */
    UBI_ST_ERR_INIT                 =  22, /*!< Initialization error */
    UBI_ST_ERR_RESET                =  23, /*!< Reset error  */
    UBI_ST_ERR_IO                   =  24, /*!< IO error */
    UBI_ST_ERR_TX                   =  25, /*!< TX error */
    UBI_ST_ERR_RX                   =  26, /*!< RX error */
    UBI_ST_ERR_PACKET               =  27, /*!< Packet error */
    UBI_ST_ERR_HEAP                 =  28, /*!< Heap error */
    UBI_ST_ERR_BUS                  =  29, /*!< Bus error */
    UBI_ST_ERR_OVERFLOW             =  30, /*!< Overflow error */
    UBI_ST_ERR_UNDERFLOW            =  31, /*!< Underflow error */
} ubi_st_t;

#define ubi_assert(__expr) assert(__expr)

#define ubi_assert_ok(__ubi_st) ubi_assert(__ubi_st == UBI_ST_OK)
#define ubi_assert_not_null(__ptr) ubi_assert((void *) __ptr != NULL)

#define ubi_unused(__var) do { (void) __var; } while(0)

/* Deprecated */
#define UBI_ERR_INTERNAL UBI_ST_ERR

#define ubi_err_t ubi_st_t

#define UBI_ERR_OK                      UBI_ST_OK
#define UBI_ERR_ERROR                   UBI_ST_ERR
#define UBI_ERR_BUSY                    UBI_ST_BUSY
#define UBI_ERR_TIMEOUT                 UBI_ST_TIMEOUT
#define UBI_ERR_CANCEL                  UBI_ST_CANCEL
#define UBI_ERR_CANCEL_2                UBI_ST_CANCEL_2

#define UBI_ERR_UNKNOWN                 UBI_ST_ERR_UNKNOWN
#define UBI_ERR_NULL                    UBI_ST_ERR_NULL
#define UBI_ERR_NO_MEM                  UBI_ST_ERR_NO_MEM
#define UBI_ERR_BUF_FULL                UBI_ST_ERR_BUF_FULL
#define UBI_ERR_BUF_EMPTY               UBI_ST_ERR_BUF_EMPTY
#define UBI_ERR_NOT_FOUND               UBI_ST_ERR_NOT_FOUND
#define UBI_ERR_NOT_SUPPORTED           UBI_ST_ERR_NOT_SUPPORTED
#define UBI_ERR_INVALID_PARAM           UBI_ST_ERR_INVALID_PARAM
#define UBI_ERR_INVALID_DATA            UBI_ST_ERR_INVALID_DATA
#define UBI_ERR_INVALID_LENGTH          UBI_ST_ERR_INVALID_LENGTH
#define UBI_ERR_INVALID_ADDR            UBI_ST_ERR_INVALID_ADDR
#define UBI_ERR_INVALID_STATE           UBI_ST_ERR_INVALID_STATE
#define UBI_ERR_INIT                    UBI_ST_ERR_INIT
#define UBI_ERR_RESET                   UBI_ST_ERR_RESET
#define UBI_ERR_IO                      UBI_ST_ERR_IO
#define UBI_ERR_TX                      UBI_ST_ERR_TX
#define UBI_ERR_RX                      UBI_ST_ERR_RX
#define UBI_ERR_PACKET                  UBI_ST_ERR_PACKET
#define UBI_ERR_HEAP                    UBI_ST_ERR_HEAP
#define UBI_ERR_BUS                     UBI_ST_ERR_BUS

#define UBI_ERR_BUS_INIT                UBI_ST_ERR_INIT
#define UBI_ERR_BUS_RESET               UBI_ST_ERR_RESET
#define UBI_ERR_BUS_IO                  UBI_ST_ERR_IO
#define UBI_ERR_BUS_TX                  UBI_ST_ERR_TX
#define UBI_ERR_BUS_RX                  UBI_ST_ERR_RX

#endif /* __ASSEMBLY__ */

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_TYPE_H_ */

