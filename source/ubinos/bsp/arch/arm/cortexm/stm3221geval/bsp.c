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

#include "../_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM3221GEVAL)

#include "../stm32f2/stm32f2xx_ll_system.h"
#include "../stm32f2/stm32f2xx_ll_rcc.h"

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 120000000
 *            HCLK(Hz)                       = 120000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 240
 *            PLL_P                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 3
 * @param  None
 * @retval None
 */
__WEAK void SystemClock_Config(void) {
	/* Enable HSE oscillator */
#if (UBINOS__BSP__STM32_RCC_HSE_CONFIG == UBINOS__BSP__STM32_RCC_HSE_CONFIG__ON)
	LL_RCC_HSE_Enable();
	while (LL_RCC_HSE_IsReady() != 1) {
	};
#elif (UBINOS__BSP__STM32_RCC_HSE_CONFIG == UBINOS__BSP__STM32_RCC_HSE_CONFIG__BYPASS)
	LL_RCC_HSE_EnableBypass();
	LL_RCC_HSE_Enable();
	while (LL_RCC_HSE_IsReady() != 1) {
	};
#elif (UBINOS__BSP__STM32_RCC_HSE_CONFIG == UBINOS__BSP__STM32_RCC_HSE_CONFIG__OFF)
    dtty_puts("Unsupported UBINOS__BSP__STM32_RCC_HSE_CONFIG option\r\n", 80);
    bsp_abortsystem();
#else
	#error "Unsupported UBINOS__BSP__STM32_RCC_HSE_CONFIG option"
#endif

	/* Set FLASH latency */
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

	/* Main PLL configuration and activation */
#if (UBINOS__BSP__STM32_HSE_VALUE == 25000000U)
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 240, LL_RCC_PLLP_DIV_2);
#elif (UBINOS__BSP__STM32_HSE_VALUE == 8000000U)
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 240, LL_RCC_PLLP_DIV_2);
#else
	#error "Unsupported UBINOS__BSP__STM32_HSE_VALUE"
#endif /* (UBINOS__BSP__STM32_HSE_VALUE == 25000000U) */
	LL_RCC_PLL_Enable();
	while (LL_RCC_PLL_IsReady() != 1) {
	};

	/* Sysclk activation on the main PLL */
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
	};

	/* Set APB1 & APB2 prescaler */
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

	/* Set systick to 1ms */
	//SysTick_Config(UBINOS__BSP__CLOCK_FREQ_MAIN);
	/* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
	SystemCoreClock = (UBINOS__BSP__CLOCK_FREQ_MAIN * 1000);
}

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM3221GEVAL) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

