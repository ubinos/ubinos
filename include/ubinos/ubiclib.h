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

/*!
 * 정수값을 10진수 아스키 코드 문자열로 변환하는 함수
 *
 * @param	value	변환할 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * itoa(int value, char * buf, int max);

/*!
 * 정수값을 16진수 아스키 코드 문자열로 변환하는 함수
 *
 * @param	value	변환할 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * itoah(int value, char * buf, int max);

/*!
 * 정수값의 바이트 순서를 big endian으로 변환하는 함수
 *
 * @param	value	변환할 값
 *
 * @return	변환된 값
 */
int htobi(int value);

/*!
 * 언사인드 정수값을 10진수 아스키 코드 문자열로 변환하는 함수
 *
 * @param	value	변환할 언사인드 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * uitoa(unsigned int value, char * buf, int max);

/*!
 * 언사인드 정수값을 10진수 아스키 코드 문자열로 변환하는 함수 (스택 오버플로우 검사 생략)
 *
 * @param	value	변환할 언사인드 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * uitoa_nosocheck(unsigned int value, char * buf, int max);

/*!
 * 언사인드 정수값을 16진수 아스키 코드 문자열로 변환하는 함수
 *
 * @param	value	변환할 언사인드 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * uitoah(unsigned int value, char * buf, int max);

/*!
 * 언사인드 정수값을 16진수 아스키 코드 문자열로 변환하는 함수 (스택 오버플로우 검사 생략)
 *
 * @param	value	변환할 언사인드 정수값
 *
 * @param	buf		변환한 문자열을 저장할 버퍼
 *
 * @param	max		변환한 문자열을 저장할 버퍼의 최대 크기
 *
 * @return	변환된 문자열 포인터<br>
 * 			<br>
 * 			 NULL: 오류<br>
 */
char * uitoah_nosocheck(unsigned int value, char * buf, int max);

/*!
 * 언사인드 정수값의 바이트 순서를 big endian으로 변환하는 함수
 *
 * @param	value	변환할 값
 *
 * @return	변환된 값
 */
unsigned int htobui(unsigned int value);

/*!
 * 16진수 아스키 코드 문자열을 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
int ahtoi(const char * buf);

/*!
 * 16진수 아스키 코드 문자열을 롱 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
long ahtol(const char * buf);

/*!
 * 10진수 아스키 코드 문자열을 언사인드 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
unsigned int atoui(const char * buf);

/*!
 * 10진수 아스키 코드 문자열을 언사인드 롱 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
unsigned long atoul(const char * buf);

/*!
 * 16진수 아스키 코드 문자열을 언사인드 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
unsigned int ahtoui(const char * buf);

/*!
 * 16진수 아스키 코드 문자열을 언사인드 롱 정수값으로 변환하는 함수
 *
 * @param	buf		변환할 문자열이 저장된 버퍼
 *
 * @return	변환된 값
 */
unsigned long ahtoul(const char * buf);

#undef toupper
#undef tolower

/*!
 * 아스키 코드 소문자를 대문자로 변환하는 함수
 *
 * @param	c		변환할 문자
 *
 * @return	변환된 문자
 */
int toupper(int c);

/*!
 * 아스키 코드 대문자를 소문자로 변환하는 함수
 *
 * @param	c		변환할 문자
 *
 * @return	변환된 문자
 */
int tolower(int c);

/*! max 매크로 */
#define max(a,b) ((a) > (b) ? (a) : (b))

/*! min 매크로 */
#define min(a,b) ((a) < (b) ? (a) : (b))

/*!
 * 메모리를 0으로 초기화하는 함수
 *
 * @param	dst		초기화할 메모리 주소
 *
 * @param	num		초기화할 메모리 크기
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int memset0(void * dst, size_t num);

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
