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

#include "../../../../_ubik.h"

#if (INCLUDE__UBINOS__UBIK == 1)
#if (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1)
#if (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA)

#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)

#if !(INCLUDE__NRF5SDK == 1)
	#error "Project nrf5sdk is necessary to use RTC tick"
#endif

#include <nrf.h>
#include <nrf_gpio.h>
#include <nrf_drv_rtc.h>
#include <nrf_drv_clock.h>
#ifdef SOFTDEVICE_PRESENT
#include <nrf_sdh.h>
#endif
#include <boards.h>
#include <app_error.h>

#if (UBINOS__UBIK__TICK_RTC_NO == 0)
	#define _TICK_RTC NRF_RTC0
	#define _TICK_RTC_IRQ_NO RTC0_IRQn
#elif (UBINOS__UBIK__TICK_RTC_NO == 1)
	#define _TICK_RTC NRF_RTC1
	#define _TICK_RTC_IRQ_NO RTC1_IRQn
#elif (UBINOS__UBIK__TICK_RTC_NO == 2)
	#define _TICK_RTC NRF_RTC2
	#define _TICK_RTC_IRQ_NO RTC2_IRQn
#else
	#error "Unsupported UBINOS__UBIK__TICK_RTC_NO"
#endif

int _ubik_inittick(void) {
	ret_code_t err_code;
    int i;
    unsigned int tickpersec = 0;
    unsigned int prescaler = 0;

    __disable_irq();

    _ubik_tickcount = 0;
    _ubik_tickcounth = 0;

#if (UBINOS__UBIK__TICK_RTC_CHECK == 1)
    _ubik_tickrtccount = 0;
    _ubik_tickrtccount_init = 0;
#endif

    tickpersec = ubik_gettickpersec();
    prescaler = (32768 / tickpersec) - 1;

	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	nrf_drv_clock_lfclk_request(NULL);

	nrf_rtc_prescaler_set(_TICK_RTC, prescaler);
	nrf_rtc_int_enable(_TICK_RTC, RTC_INTENSET_TICK_Msk);
	nrf_rtc_task_trigger(_TICK_RTC, NRF_RTC_TASK_CLEAR);
	nrf_rtc_task_trigger(_TICK_RTC, NRF_RTC_TASK_START);

    // Set exception priority
    NVIC_SetPriorityGrouping(NVIC_PRIO_GROUP);
    for (i = NVIC_IRQN_START; i <= NVIC_IRQN_END; i++) {
        NVIC_SetPriority(i, NVIC_PRIO_LOWEST);
    }
    NVIC_SetPriority(SVCall_IRQn, NVIC_PRIO_SVC);
    NVIC_SetPriority(PendSV_IRQn, NVIC_PRIO_PENDSV);

    NVIC_SetPriority(_TICK_RTC_IRQ_NO, NVIC_PRIO_SYSTICK);
    NVIC_EnableIRQ(_TICK_RTC_IRQ_NO);

    return 0;
}

void _ubik_tick_rtcisr_clear(void) {
    nrf_rtc_event_clear(_TICK_RTC, NRF_RTC_EVENT_TICK);
}

unsigned int _ubik_tick_rtccount_get(void) {
	return nrf_rtc_counter_get(_TICK_RTC);
}

void _ubik_idle_cpu_sleep(void) {
    // Wait for an event.
#ifdef SOFTDEVICE_PRESENT
    if (nrf_sdh_is_enabled())
    {
        ret_code_t ret_code = sd_app_evt_wait();
        ASSERT((ret_code == NRF_SUCCESS) || (ret_code == NRF_ERROR_SOFTDEVICE_NOT_ENABLED));
        UNUSED_VARIABLE(ret_code);
    }
    else
#endif // SOFTDEVICE_PRESENT
    {
        // Wait for an event.
        __WFE();
        // Clear the internal event register.
        __SEV();
        __WFE();
    }
}

#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */

#endif /* (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA) */
#endif /* (UBINOS__BSP__CPU_TYPE__CORTEX_MX == 1) */
#endif /* (INCLUDE__UBINOS__UBIK == 1) */


