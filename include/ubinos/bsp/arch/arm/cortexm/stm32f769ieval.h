/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam3s4ek component of the Ubinos.

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

#ifndef UBINOS_BSP_ARM_CORTEXM_STM32F769IEVAL_H_
#define UBINOS_BSP_ARM_CORTEXM_STM32F769IEVAL_H_

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * @file _board.h
 *
 * @brief BOARD definition
 *
 * Board 관련 정의
 */

#include <ubinos_config.h>
#include <ubinos/bsp/intr.h>

#if (UBINOS__BSP__CPU_MODEL__STM32F769 == 1)
#include "stm32f7/stm32f7xx.h"
#else
#error "Unsupported UBINOS__BSP__CPU_MODEL"
#endif

/* Common definition for ARM Cortex M*/

#define SWINO__TASK_YIELD	1

#define NVIC_IRQN_REAL_TO_CMSISAPI(irqn)	(irqn - 16)
#define NVIC_IRQN_CMSISAPI_TO_REAL(irqn)	(irqn + 16)

#define NVIC_IRQN_START		0
#define NVIC_IRQN_END		109

#define NVIC_PRIO_GROUP		0

#define NVIC_PRIO_REAL_TO_CMSISAPI(prio)	((prio >> (8 - __NVIC_PRIO_BITS)) & 0xff)
#define NVIC_PRIO_CMSISAPI_TO_REAL(prio)	((prio << (8 - __NVIC_PRIO_BITS)) & 0xff)

/* Priority: 0 ~ ((1 << __NVIC_PRIO_BITS) - 1) = 0 ~ 15 */
#define NVIC_PRIO_HIGHEST	1
#define NVIC_PRIO_MIDDLE	8
#define NVIC_PRIO_LOWEST	14

#define NVIC_PRIO_PENDSV	(NVIC_PRIO_LOWEST  + 1)
#define NVIC_PRIO_SYSTICK	(NVIC_PRIO_MIDDLE  - 1)
#define NVIC_PRIO_SVC		(NVIC_PRIO_MIDDLE)

#define NVIC_BASEPRI		NVIC_PRIO_HIGHEST
#define NVIC_BASEPRI_REAL	NVIC_PRIO_CMSISAPI_TO_REAL(NVIC_BASEPRI)

#define ARM_INTERRUPT_ENABLE() {		\
	__set_BASEPRI(0x00);				\
	__SEV();							\
	__DSB();							\
	__ISB();							\
}

#define ARM_INTERRUPT_DISABLE() {		\
	__set_BASEPRI(NVIC_BASEPRI_REAL);	\
	__SEV();							\
	__DSB();							\
	__ISB();							\
}

#define ARM_DATASYNC()  														\
	__asm__ __volatile__ (														\
		"dsb				 											\n\t"	\
	)

#if defined(__FPU_USED)
#define ARM_CONTEXT_SIZE    ((1 + 16 + 8 + 1 + 8 + 18) * 4) /* (stack frame type), (s16~s31), (r4~r11), (_bsp_critcount), (r0~r3, r12, lr, pc, xpsr), (aligner, s0~s15, fpscr) */
#else
#define ARM_CONTEXT_SIZE    ((8 + 1 + 8) * 4) /* (r4~r11), (_bsp_critcount), (r0~r3, r12, lr, pc, xpsr) */
#endif

#ifndef __ASSEMBLY__

unsigned int arm_get_cp15(void);
void arm_set_cp15(unsigned int value);
unsigned int arm_get_xpsr(void);
unsigned int arm_get_apsr(void);
unsigned int arm_get_ipsr(void);
unsigned int arm_get_epsr(void);

void arm_set_pendsv(void);
void arm_clear_pendsv(void);
unsigned int arm_get_pendsv(void);
void arm_set_svcpend(void);
unsigned int arm_get_svcpend(void);

#endif /* __ASSEMBLY__ */

/* Platform specific definition */

//#define NRF_CHIP_ID__STM32F217IG	0x0005283241414242 // STM32F217IG

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_BSP_ARM_CORTEXM_STM32F769IEVAL_H_ */

