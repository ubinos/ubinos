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
__WEAK void SystemClock_Config(void)
{
  /* Enable HSE oscillator */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 240, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  /* Set systick to 1ms */
  //SysTick_Config(UBINOS__BSP__CLOCK_FREQ_MAIN);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = (UBINOS__BSP__CLOCK_FREQ_MAIN * 1000);

}

#ifdef DATA_IN_ExtSRAM
/**
  * @brief  Setup the external memory controller.
  *         Called in startup_stm32f2xx.s before jump to main.
  *         This function configures the external SRAM mounted on STM322xG_EVAL board
  *         This SRAM will be used as program data memory (including heap and stack).
  * @param  None
  * @retval None
  */
__WEAK void SystemInit_ExtMemCtl(void)
{
  __IO uint32_t tmp = 0x00;

/*-- GPIOs Configuration -----------------------------------------------------*/
   /* Enable GPIOD, GPIOE, GPIOF and GPIOG interface clock */
  RCC->AHB1ENR   |= 0x00000078;
  /* Delay after an RCC peripheral clock enabling */
  tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
  (void)(tmp);

  /* Connect PDx pins to FSMC Alternate function */
  GPIOD->AFR[0]  = 0x00CCC0CC;
  GPIOD->AFR[1]  = 0xCCCCCCCC;
  /* Configure PDx pins in Alternate function mode */
  GPIOD->MODER   = 0xAAAA0A8A;
  /* Configure PDx pins speed to 100 MHz */
  GPIOD->OSPEEDR = 0xFFFF0FCF;
  /* Configure PDx pins Output type to push-pull */
  GPIOD->OTYPER  = 0x00000000;
  /* No pull-up, pull-down for PDx pins */
  GPIOD->PUPDR   = 0x00000000;

  /* Connect PEx pins to FSMC Alternate function */
  GPIOE->AFR[0]  = 0xC00CC0CC;
  GPIOE->AFR[1]  = 0xCCCCCCCC;
  /* Configure PEx pins in Alternate function mode */
  GPIOE->MODER   = 0xAAAA828A;
  /* Configure PEx pins speed to 100 MHz */
  GPIOE->OSPEEDR = 0xFFFFC3CF;
  /* Configure PEx pins Output type to push-pull */
  GPIOE->OTYPER  = 0x00000000;
  /* No pull-up, pull-down for PEx pins */
  GPIOE->PUPDR   = 0x00000000;

  /* Connect PFx pins to FSMC Alternate function */
  GPIOF->AFR[0]  = 0x00CCCCCC;
  GPIOF->AFR[1]  = 0xCCCC0000;
  /* Configure PFx pins in Alternate function mode */
  GPIOF->MODER   = 0xAA000AAA;
  /* Configure PFx pins speed to 100 MHz */
  GPIOF->OSPEEDR = 0xFF000FFF;
  /* Configure PFx pins Output type to push-pull */
  GPIOF->OTYPER  = 0x00000000;
  /* No pull-up, pull-down for PFx pins */
  GPIOF->PUPDR   = 0x00000000;

  /* Connect PGx pins to FSMC Alternate function */
  GPIOG->AFR[0]  = 0x00CCCCCC;
  GPIOG->AFR[1]  = 0x000000C0;
  /* Configure PGx pins in Alternate function mode */
  GPIOG->MODER   = 0x00085AAA;
  /* Configure PGx pins speed to 100 MHz */
  GPIOG->OSPEEDR = 0x000CAFFF;
  /* Configure PGx pins Output type to push-pull */
  GPIOG->OTYPER  = 0x00000000;
  /* No pull-up, pull-down for PGx pins */
  GPIOG->PUPDR   = 0x00000000;

/*--FSMC Configuration -------------------------------------------------------*/
  /* Enable the FSMC interface clock */
  RCC->AHB3ENR         |= 0x00000001;

  /* Configure and enable Bank1_SRAM2 */
  FSMC_Bank1->BTCR[2]  = 0x00001011;
  FSMC_Bank1->BTCR[3]  = 0x00000201;
  FSMC_Bank1E->BWTR[2] = 0x0FFFFFFF;
}
#endif /* DATA_IN_ExtSRAM */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM3221GEVAL) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

