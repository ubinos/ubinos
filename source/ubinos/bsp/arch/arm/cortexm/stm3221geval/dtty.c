/*
 Copyright (C) 2011 RTLab
 Contact: ubinos.org@gmail.com

 Contributors: Dong Hoon Kim, Sung Ho Park

 This file is part of the bsp_sam3s4ek component of the Ubinos.

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

#if (UBINOS__BSP__USE_DTTY == 1)

#include "../stm32f2/stm32f2xx_ll_bus.h"
#include "../stm32f2/stm32f2xx_ll_gpio.h"
#include "../stm32f2/stm32f2xx_ll_usart.h"

/* USART3 instance is used. (TX on PD.08, RX on PD.09)
   (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled
    on HW board in order to support Virtual Com Port) */
#define USARTx_INSTANCE               USART3
#define USARTx_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)   /* Enable the peripheral clock of GPIOD */
#define USARTx_TX_PIN                 LL_GPIO_PIN_10
#define USARTx_TX_GPIO_PORT           GPIOC
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_10, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_11
#define USARTx_RX_GPIO_PORT           GPIOC
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_11, LL_GPIO_AF_7)
#define APB_Div 4

#define SLEEP_TIMEMS	1

int _g_bsp_dtty_echo = 0;

static void Configure_USART(void)
{

  /* (1) Enable GPIO clock and configures the USART pins *********************/

  /* Enable the peripheral clock of GPIO Port */
  USARTx_GPIO_CLK_ENABLE();

  /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTx_SET_TX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);

  /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTx_SET_RX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);

  /* (2) Enable USART peripheral clock and clock source ***********************/
  USARTx_CLK_ENABLE();

  /* (3) Configure USART functional parameters ********************************/

  /* Disable USART prior modifying configuration registers */
  /* Note: Commented as corresponding to Reset value */
  // LL_USART_Disable(USARTx_INSTANCE);

  /* TX/RX direction */
  LL_USART_SetTransferDirection(USARTx_INSTANCE, LL_USART_DIRECTION_TX_RX);

  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
  LL_USART_ConfigCharacter(USARTx_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

  /* No Hardware Flow control */
  /* Reset value is LL_USART_HWCONTROL_NONE */
   LL_USART_SetHWFlowCtrl(USARTx_INSTANCE, LL_USART_HWCONTROL_NONE);

  /* Oversampling by 16 */
  /* Reset value is LL_USART_OVERSAMPLING_16 */
   LL_USART_SetOverSampling(USARTx_INSTANCE, LL_USART_OVERSAMPLING_16);

  /* Set Baudrate to 115200 using APB frequency set to 120000000/APB_Div Hz */
  /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
  /* Ex :
      Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance

      In this example, Peripheral Clock is expected to be equal to 120000000/APB_Div Hz => equal to SystemCoreClock/APB_Div
  */
  LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock/APB_Div, LL_USART_OVERSAMPLING_16, 115200);

  /* (4) Enable USART *********************************************************/
  LL_USART_Enable(USARTx_INSTANCE);
}

int dtty_init(void) {
    _g_bsp_dtty_echo = 0;

    Configure_USART();

    return 0;
}

int dtty_geterror(void) {
	return 0;
}

int dtty_enable(void) {
    return 0;
}

int dtty_disable(void) {
    return 0;
}

int dtty_getc(char * ch_p) {
	unsigned int i;

	if (NULL == ch_p) {
		return -2;
	}

#if (INCLUDE__UBINOS__UBIK == 1)
	if(_bsp_kernel_active) {
		for (i=0; ; i++)
		{
			if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
				break;
			}
			if (255 <= i) {
				bsp_task_sleepms(SLEEP_TIMEMS);
				i = 0;
			}
		}
	}
#else
	for (i=0; ; i++)
	{
		if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
			break;
		}
	}
#endif /* (INCLUDE__UBINOS__UBIK == 1) */

	*ch_p = (char) LL_USART_ReceiveData8(USARTx_INSTANCE);

	if (0 != _g_bsp_dtty_echo) {
		dtty_putc(*ch_p);
	}

	return 0;


	return 0;
}

int dtty_putc(int ch) {
    for (;;)
    {
        if (LL_USART_IsActiveFlag_TXE(USARTx_INSTANCE)) {
            break;
        }
    }

    LL_USART_TransmitData8(USARTx_INSTANCE, ch);

    return 0;
}

int dtty_puts(const char * str, int max) {
    int i = 0;

    if (NULL == str) {
        return -2;
    }

    if (0 > max) {
        return -3;
    }

    for (i = 0; i < max; i++) {
        if ('\0' == *str) {
            break;
        }
        dtty_putc(*str);
        str++;
    }

    return i;
}

int dtty_putn(const char * str, int len) {
    int i = 0;

    if (NULL == str) {
        return -2;
    }

    if (0 > len) {
        return -3;
    }

    for (i = 0; i < len; i++) {
        dtty_putc(*str);
        str++;
    }

    return i;
}

int dtty_gets(char * str, int max) {
	int i;
	int r;

	if (NULL == str) {
		return -2;
	}

	if (0 > max) {
		return -3;
	}

	for (i=0; i<max; i++) {
		r = dtty_getc(&str[i]);
		if (0 != r || '\0' == str[i] || '\n' == str[i] || '\r' == str[i]) {
			break;
		}
	}
	if (0 != i && max == i) {
		i--;
	}
	str[i] = '\0';

	return i;
}

int dtty_kbhit(void) {
	if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
		return 1;
	} else {
		return 0;
	}
}

int dtty_setecho(int echo) {
    _g_bsp_dtty_echo = echo;

    return 0;
}

#else

int dtty_init(void) {
    return 0;
}

int dtty_enable(void) {
    return 0;
}

int dtty_disable(void) {
    return 0;
}


int dtty_getc(char * ch_p) {
    return 0;
}

int dtty_putc(int ch)  {
    return 0;
}

int dtty_puts(const char * str, int max) {
    return 0;
}

int dtty_putn(const char * str, int len) {
    return 0;
}

int dtty_gets(char * str, int max) {
    return 0;
}

int dtty_kbhit(void) {
    return 0;
}

int dtty_setecho(int echo) {
    return 0;
}

#endif /* (UBINOS__BSP__USE_DTTY == ...) */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM3221GEVAL) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

