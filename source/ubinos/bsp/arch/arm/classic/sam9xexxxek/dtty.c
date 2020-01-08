/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the bsp_sam9xe512ek component of the Ubinos.

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
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__SAM9XE512EK)

#if (UBINOS__BSP__USE_DTTY == 1)

#define SLEEP_TIMEMS	1

int _g_bsp_dtty_echo	= 0;

int dtty_init(void) {
	_g_bsp_dtty_echo	= 0;

	/* Reset and disable receiver */
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTRX | AT91C_US_RSTTX;

	/* Disable interrupts */
	AT91C_BASE_DBGU->DBGU_IDR = 0xFFFFFFFF;

	/* Configure PIOs for DBGU */
	AT91C_BASE_PIOB->PIO_ASR = AT91C_PB14_DRXD | AT91C_PB15_DTXD;
	AT91C_BASE_PIOB->PIO_BSR = 0;
	AT91C_BASE_PIOB->PIO_PDR = AT91C_PB14_DRXD | AT91C_PB15_DTXD;

	/* === Configure serial link === */
	/* Define the baud rate divisor register [BRGR = MCK / (115200 * 16)] */
	AT91C_BASE_DBGU->DBGU_BRGR = 54;
	/* Define the USART mode */
	AT91C_BASE_DBGU->DBGU_MR = AT91C_US_CHMODE_NORMAL | AT91C_US_PAR_NONE;

	/* Disable the RX and TX PDC transfer requests */
	AT91C_BASE_DBGU->DBGU_PTCR = AT91C_PDC_RXTDIS;
	AT91C_BASE_DBGU->DBGU_PTCR = AT91C_PDC_TXTDIS;

	/* Enable transmitter */
	AT91C_BASE_DBGU->DBGU_CR = AT91C_US_TXEN | AT91C_US_RXEN;

	return 0;
}

int dtty_enable(void) {
	return -10;
}

int dtty_disable(void) {
	return -10;
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
			if (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY) {
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
			if (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY) {
				break;
			}
		}
	}
#else
	for (i=0; ; i++)
	{
		if (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY) {
			break;
		}
	}
#endif /* (INCLUDE__UBINOS__UBIK == 1) */

	*ch_p = (char) ((AT91C_BASE_DBGU->DBGU_RHR) & 0xFF);

	if (0 != _g_bsp_dtty_echo) {
		dtty_putc(*ch_p);
	}

	return 0;
}

#pragma GCC push_options
#pragma GCC target ("arm")
int dtty_putc(int ch) {
    for (;;)
    {
        if (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY) {
            break;
        }
    }

    AT91C_BASE_DBGU->DBGU_THR = (ch & 0xFF);

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

	for (i=0; i<max; i++) {
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
#pragma GCC pop_options

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
	if (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY) {
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

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__SAM9XE512EK) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

