/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the lib_ubik_port_arm_sam7x256ek component of the Ubinos.

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
#if (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1)

#include <assert.h>

void ubik_entercrit(void) {
	ARM_INTERRUPT_DISABLE();
	_bsp_critcount++;
}

void ubik_exitcrit(void) {
	if (0 == _bsp_critcount) {
		dtty_puts("\r\nubik_exitcrit fail (_bsp_critcount is already 0)\r\n", 80);
		bsp_abortsystem();
	}
	_bsp_critcount--;
	if (0 == _bsp_critcount) {
		ARM_INTERRUPT_ENABLE();
	}
}

#if (__FPU_USED == 1)

#define save_context() {                                                    \
    __asm__ __volatile__ (                                                  \
        "mov        r3, %0                                          \n\t"   \
        "msr        basepri, r3                                     \n\t"   \
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
        :: "i" (NVIC_BASEPRI_REAL)                                          \
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
        /* Restore basepri from _bsp_critcount */                           \
        "cmp        r2, #0                                          \n\t"   \
        "ite        eq                                              \n\t"   \
        "moveq      r3, #0                                          \n\t"   \
        "movne      r3, %0                                          \n\t"   \
        "msr        basepri, r3                                     \n\t"   \
        :: "i" (NVIC_BASEPRI_REAL)                                          \
    );                                                                      \
}

#else

#define save_context() {                                                    \
    __asm__ __volatile__ (                                                  \
        "mov        r3, %0                                          \n\t"   \
        "msr        basepri, r3                                     \n\t"   \
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
        :: "i" (NVIC_BASEPRI_REAL)                                          \
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
        /* Restore basepri from _bsp_critcount */                           \
        "cmp        r2, #0                                          \n\t"   \
        "ite        eq                                              \n\t"   \
        "moveq      r3, #0                                          \n\t"   \
        "movne      r3, %0                                          \n\t"   \
        "msr        basepri, r3                                     \n\t"   \
        :: "i" (NVIC_BASEPRI_REAL)                                          \
    );                                                                      \
}

#endif

void __attribute__((naked)) bsp_ubik_psv_handler(void) {
    save_context();
    __asm__ __volatile__ (
        "push       {lr}                                            \n\t"
    );

	_task_prev = _task_cur;
	if(TASK_STATE__RUNNING == _task_cur->state) {
		_task_cur->state = TASK_STATE__READY;
	}
	_task_cur = _tasklist_getcurnext(_task_list_ready_cur);
	_task_cur->state = TASK_STATE__RUNNING;

    __asm__ __volatile__ (
        "pop        {lr}                                            \n\t"
    );
    restore_context();
    __asm__ __volatile__ (
        "bx         lr                                              \n\t"
    );
}

void bsp_ubik_swi_handler(void) {
    unsigned int swino;

    __asm__ __volatile__ (
        /* Set r0 to task stack */
        "tst        lr, #4                                          \n\t"
        "ite        eq                                              \n\t"
        "mrseq      r0, msp                                         \n\t"
        "mrsne      r0, psp                                         \n\t"
        /* Set r0 to swino */
        "ldr        r0, [r0, #24]                                   \n\t"
        "subs       r0, r0, #2                                      \n\t"
        "ldrb       r0, [r0]                                        \n\t"
        "mov        %0, r0                                          \n\t"
        : "=r" (swino)
    );

    switch(swino) {
	case SWINO__TASK_YIELD:
        if (0 == _ubik_tasklockcount && 0 != _bsp_kernel_active) {
			arm_set_pendsv();
        }
		break;
	default:
		break;
	}
}

void bsp_ubik_tick_handler(void) {
#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)
#if (UBINOS__UBIK__TICK_RTC_CHECK == 1)
	unsigned int tickrtccount;
	unsigned int tickrtccount_diff;
	unsigned int i;
#endif /* (UBINOS__UBIK__TICK_RTC_CHECK == 1) */
#else
    unsigned int    status = 0;
#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */
    edlist_pt       tempedlist;
    _task_pt        task;
    #if !(UBINOS__UBIK__EXCLUDE_STIMER == 1)
    _stimer_pt      stimer;
    #endif /* !(UBINOS__UBIK__EXCLUDE_STIMER == 1) */
    _wtask_pt       wtask;
    _sigobj_pt      sigobj;
    int             j;

#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)

	_ubik_tick_rtcisr_clear();

	if (_bsp_kernel_active != 0) {

#if (UBINOS__UBIK__TICK_RTC_CHECK == 1)

		tickrtccount = _ubik_tick_rtccount_get();
		if (_ubik_tickrtccount_init) {
			if (_ubik_tickrtccount < tickrtccount) {
				tickrtccount_diff = tickrtccount - _ubik_tickrtccount;
			}
			else {
				tickrtccount_diff = tickrtccount + (UBINOS__UBIK__TICK_RTC_COUNT_MAX - _ubik_tickrtccount) + 1;
			}
		}
		else {
			tickrtccount_diff = 1;
			_ubik_tickrtccount_init = 1;
		}
		_ubik_tickrtccount = tickrtccount;

#if (UBINOS__UBIK__TICK_RTC_CHECK_TYPE == UBINOS__UBIK__TICK_RTC_CHECK_TYPE__CORRECT)

		for (i = 0; i < tickrtccount_diff; i++) {

#elif (UBINOS__UBIK__TICK_RTC_CHECK_TYPE == UBINOS__UBIK__TICK_RTC_CHECK_TYPE__ABORT)

		(void) i;
		if (tickrtccount_diff != 1) {
			dtty_puts("\r\nrtc tick check fail\r\n", 80);
			bsp_abortsystem();
		}

		{

#else

	#error "Unsupported UBINOS__UBIK__TICK_RTC_CHECK_TYPE"

#endif /* (UBINOS__UBIK__TICK_RTC_CHECK_TYPE == UBINOS__UBIK__TICK_RTC_CHECK_TYPE__CORRECT) */

#else

		{

#endif /* (UBINOS__UBIK__TICK_RTC_CHECK == 1) */

#else

	if (_bsp_kernel_active != 0) {

		status = SysTick->CTRL;
		if (0 != (0x00010000 & status)) {

#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */

			ARM_INTERRUPT_DISABLE();

			////////////////

			_ubik_tickcount++;

			////////////////

			if (0 == _ubik_tickcount) {
				_ubik_tickcounth++;

				tempedlist                      = _task_list_blocked_timed_cur;
				_task_list_blocked_timed_cur    = _task_list_blocked_timed_next;
				_task_list_blocked_timed_next   = tempedlist;

				#if !(UBINOS__UBIK__EXCLUDE_STIMER == 1)
				tempedlist                      = _stimer_list_cur;
				_stimer_list_cur                = _stimer_list_next;
				_stimer_list_next               = tempedlist;
				#endif
			}

			for (;;) {
				task = _tasklist_head(_task_list_blocked_timed_cur);
				if (NULL != task && _ubik_tickcount >= task->wakeuptick) {
					for (j=0; j<task->wtask_count; j++) {
						wtask = &task->wtask_p[j];
						sigobj = _sigobj_wtasklist_owner(wtask);
						if (NULL != sigobj) {
							wtask->sigtype  = SIGOBJ_SIGTYPE__TIMEOUT;
							task->wtask_recvcount++;
							_sigobj_wtasklist_remove(wtask);
							_sigobj_wtasklist_notifychange(sigobj);
						}
					}
					task->state             = TASK_STATE__READY;
					task->wakeuptick        = 0;
					_task_changelist(task);
				}
				else {
					break;
				}
			}

#if !(UBINOS__UBIK__EXCLUDE_STIMER == 1)
			for (;;) {
				stimer = _stimerlist_head(_stimer_list_cur);
				if (NULL != stimer && _ubik_tickcount >= stimer->wakeuptick) {
					switch (stimer->sigobj->type) {
					case OBJTYPE__UBIK_SEM:
						sem_give((sem_pt) stimer->sigobj);
						if (0 == stimer->oneshot) {
							_stimerlist_add(stimer);
						}
						else {
							_stimerlist_remove(stimer);
							stimer->running = 0;
						}
						break;
					case OBJTYPE__UBIK_SIGNAL:
						if (0 == stimer->broadcast) {
							signal_send((signal_pt) stimer->sigobj, stimer->sigtype);
						} else {
							signal_broadcast((signal_pt) stimer->sigobj, stimer->sigtype);
						}
						if (0 == stimer->oneshot) {
							_stimerlist_add(stimer);
						}
						else {
							_stimerlist_remove(stimer);
							stimer->running = 0;
						}
						break;
					default:
						_stimerlist_remove(stimer);
						stimer->running = 0;
						break;
					}
				}
				else {
					break;
				}
			}
#endif /* !(UBINOS__UBIK__EXCLUDE_STIMER == 1) */

			ARM_INTERRUPT_ENABLE();

			////////////////

#if !(UBINOS__UBIK__EXCLUDE_TICK_HOOKFUNC == 1)
			if (NULL != _ubik_tickhookfunc_func) {
				_ubik_tickhookfunc_func();
			}
#endif /* !(UBINOS__UBIK__EXCLUDE_TICK_HOOKFUNC == 1) */

			////////////////

			if (0 == _ubik_tasklockcount) {
				arm_set_pendsv();
			}

			//////////////////
		}
	}
}

void bsp_ubik_irq_handler(void) {
    unsigned int exceptiontype;

    __asm__ __volatile__ (
        "mrs        %0, ipsr                                        \n\t"
        : "=r" (exceptiontype)
    );

    dtty_puts("\r\n\r\nunknown exception (", 80);
    switch (exceptiontype) {
    default:
    	if (exceptiontype >= 100) {
            dtty_putc((int) ((exceptiontype / 100 % 10) + '0'));
    	}
    	if (exceptiontype >= 10) {
            dtty_putc((int) ((exceptiontype / 10 % 10) + '0'));
    	}
    	dtty_putc((int) ((exceptiontype % 10) + '0'));
        break;
    }
    dtty_puts(")\r\n", 80);
    bsp_abortsystem();
}


void task_comp_start(void) {
	/* Enable interrupt */
    __disable_irq();
    __set_BASEPRI(0);

    // Make sure in thread (not in ISR).
    assert((__get_IPSR() & IPSR_ISR_Msk) == 0);
    // Make sure in privledged.
    assert((__get_CONTROL() & CONTROL_nPRIV_Msk) == 0);
    // Make sure using MSP stack.
    assert((__get_CONTROL() & CONTROL_SPSEL_Msk) == 0);
#if (__FPU_USED == 1)
    // Make sure FP extension is not active.
    assert((__get_CONTROL() & CONTROL_FPCA_Msk) == 0);
#endif
    // Make sure that interrupt is disabled.
    assert(__get_PRIMASK() == 1);

    _bsp_kernel_active = 1;

    _task_cur->state = TASK_STATE__RUNNING;

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

        /* Pop r0~r3, r12, lr, xpsr */
        "ldr        r0, [sp, #28]                                   \n\t"
        "msr        apsr_nzcvq , r0                                 \n\t"
        "ldr        r0, [sp, #24]                                   \n\t"
        "str        r0, [sp, #28]                                   \n\t"
        "pop        {r0-r3, r12, lr}                                \n\t"
        "add        sp, sp, #4                                      \n\t"

        /* Enable interrupt and pop pc */
        "cpsie      i                                               \n\t"
        "pop        {pc}                                            \n\t"
    );
}

#endif /* (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1) */
#endif /* (INCLUDE__UBINOS__UBIK == 1) */


