/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam... component of the Ubinos.

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

#include <ubinos/bsp.h>
#include <ubinos/bsp_ubik.h>

#if (INCLUDE__UBINOS__BSP == 1)

#if (UBINOS__BSP__USE_DTTY == 1)

int _g_bsp_dtty_init = 0;
int _g_bsp_dtty_echo = 0;

#if (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__ARM926EJ_S)
#pragma GCC push_options
#pragma GCC target ("arm")
#endif
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
#if (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__ARM926EJ_S)
#pragma GCC pop_options
#endif

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

int dtty_setecho(int echo) {
    _g_bsp_dtty_echo = echo;

    return 0;
}

#else /* (UBINOS__BSP__USE_DTTY == ...) */

int dtty_puts(const char * str, int max) {
    return 0;
}

int dtty_putn(const char * str, int len) {
    return 0;
}

int dtty_gets(char * str, int max) {
    return 0;
}

int dtty_setecho(int echo) {
    return 0;
}


int dtty_init(void) {
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

int dtty_getc(char * ch_p) {
    return 0;
}

int dtty_putc(int ch)  {
    return 0;
}

int dtty_kbhit(void) {
    return 0;
}

#endif /* (UBINOS__BSP__USE_DTTY == ...) */

#endif /* (INCLUDE__UBINOS__BSP == 1) */

