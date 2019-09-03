/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the itf_ubinos component of the Ubinos.

 GNU General Public License Usage
 This file may be used under the terms of the GNU
 General Public License version 3.0 as published by the Free Software
 Foundation and appearing in the file license_gpl3.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU General Public License version 3.0 requirements will be
 met: http://www.gnu.org/copyleft/gpl.html.

 GNU Lesser General Public License Usage
 Alternatively, this file may be used under the terms of the GNU Lesser
 General Public License version 2.1 as published by the Free Software
 Foundation and appearing in the file license_lgpl.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU Lesser General Public License version 2.1 requirements
 will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

 Commercial Usage
 Alternatively, licensees holding valid commercial licenses may
 use this file in accordance with the commercial license agreement
 provided with the software or, alternatively, in accordance with the
 terms contained in a written agreement between you and rightful owner.
 */

#ifndef UBICLIB_LOGM_H_
#define UBICLIB_LOGM_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file	logm.h
 *
 * @brief	ubiclib (Ubinos C Library) 컴포넌트 로그 메세지 인터페이스
 *
 * ubiclib 컴포넌트가  제공하는 로그 메세지 인터페이스를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

/*! 모든 카테고리 */
#define LOGM_CATEGORY__ALL			0
/*! 기본 카테고리 */
#define LOGM_CATEGORY__DEFAULT		1
/*! 힙 카테고리 */
#define LOGM_CATEGORY__HEAP			2
/*! 비트맵 카테고리 */
#define LOGM_CATEGORY__BITMAP		3
/*! 사용자0 카테고리 */
#define LOGM_CATEGORY__USER00		4
/*! 사용자1 카테고리 */
#define LOGM_CATEGORY__USER01		5
/*! 사용자2 카테고리 */
#define LOGM_CATEGORY__USER02		6
/*! 카테고리 끝 */
#define LOGM_CATEGORY__END			7

/*! 어떤 메시지도 출력하지 않음 */
#define LOGM_LEVEL__NONE			0
/*! 항상 기록되어야 하는 메시지 */
#define LOGM_LEVEL__ALWAYS			1
/*! 심각한 수준의 문제에 관한 메시지 */
#define LOGM_LEVEL__FATAL			2
/*! 일반적인 문제에 관한 메시지 */
#define LOGM_LEVEL__ERROR			3
/*! 경고 메시지 */
#define LOGM_LEVEL__WARNING			4
/*! 동작 상태 정보 */
#define LOGM_LEVEL__INFO			5
/*! 디버깅시 필요한 기타 정보 */
#define LOGM_LEVEL__DEBUG			6
/*! 레벨 끝 */
#define LOGM_LEVEL__END				7

/*! 카테고리 */
#define LOGM_CATEGORY 				LOGM_CATEGORY__DEFAULT
/*! 레벨 */
#define LOGM_LEVEL	 				LOGM_LEVEL__WARNING
/*! 테그 */
#define LOGM_TAG					NULL

#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)

/*!
 * 기록할 메시지 수준을 설정하는 함수
 *
 * @param	category 메시지 분류 번호 (0은 모든 분류)
 *
 * @param	level    기록할 메시지 수준 (설정한 수준 이상(같거나 작은 값)의 메시지만 기록됨)
 *
 * @return	설정한 기록할 메시지 수준<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int logm_setlevel(int category, int level);

/*!
 * 설정되어 있는 기록할 메시지 수준을 돌려주는 함수
 *
 * @param	category 메시지 분류 번호
 *
 * @return	설정되어 있는 기록할 메시지 수준<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
int logm_getlevel(int category);

/*!
 * 메시지를 기록하는 함수
 *
 * @param category	메시지 분류 번호
 *
 * @param level		메시지 수준
 *
 * @param tag		메시지 테그
 *
 * @param format	메시지 형식
 *
 * @param ...		메시지에 포함될 데이터들
 *
 * @return			기록한 메시지 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
int logm_printf(int category, int level, const char * tag, const char * format, ...);

/*!
 * 메시지를 기록하는 함수
 *
 * @param category	메시지 분류 번호
 *
 * @param level		메시지 수준
 *
 * @param tag		메시지 테그
 *
 * @param msg		메시지
 * @return			기록한 메시지 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
int logm_print(int category, int level, const char * tag, const char * msg);

/*!
 * 버퍼에 문자열을 출력하는 함수
 *
 * @param str		문자열을 출력할 버퍼
 *
 * @param num		문자열 최대 길이
 *
 * @param format	문자열 형식
 *
 * @param ...		문자열에 포함될 데이터들
 *
 * @return			출력한 문자열 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
int snprintf(char * str, size_t num, const char * format, ...);

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logma(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__ALWAYS,  LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmt(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__FATAL,   LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logme(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__ERROR,   LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */
#define logmw(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__WARNING, LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmi(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__INFO,    LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmd(msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL__DEBUG,   LOGM_TAG, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 기본값 수준) */
#define logm (msg) logm_print(LOGM_CATEGORY, LOGM_LEVEL,          LOGM_TAG, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logmfa(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__ALWAYS,  LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmft(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__FATAL,   LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logmfe(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__ERROR,   LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */
#define logmfw(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__WARNING, LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmfi(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__INFO,    LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmfd(format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL__DEBUG,   LOGM_TAG, format, ## args)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 기본값 수준) */
#define logmf (format, args...) logm_printf(LOGM_CATEGORY, LOGM_LEVEL,          LOGM_TAG, format, ## args)

#else /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

/*!
 * 기록할 메시지 수준을 설정하는 함수
 *
 * @param	category 메시지 분류 번호 (0은 모든 분류)
 *
 * @param	level    기록할 메시지 수준 (설정한 수준 이상(같거나 작은 값)의 메시지만 기록됨)
 *
 * @return	설정한 기록할 메시지 수준<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
#define logm_setlevel(category, level)                  ((void) (LOGM_LEVEL__NONE))

/*!
 * 설정되어 있는 기록할 메시지 수준을 돌려주는 함수
 *
 * @param	category 메시지 분류 번호
 *
 * @return	설정되어 있는 기록할 메시지 수준<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
#define logm_getlevel(category)                         ((void) (LOGM_LEVEL__NONE))

/*!
 * 메시지를 기록하는 함수
 *
 * @param category	메시지 분류 번호
 *
 * @param level		메시지 수준
 *
 * @param tag		메시지 테크
 *
 * @param format	메시지 형식
 *
 * @param ...		메시지에 포함될 데이터들
 *
 * @return			기록한 메시지 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
#define logm_printf(category, level, tag, format, args...)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logma(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmt(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logme(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */
#define logmw(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmi(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmd(msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 기본값 수준) */
#define logm (msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logmfa(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmft(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logmfe(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */
#define logmfw(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmfi(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmfd(format, args...)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 기본값 수준) */
#define logmf (format, args...)

#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

#ifdef	__cplusplus
}
#endif

#endif /* UBICLIB_LOGM_H_ */
