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
#if (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1)

#if (UBINOS__BSP__USE_RELOCATED_ISR_VECTOR == 1)

int intr_connectisr(int no, isr_ft isr, int priority, unsigned int option) {
    void ** isr_vector_ptr = 0;
    extern unsigned int relocated_isr_vector_start       __asm__ ("__relocated_isr_vector_start__");

    if (NVIC_IRQN_START > no || NVIC_IRQN_END < no) {
        return -2;
    }
    if (NVIC_PRIO_LOWEST < priority || NVIC_PRIO_HIGHEST > priority) {
        return -3;
    }

    /* Disable the interrupt on the interrupt controller */
    NVIC_DisableIRQ(no);

    /* Clear the Pending Register on the interrupt controller */
    NVIC_ClearPendingIRQ(no);

    /* Set the interrupt priority */
    NVIC_SetPriority(no, priority);

    /* Register the interrupt handler on the interrupt handler table */
    isr_vector_ptr = (void **) &relocated_isr_vector_start;
    isr_vector_ptr[16 + no] = isr;

    return 0;
}

#endif /* (UBINOS__BSP__USE_RELOCATED_ISR_VECTOR == 1) */

int intr_enable(int no) {
    NVIC_EnableIRQ(no);
    return 0;
}

int intr_disable(int no) {
    NVIC_DisableIRQ(no);
    return 0;
}

int intr_clearpending(int no) {
    NVIC_ClearPendingIRQ(no);
    return 0;
}

int intr_gethighestpriority(void) {
    return NVIC_PRIO_HIGHEST;
}

int intr_getlowestpriority(void) {
    return NVIC_PRIO_LOWEST;
}

#endif /* (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

