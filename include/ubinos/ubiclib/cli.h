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

#ifndef UBICLIB_CLI_H_
#define UBICLIB_CLI_H_

#ifdef	__cplusplu
extern "C" {
#endif

/*!
 * @file cli.h
 *
 * @brief ubiclib command line interface API
 *
 * ubiclib command line interface API를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

/** cli 후크 함수 포인터  형 정의 */
typedef int (*cli_hookfunc_ft)(char *str, int max, void *arg);

/** cli help 후크 함수 포인터  형 정의 */
typedef void (*cli_helphookfunc_ft)();

/**
 * 후크 함수를 등록하는 함수
 *
 * 사용자는 후크 함수를 이용해 cli에 원하는 기능을 추가할 수 있습니다.
 *
 * @param	후크 함수 포인터<br>
 *
 * @param	후크 함수가 호출될 때 전달할 인수<br>
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
int cli_sethookfunc(cli_hookfunc_ft hookfunc, void *arg);

/**
 * 도움말 후크 함수를 등록하는 함수
 *
 * 사용자는 도움말 후크 함수를 이용해 cli 도움말을 추가할 수 있습니다.
 *
 * @param	도움말 후크 함수 포인터<br>
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
int cli_sethelphookfunc(cli_helphookfunc_ft helphookfunc);

/**
 * 프로프트 문자열을 설정하는 함수
 *
 * @param	프롬프트 문자열<br>
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
int cli_setprompt(char *prompt);

/**
 * cli 메인 함수
 *
 * @param	사용자 정의 인수<br>
 *
 * @return	  0: 성공<br>
 * 			<br>
 * 			 -1: 오류<br>
 */
void cli_main(void *arg);

#ifdef	__cplusplus
}
#endif

#endif /* UBICLIB_CLI_H_ */
