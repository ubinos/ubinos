/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _UBICLIB_H_
#define _UBICLIB_H_

/**
 * @file _ubiclib.h
 *
 * @brief ubiclib 컴포넌트 내부 인터페이스
 *
 * ubiclib 컴포넌트 내부 인터페이스를 정의합니다.
 */

#ifdef	__cplusplus
extern "C" {
#endif

#include <ubinos/bsp.h>
#include <ubinos/bsp_ubik.h>
#include <ubinos/ubik.h>
#include <ubinos/ubiclib.h>

/**
 * ubiclib port 컴포넌트를 초기화하는 함수
 *
 * 초기화 작업들 중 재진입(reenterance)을 지원하기 위한 부분은 수행하지 않습니다.
 * 재진입(reenterance)을 지원하려면 ubiclib_port_comp_init_reent 함수를 추가로 호출해 주어야 합니다.
 * 이 함수는 ubiclib_comp_init 함수에서 자동적으로 호출됩니다.
 *
 * @return	 0: 성공,<br>
 * 			-1: 오류
 */
int ubiclib_port_comp_init(void);

/**
 * ubiclib port 컴포넌트의 초기화 작업들 중 재진입(reenterance)을 지원하기 위한 부분을 수행하는 함수
 *
 * 이 함수는 ubiclib_comp_init_reent 함수에서 자동적으로 호출됩니다.
 *
 * @return	 0: 성공,<br>
 * 			-1: 오류
 */
int ubiclib_port_comp_init_reent(void);

#ifdef	__cplusplus
}
#endif

#endif /* _UBICLIB_H_ */
