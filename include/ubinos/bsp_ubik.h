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

#ifndef UBINOS_BSP_UBIK_H_
#define UBINOS_BSP_UBIK_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file bsp.h
 *
 * @brief BSP UBIK (Board Support Package for Kernel) API
 *
 * BSP 에서 사용하는 Kernel 인터페이스를 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

void bsp_ubik_entercrit(void);
void bsp_ubik_exitcrit(void);

typedef void * bsp_mutex_pt;
int bsp_mutex_create(bsp_mutex_pt * bsp_mutex_p);
int bsp_mutex_delete(bsp_mutex_pt * bsp_mutex_p);
int bsp_mutex_lock(bsp_mutex_pt bsp_mutex);
int bsp_mutex_lock_timed(bsp_mutex_pt bsp_mutex, unsigned int tick);
int bsp_mutex_unlock(bsp_mutex_pt bsp_mutex);

void * bsp_task_getcur();
int bsp_task_sleepms(unsigned int timems);

int bsp_ubik_isrt(void);
int bsp_ubik_iscrit(void);

void bsp_ubik_task_schedule_irq();

void bsp_ubik_swisr(unsigned int swino);

#if (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1)

void __attribute__((naked)) bsp_ubik_psv_handler(void);

void bsp_ubik_swi_handler(void);
void bsp_ubik_systick_handler(void);
void bsp_ubik_irq_handler(void);

#endif /* (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1) */

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_BSP_UBIK_H_ */
