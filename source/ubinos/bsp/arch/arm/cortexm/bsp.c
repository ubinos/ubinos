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
#if (UBINOS__BSP__CORTEX_MX == 1)

#include <stdio.h>

#if 	(0x50 > UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN)
#error "UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN should be equal or larger than 0x50."
#endif

int bsp_comp_init(void) {
    int r = 0;

    _bsp_kernel_active = 0;
    _bsp_critcount = 0;

    r = dtty_init();
    if (0 != r) {
        return -1;
    }

    return 0;
}

int bsp_isintr(void) {
    if ((__get_IPSR() & IPSR_ISR_Msk) != 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void bsp_busywait(unsigned int count) {
    __asm__ __volatile__ (
            "cmp    r0, #0                                      \n\t"
            "beq    2f                                          \n\t"
            "nop                                                \n\t"
            "nop                                                \n\t"
            "1:                                                 \n\t"
            "subs   r0, r0, #1                                  \n\t"
            "bne    1b                                          \n\t"
            "2:                                                 \n\t"
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
    register unsigned int value;
    __asm__ __volatile__ ("mrc p15, 0, %0, c1, c0, 0" : "=r" (value));
    return value;
}

void arm_set_cp15(unsigned int value) {
    __asm__ __volatile__ ("mcr p15, 0, %0, c1, c0, 0" : : "r" (value));
}

unsigned int arm_get_xpsr(void) {
    register unsigned int value;
    __asm__ __volatile__ ("mrs %0, xpsr" : "=r" (value));
    return value;
}

unsigned int arm_get_apsr(void) {
    register unsigned int value;
    __asm__ __volatile__ ("mrs %0, apsr" : "=r" (value));
    return value;
}

unsigned int arm_get_ipsr(void) {
    register unsigned int value;
    __asm__ __volatile__ ("mrs %0, ipsr" : "=r" (value));
    return value;
}

unsigned int arm_get_epsr(void) {
    register unsigned int value;
    __asm__ __volatile__ ("mrs %0, epsr" : "=r" (value));
    return value;
}

void arm_set_pendsv(void) {
    SCB->ICSR = (1 << 28);
    __DSB();
    __ISB();
}

void arm_clear_pendsv(void) {
    SCB->ICSR = (1 << 27);
    __DSB();
    __ISB();
}

unsigned int arm_get_pendsv(void) {
    register unsigned int value;
    value = SCB->ICSR;
    return (value >> 28);
}

void arm_set_svcpend(void) {
    SCB->SHCSR = (1 << 15);
    __DSB();
    __ISB();
}

unsigned int arm_get_svcpend(void) {
    register unsigned int value;
    value = SCB->SHCSR;
    return (value >> 15);
}

#endif /* (UBINOS__BSP__CORTEX_MX == 1) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

