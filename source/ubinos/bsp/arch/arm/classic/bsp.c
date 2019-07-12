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

#include "_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__ARM926EJ_S)

#include <stdio.h>

#if 	(0x50 > UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN)
	#error "UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN should be equal or larger than 0x50."
#endif

volatile unsigned int _bsp_intrcount = 0;

int bsp_comp_init(void) {
	int r = 0;

	_bsp_kernel_active	= 0;
	_bsp_critcount		= 0;

    _bsp_intrcount      = 0;

	r = dtty_init();
	if (0 != r) {
		return -1;
	}

	return 0;
}

int bsp_isintr(void) {
    if (0 == _bsp_intrcount) {
        return 0;
    } else {
        return 1;
    }
}

#pragma GCC push_options
#pragma GCC target ("arm")

void bsp_busywait(unsigned int count) {
    __asm__ __volatile__ (                                                  \
        "cmp    r0, #0                                              \n\t"   \
        "beq    2f                                                  \n\t"   \
        "1:                                                         \n\t"   \
        "subs   r0, r0, #1                                          \n\t"   \
        "bne    1b                                                  \n\t"   \
        "2:                                                         \n\t"   \
    );
}

void bsp_abortsystem(void) {
    ARM_INTERRUPT_DISABLE();

    dtty_puts("\r\n\r\nsystem is aborted\r\n\r\n", 80);

    __asm__ __volatile__ (
            "1:                                                 \n\t"
            "b  1b                                              \n\t"
    );
}

void bsp_enableintr(void) {
    ARM_INTERRUPT_ENABLE();
}

void bsp_disableintr(void) {
    ARM_INTERRUPT_DISABLE();
}

#define _exception_check_bsp_critcount() {                              \
    if (0 != _bsp_critcount) {                                          \
        dtty_puts("\r\ninterrupt disable fail\r\n", 80);        \
        bsp_abortsystem();                                              \
    }                                                                   \
}

void bsp_exception_handler(unsigned int exceptiontype, unsigned int swino) {
    isr_ft isr = 0;

    _bsp_intrcount++;

    switch (exceptiontype) {

    case EXCEPTION_TYPE_IRQ:

        isr = (isr_ft) AT91C_BASE_AIC->AIC_IVR;
        AT91C_BASE_AIC->AIC_IVR = 0;

        _exception_check_bsp_critcount();

        if (isr != (isr_ft) 0x0) {
            (*isr)();
        }

        bsp_ubik_task_schedule_irq();

        AT91C_BASE_AIC->AIC_EOICR = 0;

        break;

    case EXCEPTION_TYPE_SWI:

        bsp_ubik_swisr(swino);

        break;

    case EXCEPTION_TYPE_UND:
    case EXCEPTION_TYPE_PABT:
    case EXCEPTION_TYPE_DABT:
    case EXCEPTION_TYPE_FIQ:
    default:
        dtty_puts("\r\n\r\nunknown exception (", 80);
        switch (exceptiontype) {
        case EXCEPTION_TYPE_UND:
            dtty_puts("UND", 80);
            break;
        case EXCEPTION_TYPE_SWI:
            dtty_puts("SWI", 80);
            break;
        case EXCEPTION_TYPE_PABT:
            dtty_puts("PABT", 80);
            break;
        case EXCEPTION_TYPE_DABT:
            dtty_puts("DABT", 80);
            break;
        case EXCEPTION_TYPE_IRQ:
            dtty_puts("FIQ", 80);
            break;
        case EXCEPTION_TYPE_FIQ:
            dtty_puts("FIQ", 80);
            break;
        default:
            dtty_putc((int) (exceptiontype + '0'));
            break;
        }
        dtty_puts(")\r\n", 80);
        bsp_abortsystem();
        break;
    }

    _bsp_intrcount--;
}

void bsp_spurious_exception_handler(void) {
    dtty_puts("\r\n\r\nspurious interrupt\r\n", 80);
    bsp_abortsystem();
}

int bsp_getstacksize(int type, unsigned int * stacksize_p) {
    if (NULL == stacksize_p) {
        return -3;
    }

    *stacksize_p = __STACK_SIZE;

    return 0;
}

int bsp_getmaxstackusage(int type, unsigned int * maxstackusage_p) {
	if (NULL != maxstackusage_p) {
		*maxstackusage_p = 0;
	}

	return -1;
}

unsigned int bsp_getbusywaitcountperms(void) {
    return UBINOS__BSP__BUSYWAITCOUNT_PER_MS;
}

unsigned int bsp_timemstobwc(unsigned int timems) {
    return (timems * UBINOS__BSP__BUSYWAITCOUNT_PER_MS);
}

unsigned int bsp_bwctotimems(unsigned int count) {
    return (count / UBINOS__BSP__BUSYWAITCOUNT_PER_MS);
}


void bsp_busywaitms(unsigned int timems) {
    unsigned int count;

    count = bsp_timemstobwc(timems);
    if (count < timems) {
        count = UINT_MAX;
    }

    bsp_busywait(count);
}

unsigned int arm_get_cp15(void) {
    unsigned int value;
    __asm__ __volatile__ ("mrc p15, 0, %0, c1, c0, 0" : "=r" (value));
    return value;
}

void arm_set_cp15(unsigned int value) {
    __asm__ __volatile__ ("mcr p15, 0, %0, c1, c0, 0" : : "r" (value));
}

unsigned int arm_get_cpsr(void) {
    unsigned int value;
    __asm__ __volatile__ ("mrs %0, cpsr" : "=r" (value));
    return value;
}

#pragma GCC pop_options

#endif /* (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__ARM926EJ_S) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

