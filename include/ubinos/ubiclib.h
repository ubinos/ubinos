/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UBICLIB_H_
#define UBICLIB_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file ubiclib.h
 *
 * @brief ubiclib (Ubinos C Library) API
 *
 * ubiclib (Ubinos C Library) API를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

/*!
 * ubiclib 컴포넌트를 초기화하는 함수
 *
 * 초기화 작업들 중 재진입(reenterance)을 지원하기 위한 부분은 수행하지 않습니다.<br>
 * 재진입(reenterance)을 지원하려면 ubiclib_comp_init_reent 함수를 추가로 호출해 주어야 합니다.<br>
 * 이 함수는 시스템 시작시  bsp 컴포넌트의 main 함수에서 자동적으로 호출됩니다.
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
int ubiclib_comp_init(void);

/*!
 * ubiclib 컴포넌트의 초기화 작업들 중 재진입(reenterance)을 지원하기 위한 부분을 수행하는 함수
 *
 * 이 함수는 시스템 시작시  bsp 컴포넌트의 main 함수에서 자동적으로 호출됩니다.
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
int ubiclib_comp_init_reent(void);

/*! max 매크로 */
#define max(a,b) ((a) > (b) ? (a) : (b))

/*! min 매크로 */
#define min(a,b) ((a) < (b) ? (a) : (b))

/*!
 * 부호 없는 정수 지수승 연산을 수행하는 함수
 *
 * @param	x		지수
 *
 * @param	y		승수
 *
 * @return	y power of x<br>
 */
unsigned int uipow(unsigned int x, unsigned int y);

/*!
 * 부호 없는 정수 x와 d의 x/d 결과의 올림값을 구하는 함수<br>
 *
 * @param	x		피제수 (dividend)<br>
 *
 * @param	d		제수 (divisor)<br>
 * 					x가 0이면 d가 0이더라고 오류로 처리하지 않음<br>
 *
 * @return	x/d 결과의 올림값<br>
 */
unsigned int uidiv_ceil(register unsigned int x, register unsigned int d);

/*!
 * 부호 없는 정수의 값이 1인 최상위 비트까지 0의 수를 구하는 함수<br>
 * Leading Zero Count<br>
 *
 * @param	x		x 값
 *
 * @return	값이 1인 최상위 비트까지 0의 수<br>
 */
unsigned int uilzc(register unsigned int x);

/*!
 * 부호 없는 정수의 값이 1인 최하위 비트를 구하는 함수<br>
 * Least Significant 1 Bit<br>
 *
 * @param	x		x 값
 *
 * @return	값이 1인 최하위 비트<br>
 */
unsigned int uilsb(register unsigned int x);

/*!
 * 부호 없는 정수 x의 log2의 올림값을 구하는 함수<br>
 * Log2 of an Integer x<br>
 *
 * @param	x		x 값
 *
 * @return	log2(x)의 올림값<br>
 */
unsigned int uilog2_ceil(register unsigned int x);

/*!
 * 부호 없는 정수 x의 log2의 내림값을 구하는 함수<br>
 * Floor of Log2 of an Integer x<br>
 *
 * @param	x		x 값
 *
 * @return	log2(x)의 내림값<br>
 */
unsigned int uilog2_floor(register unsigned int x);

/*!
 * 부호 없는 정수 x 보다 큰 가장 작은 2의 거듭제곱 값을 찾는 함수<br>
 * Next Largest Power of 2<br>
 *
 * @param	x		대상 값
 *
 * @return	x 보다 큰 가장 작은 2의 거듭제곱 값<br>
 */
unsigned int uinlp2(register unsigned int x);

/*!
 * 부호 없는 정수 x 보다 크거나 같은 가장 작은 2의 거듭제곱 값을 찾는 함수<br>
 * Equal or Next Largest Power of 2<br>
 *
 * @param	x		대상 값
 *
 * @return	x 보다 크거나 같은 가장 작은 2의 거듭제곱 값<br>
 */
unsigned int uienlp2(register unsigned int x);

/*!
 * 부호 없는 정수의 값이 1인 최상위 비트를 구하는 함수<br>
 * Most Significant 1 Bit<br>
 *
 * @param	x		대상 값
 *
 * @return	최상위 1 비트 위치<br>
 */
unsigned int uimsb(register unsigned int x);

/*!
 * 부호 없는 정수의 값이 1인 비트 수를 구하는 함수<br>
 * Population Count (Ones Count)<br>
 *
 * @param	x		대상 값
 *
 * @return	값이 1인 비트 수<br>
 */
unsigned int uiones(register unsigned int x);

#include <ubinos/ubiclib/logm.h>
#include <ubinos/ubiclib/bitmap.h>
#include <ubinos/ubiclib/cirbuf.h>
#include <ubinos/ubiclib/dlist.h>
#include <ubinos/ubiclib/edlist.h>
#include <ubinos/ubiclib/heap.h>
#include <ubinos/ubiclib/list.h>
#include <ubinos/ubiclib/stdlib.h>
#include <ubinos/ubiclib/cli.h>

#ifdef	__cplusplus
}
#endif

#endif /* UBICLIB_H_ */
