/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UBINOS_BSP_DTTY_ASYNC_H_
#define UBINOS_BSP_DTTY_ASYNC_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file dtty.h
 *
 * @brief Async communication BSP debug terminal API
 *
 * 비동기 통신 BSP 디버그 터미널 API를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

/*!
 * 디버깅 터미널을 초기화하는 함수
 *
 * 이 함수는 시스템 시작시 bsp_comp_init 함수에서 자동적으로 호출됩니다.
 *
 * @return	 0: 성공<br>
 * 			<br>
 * 			-1: 오류
 */
int dtty_async_init(void);

/*!
 * 디버깅 터미널을 활성화하는 함수
 *
 * 이 함수는 dtty_init 함수에서 자동적으로 호출됩니다.
 *
 * @return	 0: 성공<br>
 * 			<br>
 * 			-1 : 오류
 * 			-10: 시스템이 이 함수를 지원하지 않음
 */
int dtty_async_enable(void);

/*!
 * 디버깅 터미널을 비활성화하는 함수
 *
 * @return	 0: 성공<br>
 * 			<br>
 * 			-1 : 오류
 * 			-10: 시스템이 이 함수를 지원하지 않음
 */
int dtty_async_disable(void);

/*!
 * 디버깅 터미널 오류가 있는지를 검사하는 함수
 *
 * @return	 0: 없음<br>
 * 			 other: 오류 번호<br>
 */
int dtty_async_geterror(void);

/*!
 * 디버깅 터미널에서 문자를 입력받는 함수
 *
 * @param	ch_p	입력받은 문자를 저장할 변수의 주소
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int dtty_async_getc(char * ch_p);

/*!
 * 디버깅 터미널에 문자를 출력하는 함수
 *
 * @param	ch		출력할 문자
 *
 * @return	 0: 성공<br>
 * 			<br>
 * 			-1: 오류
 */
int dtty_async_putc(int ch);

/*!
 * 디버깅 터미널에 문자열을 출력하는 함수
 *
 * @param	str		출력할 문자열
 *
 * @param	max		출력할 문자열의 크기
 *
 * @return	 출력한 문자열의 크기
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int dtty_async_putn(const char * str, int len);

/*!
 * 디버깅 터미널 입력 버퍼에 입력받은 문자가 있는지를 검사하는 함수
 *
 * @return	 1: 있음<br>
 * 			 0: 없음<br>
 */
int dtty_async_kbhit(void);

/*!
 * 디버깅 터미널에 문자열을 출력하는 함수
 *
 * @param	str		출력할 문자열
 *
 * @param	max		출력할 문자열의 최대 크기
 *
 * @return	 출력한 문자열의 크기
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int dtty_async_puts(const char * str, int max);

/*!
 * 디버깅 터미널에서 문자열을 입력받는 함수
 *
 * "\n", "\r", 또는 "\0" 이 입력되거나 최대 크기보다 작을 때까지 입력받는다.
 * 입력받은 "\n", "\r"은 퍼버에 저장되지 않는다.
 *
 * @param	str		입력받은 문자열을 저장할 버퍼
 *
 * @param	max		입력받을 문자열의 최대 크기
 *
 * @return	 입력받은 문자열의 크기
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int dtty_async_gets(char * str, int max);

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_BSP_DTTY_ASYNC_H_ */