/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
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


/*! 미분류 카테고리 */
#define LOGM_CATEGORY__NONE			0

/*! 유비노스 카테고리 */
#define LOGM_CATEGORY__UBINOS		1
/*! BSP 카테고리 */
#define LOGM_CATEGORY__BSP			2
/*! 유비노스 커널 카테고리 */
#define LOGM_CATEGORY__UBIK			3
/*! 테스크 카테고리 */
#define LOGM_CATEGORY__TASK			4
/*! 세마포어 카테고리 */
#define LOGM_CATEGORY__SEM			5
/*! 메시지큐 카테고리 */
#define LOGM_CATEGORY__MSGQ			6
/*! 상태 변수 카테고리 */
#define LOGM_CATEGORY__CONDV		7
/*! 시그널 카테고리 */
#define LOGM_CATEGORY__SIGNAL		8
/*! 세마포어 타이머 카테고리 */
#define LOGM_CATEGORY__STIMER		9

/*! 유비 C 라이브러리 카테고리 */
#define LOGM_CATEGORY__UBICLIB		10
/*! 힙 카테고리 */
#define LOGM_CATEGORY__HEAP			11

/*! 사용자0 카테고리 */
#define LOGM_CATEGORY__USER00		12
/*! 사용자1 카테고리 */
#define LOGM_CATEGORY__USER01		13
/*! 사용자2 카테고리 */
#define LOGM_CATEGORY__USER02		14

/*! 카테고리 끝 */
#define LOGM_CATEGORY__END			15


/*! 어떤 메시지도 출력하지 않음 */
#define LOGM_LEVEL__NONE			0
/*! 항상 기록되어야 하는 메시지까지만 출력함 */
#define LOGM_LEVEL__ALWAYS			1
/*! 심각한 수준의 문제에 관한 메시지까지만 출력함 */
#define LOGM_LEVEL__FATAL			2
/*! 일반적인 문제에 관한 메시지까지만 출력함 */
#define LOGM_LEVEL__ERROR			3
/*! 경고 메시지까지만 출력함 */
#define LOGM_LEVEL__WARNING			4
/*! 동작 상태 정보까지만 출력함 */
#define LOGM_LEVEL__INFO			5
/*! 디버깅시 필요한 정보까지 모두 출력함 */
#define LOGM_LEVEL__DEBUG			6
/*! 기타 상세 정보까지 모두 출력함 */
#define LOGM_LEVEL__VERBOSE			7
/*! 레벨 끝 */
#define LOGM_LEVEL__END				8


/*! 카테고리 설정 */
#define LOGM_CATEGORY				LOGM_CATEGORY__NONE
/*! 레벨 설정 */
#define LOGM_LEVEL					LOGM_LEVEL__WARNING
/*! 테그 설정 */
#define LOGM_TAG					NULL


#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)


/*!
 * 기록할 메시지 수준을 설정하는 함수
 *
 * @param	category 메시지 분류 번호 (-1은 모든 분류)
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
 * @param func		메시지를 출력하는 함수 이름
 *
 * @param line		메시지를 출력하는 줄 수
 *
 * @param msg		메시지
 *
 * @return			기록한 메시지 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
int logm_println(int category, int level, const char * tag, const char * func, int line, const char * msg);

/*!
 * 메시지를 기록하는 함수
 *
 * @param category	메시지 분류 번호
 *
 * @param level		메시지 수준
 *
 * @param tag		메시지 테그
 *
 * @param func		메시지를 출력하는 함수 이름
 *
 * @param line		메시지를 출력하는 줄 수
 *
 * @param format	메시지 형식
 *
 * @param ...		메시지에 포함될 데이터들
 *
 * @return			기록한 메시지 길이<br>
 * 					<br>
 *                 -1: 오류<br>
 */
int logm_printfln(int category, int level, const char * tag, const char * func, int line, const char * format, ...);


/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 설정 수준) */
#define logm (msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL,          LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logma(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__ALWAYS,  LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmt(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__FATAL,   LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logme(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__ERROR,   LOGM_TAG, __FUNCTION__, __LINE__, msg)
/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */

#define logmw(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__WARNING, LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmi(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__INFO,    LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmd(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__DEBUG,   LOGM_TAG, __FUNCTION__, __LINE__, msg)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__VERBOSE 수준) */
#define logmv(msg) logm_println(LOGM_CATEGORY, LOGM_LEVEL__VERBOSE, LOGM_TAG, __FUNCTION__, __LINE__, msg)


/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 설정 수준) */
#define logmf (format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL,            LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ALWAYS 수준) */
#define logmfa(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__ALWAYS,    LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__FATAL 수준) */
#define logmft(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__FATAL,     LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__ERROR 수준) */
#define logmfe(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__ERROR,     LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__WARNING 수준) */
#define logmfw(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__WARNING,   LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__INFO 수준) */
#define logmfi(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__INFO,      LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__DEBUG 수준) */
#define logmfd(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__DEBUG,     LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__VERBOSE 수준) */
#define logmfv(format, args...) logm_printfln(LOGM_CATEGORY, LOGM_LEVEL__VERBOSE,   LOGM_TAG, __FUNCTION__, __LINE__, format, ## args)


#else /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */


/*!
 * 기록할 메시지 수준을 설정하는 함수
 *
 * @param	category 메시지 분류 번호 (-1은 모든 분류)
 *
 * @param	level    기록할 메시지 수준 (설정한 수준 이상(같거나 작은 값)의 메시지만 기록됨)
 *
 * @return	설정한 기록할 메시지 수준<br>
 * 			<br>
 * 			 -1: 오류<br>
 * 			 -n: n-1 번째 매개변수가 잘못되었음<br>
 */
#define logm_setlevel(category, level) ((void) (LOGM_LEVEL__NONE))

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
#define logm_getlevel(category) ((void) (LOGM_LEVEL__NONE))


/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 설정 수준) */
#define logm (msg)

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

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__VERBOSE 수준) */
#define logmv(msg)


/*! 메시지를 기록하는 매크로 (LOGM_LEVEL 설정 수준) */
#define logmf (format, args...)

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

/*! 메시지를 기록하는 매크로 (LOGM_LEVEL__VERBOSE 수준) */
#define logmfv(format, args...)


#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

#ifdef	__cplusplus
}
#endif

#endif /* UBICLIB_LOGM_H_ */
