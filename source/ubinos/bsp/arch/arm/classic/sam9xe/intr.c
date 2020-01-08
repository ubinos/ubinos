/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the bsp_sam... component of the Ubinos.

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

int intr_connectisr(int no, isr_ft isr, int priority, unsigned int option) {
    unsigned int mask;
    unsigned int type;

    mask = 0x1 << no;

	if (0 != (option & INTR_OPT__LEVEL)) {
		if (0 != (option & INTR_OPT__HIGH)) {
			type = (0x2<<5);
		}
		else {
			type = (0x0<<5);
		}
	}
	else {
		if (0 != (option & INTR_OPT__HIGH)) {
			type = (0x3<<5);
		}
		else {
			type = (0x1<<5);
		}
	}

	type |= (AT91C_AIC_PRIOR & priority);

    /* Disable the interrupt on the interrupt controller */
    AT91C_BASE_AIC->AIC_IDCR = mask;

    /* Save the interrupt handler routine pointer and the interrupt priority */
    AT91C_BASE_AIC->AIC_SVR[no] = (unsigned int) isr;

    /* Store the Source Mode Register */
    AT91C_BASE_AIC->AIC_SMR[no] = type;

    /* Clear the interrupt on the interrupt controller */
    AT91C_BASE_AIC->AIC_ICCR = mask;

	return 0;
}

int intr_enable(int no) {
    AT91C_BASE_AIC->AIC_IECR = 1 << no;
	return 0;
}

int intr_disable(int no) {
    AT91C_BASE_AIC->AIC_IDCR = 1 << no;
	return 0;
}

int intr_gethighestpriority(void) {
	return AT91C_AIC_PRIOR_HIGHEST;
}

int intr_getlowestpriority(void) {
	return AT91C_AIC_PRIOR_LOWEST;
}

#endif /* (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM9XE512) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

