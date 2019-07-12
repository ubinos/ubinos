/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the bsp_sam9xe512ek component of the Ubinos.

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

#include "../_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM9XE512)

#include "board_memories.h"

#pragma GCC push_options
#pragma GCC target ("arm")
#pragma GCC optimize ("O0")

void SystemInit(void) {
	unsigned int reg;

	/* Remap the memory */
    extern unsigned int relocated_isr_vector_start  __asm__ ("__relocated_isr_vector_start__");
    extern unsigned int ram_start            __asm__ ("__ram_start__");
	if (&relocated_isr_vector_start == &ram_start) {
		AT91C_BASE_MATRIX->MATRIX_MRCR = (AT91C_MATRIX_RCA926I | AT91C_MATRIX_RCA926D);
	}
	else {
		AT91C_BASE_MATRIX->MATRIX_MRCR = 0x00000000;
	}

    reg = arm_get_cp15();

#if (UBINOS__BSP__USE_MMU == 1)
    /* Enable MMU */
    reg |= (0x1 <<  0);
#endif

#if (UBINOS__BSP__USE_ICACHE == 1)
    /* Enable i-cache */
    reg |= (0x1 << 12);
#endif

#if (UBINOS__BSP__USE_DCACHE == 1)
    /* Enable d-cache */
    reg |= (0x1 <<  2);
#endif

    arm_set_cp15(reg);
}

#pragma GCC pop_options

#endif /* (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM9XE512) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

