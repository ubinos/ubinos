/*
  Copyright (C) 2011 RTLab, Yu Jin Park, Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the lib_ubik_armcortexm component of the Ubinos.

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


#include "../../../_ubik.h"

#if (INCLUDE__UBINOS__UBIK == 1)
#if (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__CORTEX_M4)

#include <assert.h>

void ubik_entercrit(void) {
    if (0 == bsp_isintr()) {
        ARM_INTERRUPT_DISABLE();
        _bsp_critcount++;
    }
}

void ubik_exitcrit(void) {
    if (0 == bsp_isintr()) {
        if (0 == _bsp_critcount) {
            dtty_puts("\r\nubik_exitcrit fail (_bsp_critcount is already 0)\r\n", 80);
            bsp_abortsystem();
        }
        _bsp_critcount--;
        if (0 == _bsp_critcount && 0 != _bsp_kernel_active) {
            ARM_INTERRUPT_ENABLE();
        }
    }
}

#if (__FPU_USED == 1)

#define save_context() {                                                    \
    __asm__ __volatile__ (                                                  \
        /* Set r3 to psp */                                                 \
        "mrs        r3, psp                                         \n\t"   \
        /* Save _bsp_critcount into psp stack */                            \
        "ldr        r2, =_bsp_critcount                             \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "stmdb      r3!, {r2}                                       \n\t"   \
        /* Save r4-r11 into psp stack */                                    \
        "stmdb      r3!, {r4-r11}                                   \n\t"   \
        /* Save FPU registers and stack frame type */                       \
        "and        r2, lr, #0x10                                   \n\t"   \
        "cmp        r2, #0                                          \n\t"   \
        "it         eq                                              \n\t"   \
        "vstmdbeq   r3!, {s16-s31}                                  \n\t"   \
        "stmdb      r3!, {r2}                                       \n\t"   \
        /* Save r3(psp) to _task_cur->stacktop */                           \
        "ldr        r2, =_task_cur                                  \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "str        r3, [r2, #4]                                    \n\t"   \
    );                                                                      \
}
#define restore_context() {                                                 \
    __asm__ __volatile__ (                                                  \
        /* Restore r3(psp) from _task_cur->stacktop */                      \
        "ldr        r2, =_task_cur                                  \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "ldr        r3, [r2, #4]                                    \n\t"   \
        /* Restore FPU registers and stack frame type */                    \
        "ldmia      r3!, {r2}                                       \n\t"   \
        "cmp        r2, #0                                          \n\t"   \
        "itte       eq                                              \n\t"   \
        "vldmiaeq   r3!, {s16-s31}                                  \n\t"   \
        "bfceq      lr, #4, #1                                      \n\t"   \
        "orrne      lr, r2                                          \n\t"   \
        /* Restore r4-r11 from psp stack */                                 \
        "ldmia      r3!, {r4-r11}                                   \n\t"   \
        /* Restore _bsp_critcount from psp stack */                         \
        "ldmia      r3!, {r2}                                       \n\t"   \
        "ldr        r1, =_bsp_critcount                             \n\t"   \
        "str        r2, [r1]                                        \n\t"   \
        /* Set r3 to psp */                                                 \
        "msr        psp, r3                                         \n\t"   \
        /* Restore primask from _bsp_critcount */                           \
        "cmp        r2, #0                                          \n\t"   \
        "ite        eq                                              \n\t"   \
        "moveq      r1, #0                                          \n\t"   \
        "movne      r1, %0                                         \n\t"   \
        "msr        basepri, r1                                     \n\t"   \
        :: "i" (NVIC_BASEPRI)                                               \
    );                                                                      \
}

#else

#define save_context() {                                                    \
    __asm__ __volatile__ (                                                  \
        /* Set r3 to psp */                                                 \
        "mrs        r3, psp                                         \n\t"   \
        /* Save _bsp_critcount into psp stack */                            \
        "ldr        r2, =_bsp_critcount                             \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "stmdb      r3!, {r2}                                       \n\t"   \
        /* Save r4-r11 into psp stack */                                    \
        "stmdb      r3!, {r4-r11}                                   \n\t"   \
        /* Save r3(psp) to _task_cur->stacktop */                           \
        "ldr        r2, =_task_cur                                  \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "str        r3, [r2, #4]                                    \n\t"   \
    );                                                                      \
}
#define restore_context() {                                                 \
    __asm__ __volatile__ (                                                  \
        /* Restore r3(psp) from _task_cur->stacktop */                      \
        "ldr        r2, =_task_cur                                  \n\t"   \
        "ldr        r2, [r2]                                        \n\t"   \
        "ldr        r3, [r2, #4]                                    \n\t"   \
        /* Restore r4-r11 from psp stack */                                 \
        "ldmia      r3!, {r4-r11}                                   \n\t"   \
        /* Restore _bsp_critcount from psp stack */                         \
        "ldmia      r3!, {r2}                                       \n\t"   \
        "ldr        r1, =_bsp_critcount                             \n\t"   \
        "str        r2, [r1]                                        \n\t"   \
        /* Set r3 to psp */                                                 \
        "msr        psp, r3                                         \n\t"   \
        /* Restore primask from _bsp_critcount */                           \
        "cmp        r2, #0                                          \n\t"   \
        "ite        eq                                              \n\t"   \
        "moveq      r1, #0                                          \n\t"   \
        "movne      r1, %0                                         \n\t"   \
        "msr        basepri, r1                                     \n\t"   \
        :: "i" (NVIC_BASEPRI)                                               \
    );                                                                      \
}

#endif

void __attribute__((naked)) bsp_ubik_irq_handler(void) {
    unsigned int exceptiontype;

    __asm__ __volatile__ (
        "push       {lr}                                            \n\t"
    );

    __asm__ __volatile__ (
        "mrs        r0, ipsr                                        \n\t"
        "mov        %0, r0                                          \n\t"
        : "=r" (exceptiontype)
    );

    dtty_puts("\r\n\r\nunknown exception (", 80);
    switch (exceptiontype) {
    default:
        dtty_putc((int) (exceptiontype + '0'));
        break;
    }
    dtty_puts(")\r\n", 80);
    bsp_abortsystem();

    __asm__ __volatile__ (
        "pop        {lr}                                            \n\t"
    );
    restore_context();
    __asm__ __volatile__ (
        "bx         lr                                              \n\t"
    );
}

void __attribute__((naked)) bsp_ubik_swi_handler(void) {
    unsigned int swino;

    __asm__ __volatile__ (
        /* Set r1 to task stack */
        "mrs        r0, psp                                         \n\t"
        /*Set r1 to swino */
        "ldr        r0, [r0, #24]                                   \n\t"
        "ldrb       r0, [r0, #-2]                                   \n\t"
    );

    save_context();

    __asm__ __volatile__ (
        "push       {lr}                                            \n\t"
        "mov        %0, r0                                          \n\t"
        : "=r" (swino)
    );
    _ubik_swisr(swino);

    __asm__ __volatile__ (
        "pop        {lr}                                            \n\t"
    );
    restore_context();
    __asm__ __volatile__ (
        "bx         lr                                              \n\t"
    );
}

void __attribute__((naked)) bsp_ubik_psv_handler(void) {
    save_context();
    __asm__ __volatile__ (
        "push       {lr}                                            \n\t"
    );

    _ubik_swisr(SWINO__TASK_YIELD);

    __asm__ __volatile__ (
        "pop        {lr}                                            \n\t"
    );
    restore_context();
    __asm__ __volatile__ (
        "bx         lr                                              \n\t"
    );
}

void __attribute__((naked)) bsp_ubik_systick_handler(void) {
    save_context();
    __asm__ __volatile__ (
        "push       {lr}                                            \n\t"
    );

    _ubik_tickisr();

    __asm__ __volatile__ (
        "pop        {lr}                                            \n\t"
    );
    restore_context();
    __asm__ __volatile__ (
        "bx         lr                                              \n\t"
    );
}


void task_comp_start(void) {
    // Make sure in thread (not in ISR).
    assert((__get_IPSR() & IPSR_ISR_Msk) == 0);
    // Make sure in privledged.
    assert((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    // Make sure using MSP stack.
    assert((__get_CONTROL() & CONTROL_SPSEL_Msk) == 0);
    // Make sure FP extension is not active.
    assert((__get_CONTROL() & CONTROL_FPCA_Msk) == 0);
    // Make sure that interrupt is disabled.
    assert(__get_PRIMASK() == 1);

    _bsp_kernel_active = 1;

    _task_cur->state = TASK_STATE__RUNNING;

    ARM_INTERRUPT_ENABLE();

    __asm__ __volatile__ (
        /* Restore r3(psp) from _task_cur->stacktop */
        "ldr        r2, =_task_cur                                  \n\t"
        "ldr        r2, [r2]                                        \n\t"
        "ldr        r3, [r2, #4]                                    \n\t"
#if (__FPU_USED == 1)
        /* Restore FPU registers and stack frame type */
        "ldmia      r3!, {r2}                                       \n\t"
        "cmp        r2, #0                                          \n\t"
        "itte       eq                                              \n\t"
        "vldmiaeq   r3!, {s16-s31}                                  \n\t"
        "bfceq      lr, #4, #1                                      \n\t"
        "orrne      lr, r2                                          \n\t"
#endif
        /* Restore r4-r11 from psp stack */
        "ldmia      r3!, {r4-r11}                                   \n\t"
        /* Restore _bsp_critcount from psp stack */
        "ldmia      r3!, {r2}                                       \n\t"
        "ldr        r1, =_bsp_critcount                             \n\t"
        "str        r2, [r1]                                        \n\t"
        /* Set r3 to psp */
        "msr        psp, r3                                         \n\t"

        /* Use psp */
        "mrs        r3, control                                     \n\t"
        "orr        r3, r3, #2                                      \n\t"
        "msr        control, r3                                     \n\t"
        "isb                                                        \n\t"
        /* Reset msp */
        "ldr        r3, =__stack_top__                              \n\t"
        "msr        msp, r3                                         \n\t"

        /* Pop r0~r3, r12, lr, pc, xpsr and enable interrupt */
        "ldr        r0, [sp, #28]                                   \n\t"
        "msr        apsr_nzcvq , r0                                 \n\t"
        "ldr        r0, [sp, #24]                                   \n\t"
        "str        r0, [sp, #28]                                   \n\t"
        "pop        {r0-r3, r12, lr}                                \n\t"
        "add        sp, sp, #4                                      \n\t"
        "cpsie      i                                               \n\t"
        "pop        {pc}                                            \n\t"
    );
}

#endif /* (UBINOS__BSP__CPU_TYPE == ...) */
#endif /* (INCLUDE__UBINOS__UBIK == 1) */


