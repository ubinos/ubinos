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
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DK)

#if (UBINOS__BSP__USE_DTTY == 1)

#define SLEEP_TIMEMS	1

int _g_bsp_dtty_echo = 0;

#define GPIO_CFG(pin_number, pin_dir, pin_input, pin_pull, pin_drive, pin_sense) {     \
    NRF_GPIO->PIN_CNF[pin_number] =   ((uint32_t)pin_dir   << GPIO_PIN_CNF_DIR_Pos  )  \
                                    | ((uint32_t)pin_input << GPIO_PIN_CNF_INPUT_Pos)  \
                                    | ((uint32_t)pin_pull  << GPIO_PIN_CNF_PULL_Pos )  \
                                    | ((uint32_t)pin_drive << GPIO_PIN_CNF_DRIVE_Pos)  \
                                    | ((uint32_t)pin_sense << GPIO_PIN_CNF_SENSE_Pos); \
}

#define GPIO_PIN_OUTSET(pin_number) {             \
    NRF_GPIO->OUTSET = 1UL << pin_number;         \
}
#define GPIO_PIN_OUTCLR(pin_number) {             \
    NRF_GPIO->OUTCLR = 1UL << pin_number;         \
}

#define GPIO_CFG_OUTPUT(pin_number) {             \
    GPIO_CFG(pin_number,                          \
        GPIO_PIN_CNF_DIR_Output,                  \
        GPIO_PIN_CNF_INPUT_Disconnect,            \
        GPIO_PIN_CNF_PULL_Disabled,               \
        GPIO_PIN_CNF_DRIVE_S0S1,                  \
        GPIO_PIN_CNF_SENSE_Disabled);             \
}

#define GPIO_CFG_INPUT(pin_number, pull_config) { \
    GPIO_CFG(pin_number,                          \
        GPIO_PIN_CNF_DIR_Input,                   \
        GPIO_PIN_CNF_INPUT_Connect,               \
		pull_config,                              \
        GPIO_PIN_CNF_DRIVE_S0S1,                  \
        GPIO_PIN_CNF_SENSE_Disabled);             \
}

#define GPIO_CFG_DEFAULT(pin_number) {            \
    GPIO_CFG(pin_number,                          \
        GPIO_PIN_CNF_DIR_Input,                   \
        GPIO_PIN_CNF_INPUT_Disconnect,            \
        GPIO_PIN_CNF_PULL_Disabled,               \
        GPIO_PIN_CNF_DRIVE_S0S1,                  \
        GPIO_PIN_CNF_SENSE_Disabled);             \
}

int dtty_init(void) {
    _g_bsp_dtty_echo = 0;

    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);

    /* Disable receiver & transmitter interrupts */
    NRF_UART0->INTENCLR = 0xffffffff;

    /* Stop receiver & transmitter */
    NRF_UART0->TASKS_STOPTX = 1;
    NRF_UART0->TASKS_STOPRX = 1;

    /* Configure GPIO */
    GPIO_PIN_OUTSET(6); // TXD
    GPIO_CFG_OUTPUT(6);
    GPIO_CFG_INPUT(8, GPIO_PIN_CNF_PULL_Disabled); // RXD

    /* Configure serial link */
    NRF_UART0->BAUDRATE = (UART_BAUDRATE_BAUDRATE_Baud115200 << UART_BAUDRATE_BAUDRATE_Pos);
    NRF_UART0->CONFIG = (UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos) | (UART_CONFIG_HWFC_Disabled << UART_CONFIG_HWFC_Pos);
    NRF_UART0->PSELTXD = 6;
    NRF_UART0->PSELRXD = 8;
    NRF_UART0->EVENTS_ERROR = 0;
    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);

    /* Start receiver & transmitter */
    NRF_UART0->TASKS_STARTTX = 1;
    NRF_UART0->TASKS_STARTRX = 1;

    return 0;
}

int dtty_geterror(void) {
	return NRF_UART0->EVENTS_ERROR;
}

int dtty_enable(void) {
    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
    return 0;
}

int dtty_disable(void) {
    NRF_UART0->ENABLE = (UART_ENABLE_ENABLE_Disabled << UART_ENABLE_ENABLE_Pos);
    return 0;
}

int dtty_getc(char * ch_p) {
    unsigned int i;

    if (NULL == ch_p) {
        return -2;
    }

#if (INCLUDE__UBINOS__UBIK == 1)
    if (_bsp_kernel_active) {
        for (i = 0;; i++) {
            if (NRF_UART0->EVENTS_RXDRDY) {
                break;
            }
            if (255 <= i) {
                bsp_task_sleepms(SLEEP_TIMEMS);
                i = 0;
            }
        }
    }
    else {
        for (i=0;; i++)
        {
            if(NRF_UART0->EVENTS_RXDRDY) {
                break;
            }
        }
    }
#else
    for (i=0;; i++)
    {
        if(NRF_UART0->EVENTS_RXDRDY) {
            break;
        }
    }
#endif /* (INCLUDE__UBINOS__UBIK == 1) */

    *ch_p = (char) (0x000000ff & (NRF_UART0->RXD));

    NRF_UART0->EVENTS_RXDRDY = 0x0UL;

    if (0 != _g_bsp_dtty_echo) {
        dtty_putc(*ch_p);
    }

    return 0;
}

int dtty_putc(int ch) {
    NRF_UART0->EVENTS_TXDRDY = 0x0UL;

    NRF_UART0->TXD = (0x000000ff & ch);

    for (;;) {
        if (NRF_UART0->EVENTS_TXDRDY) {
            break;
        }
    }

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

    for (i = 0; i < max; i++) {
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
    if (NRF_UART0->EVENTS_RXDRDY) {
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

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DK) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

