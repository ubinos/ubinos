/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam7x256ek component of the Ubinos.

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

#ifndef UBINOS_BSP_ARCH_H_
#define UBINOS_BSP_ARCH_H_

#ifdef	__cplusplus
extern "C"
{
#endif

/*!
 * @file arch.h
 *
 * @brief Architecture definition
 *
 * Architecture 관련 내용을 정의합니다.
 */

#include <ubinos_config.h>
#include <ubinos/type.h>

#if   (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM7X256) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM7X512)
#include "arch/arm/classic/sam7xxxxek.h"
#elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM9XE512)
#include "arch/arm/classic/sam9xexxxek.h"
#elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM4SD32C)
#include "arch/arm/cortexm/sam4sek2.h"
#elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA)
#include "arch/arm/cortexm/nrf52dk.h"
#elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F217IG)
#include "arch/arm/cortexm/stm3221geval.h"
#else
#error "Unsupported UBINOS__BSP__CPU_MODEL"
#endif

#ifndef __ASSEMBLY__

extern volatile unsigned int _bsp_kernel_active; /* variable representing whether kernel is active or not */
extern volatile unsigned int _bsp_critcount; /* critical section nesting count */

#endif /* __ASSEMBLY__ */

#ifdef	__cplusplus
}
#endif

#endif /* UBINOS_BSP_ARCH_H_ */