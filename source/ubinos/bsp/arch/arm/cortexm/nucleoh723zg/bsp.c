/*
 * Copyright (c) 2022 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOH723ZG)

#include "../stm32h7/stm32h7xx_ll_system.h"
#include "../stm32h7/stm32h7xx_ll_bus.h"
#include "../stm32h7/stm32h7xx_ll_rcc.h"
#include "../stm32h7/stm32h7xx_ll_pwr.h"

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL1 (HSE BYPASS)
  *            SYSCLK(Hz)                     = 520000000 (CPU Clock)
  *            HCLK(Hz)                       = 260000000 (AXI and AHBs Clock)
  *            AHB Prescaler                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  130MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  130MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  130MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  130MHz)
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 4
  *            PLL_N                          = 260
  *            PLL_P                          = 1
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Power Configuration */
  LL_PWR_ConfigSupply(LL_PWR_LDO_SUPPLY);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);
  while (LL_PWR_IsActiveFlag_VOS() == 0)
  {
  }

  /* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSE);
  LL_RCC_PLL1P_Enable();
  LL_RCC_PLL1Q_Enable();
  LL_RCC_PLL1R_Enable();
  LL_RCC_PLL1FRACN_Disable();
  LL_RCC_PLL1_SetVCOInputRange(LL_RCC_PLLINPUTRANGE_2_4);
  LL_RCC_PLL1_SetVCOOutputRange(LL_RCC_PLLVCORANGE_WIDE);
  LL_RCC_PLL1_SetM(4);
  LL_RCC_PLL1_SetN(260);
  LL_RCC_PLL1_SetP(1);
  LL_RCC_PLL1_SetQ(4);
  LL_RCC_PLL1_SetR(2);
  LL_RCC_PLL1_Enable();
  while(LL_RCC_PLL1_IsReady() != 1)
  {
  }

  /* Set Sys & AHB & APB1 & APB2 & APB4  prescaler */
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_2);

  /* Set PLL1 as System Clock Source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
  {
  }

  // /* Set systick to 1ms */
  // SysTick_Config(520000000 / 1000);

  // /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  // SystemCoreClock = 520000000;

  SystemCoreClock = (UBINOS__BSP__CLOCK_FREQ_MAIN * 1000);
}

__WEAK void MPU_Config(void) {
}

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOH723ZG) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

