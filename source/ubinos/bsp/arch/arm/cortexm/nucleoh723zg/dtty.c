/*
 * Copyright (c) 2019 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOH723ZG)

#if (UBINOS__BSP__USE_DTTY == 1)
#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__UART)

#include "../stm32h7/stm32h7xx_ll_bus.h"
#include "../stm32h7/stm32h7xx_ll_gpio.h"
#include "../stm32h7/stm32h7xx_ll_usart.h"
#include "../stm32h7/stm32h7xx_ll_rcc.h"

#if (UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER == 3)

#define USARTx_INSTANCE               USART3
#define USARTx_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART234578_CLKSOURCE_PCLK1)
#define USARTx_IRQn                   USART3_IRQn
#define USARTx_IRQHandler             USART3_IRQHandler

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD)   /* Enable the peripheral clock of GPIOD */
#define USARTx_TX_PIN                 LL_GPIO_PIN_8
#define USARTx_TX_GPIO_PORT           GPIOD
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_8, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_9
#define USARTx_RX_GPIO_PORT           GPIOD
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define APB_Div 2
#define AHB_Div 2

#else

#error "Unsupported UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER"

#endif

#define SLEEP_TIMEMS    1

extern int _g_bsp_dtty_init;
extern int _g_bsp_dtty_in_init;
extern int _g_bsp_dtty_echo;
extern int _g_bsp_dtty_autocr;

static void Configure_USART(void) {

    /* (1) Enable GPIO clock and configures the USART pins *********************/

    /* Enable the peripheral clock of GPIO Port */

    /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
    USARTx_GPIO_CLK_ENABLE();
    LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_TX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);

    /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
    USARTx_GPIO_CLK_ENABLE();
    LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_RX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);

    /* (2) Enable USART peripheral clock and clock source ***********************/
    USARTx_CLK_ENABLE();

    /* Set clock source */
    USARTx_CLK_SOURCE();

    /* (3) Configure USART functional parameters ********************************/

    /* Disable USART prior modifying configuration registers */
    /* Note: Commented as corresponding to Reset value */
    LL_USART_Disable(USARTx_INSTANCE);

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

    /* Set Baudrate to 115200 using APB frequency set to 125000000 Hz */
    /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
    /* Ex :
        Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance

        In this example, Peripheral Clock is expected to be equal to 125000000 Hz => equal to SystemCoreClock/(AHB_Div * APB_Div)
    */
    LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock/(AHB_Div * APB_Div), LL_USART_PRESCALER_DIV1, LL_USART_OVERSAMPLING_16, 115200);

    /* (4) Enable USART *********************************************************/
    LL_USART_Enable(USARTx_INSTANCE);

    /* Polling USART initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(USARTx_INSTANCE))) || (!(LL_USART_IsActiveFlag_REACK(USARTx_INSTANCE))))
    {
    }
}

int dtty_init(void) {
    if (!_g_bsp_dtty_init && !_g_bsp_dtty_in_init)
    {
        _g_bsp_dtty_in_init = 1;

        Configure_USART();

        _g_bsp_dtty_echo = 1;
        _g_bsp_dtty_autocr = 1;

        _g_bsp_dtty_init = 1;

        _g_bsp_dtty_in_init = 0;
    }

    return 0;
}

int dtty_enable(void) {
    return 0;
}

int dtty_disable(void) {
    return 0;
}

int dtty_geterror(void) {
    return 0;
}

int dtty_getc(char *ch_p) {
    if (!_g_bsp_dtty_init) {
        dtty_init();
    }

    unsigned int i;

    if (NULL == ch_p) {
        return -2;
    }

#if (INCLUDE__UBINOS__UBIK == 1)
    if (_bsp_kernel_active) {
        for (i = 0;; i++) {
            if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
                break;
            }
            if (255 <= i) {
                bsp_task_sleepms(SLEEP_TIMEMS);
                i = 0;
            }
        }
    }
    else {
        for (i=0; ; i++)
        {
            if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
                break;
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
}

int dtty_putc(int ch) {
    if (!_g_bsp_dtty_init) {
        dtty_init();
    }

    if (0 != _g_bsp_dtty_autocr && '\n' == ch) {
        for (;;) {
            if (LL_USART_IsActiveFlag_TXE(USARTx_INSTANCE)) {
                break;
            }
        }
        LL_USART_TransmitData8(USARTx_INSTANCE, '\r');
    }

    for (;;) {
        if (LL_USART_IsActiveFlag_TXE(USARTx_INSTANCE)) {
            break;
        }
    }
    LL_USART_TransmitData8(USARTx_INSTANCE, ch);

    return 0;
}

int dtty_flush(void)
{
    return 0;
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

int dtty_kbhit(void) {
    if (!_g_bsp_dtty_init) {
        dtty_init();
    }

    if (LL_USART_IsActiveFlag_RXNE(USARTx_INSTANCE)) {
        return 1;
    } else {
        return 0;
    }
}

void dtty_write_process(void *arg)
{
}

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__UART) */
#endif /* (UBINOS__BSP__USE_DTTY == 1) */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOH723ZG) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

