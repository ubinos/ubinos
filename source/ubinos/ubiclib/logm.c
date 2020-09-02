/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_ubiclib.h"

#if (INCLUDE__UBINOS__UBICLIB == 1)

#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)

#include <ubinos/bsp.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE "\n"

volatile int _ubiclib_logm_level[LOGM_CATEGORY__END] = {
		LOGM_LEVEL, // 00 NONE

		LOGM_LEVEL, // 01 UBINOS
		LOGM_LEVEL, // 02 BSP
		LOGM_LEVEL, // 03 UBIK
		LOGM_LEVEL, // 04 TASK
		LOGM_LEVEL, // 05 SEM
		LOGM_LEVEL, // 06 MSGQ
		LOGM_LEVEL, // 07 CONDV
		LOGM_LEVEL, // 08 SIGNAL
		LOGM_LEVEL, // 09 STIMER

		LOGM_LEVEL, // 10 UBICLIB
		LOGM_LEVEL, // 11 HEAP

		LOGM_LEVEL, // 12 SYS00
		LOGM_LEVEL, // 13 SYS01
		LOGM_LEVEL, // 14 SYS02
		LOGM_LEVEL, // 15 SYS03
		LOGM_LEVEL, // 16 SYS04
		LOGM_LEVEL, // 17 SYS05
		LOGM_LEVEL, // 18 SYS06
		LOGM_LEVEL, // 19 SYS07
		LOGM_LEVEL, // 20 SYS08
		LOGM_LEVEL, // 21 SYS09

		LOGM_LEVEL, // 22 USER00
		LOGM_LEVEL, // 23 USER01
		LOGM_LEVEL, // 24 USER02
		LOGM_LEVEL, // 25 USER03
		LOGM_LEVEL, // 26 USER04
		LOGM_LEVEL, // 27 USER05
		LOGM_LEVEL, // 28 USER06
		LOGM_LEVEL, // 29 USER07
		LOGM_LEVEL, // 30 USER08
		LOGM_LEVEL, // 31 USER09
};

const char *_ubiclib_logm_categoryname[LOGM_CATEGORY__END] = {
		"[NONE   ] ", // 00 NONE

		"[UBINOS ] ", // 01 UBINOS
		"[BSP    ] ", // 02 BSP
		"[UBIK   ] ", // 03 UBIK
		"[TASK   ] ", // 04 TASK
		"[SEM    ] ", // 05 SEM
		"[MSGQ   ] ", // 06 MSGQ
		"[CONDV  ] ", // 07 CONDV
		"[SIGNAL ] ", // 08 SIGNAL
		"[STIMER ] ", // 09 STIMER

		"[UBICLIB] ", // 10 UBICLIB
		"[HEAP   ] ", // 11 HEAP

		"[SYS00  ] ", // 12 SYS00
		"[SYS01  ] ", // 13 SYS01
		"[SYS02  ] ", // 14 SYS02
		"[SYS03  ] ", // 15 SYS03
		"[SYS04  ] ", // 16 SYS04
		"[SYS05  ] ", // 17 SYS05
		"[SYS06  ] ", // 18 SYS06
		"[SYS07  ] ", // 19 SYS07
		"[SYS08  ] ", // 20 SYS08
		"[SYS09  ] ", // 21 SYS09

		"[USER00 ] ", // 22 USER00
		"[USER01 ] ", // 23 USER01
		"[USER02 ] ", // 24 USER02
		"[USER03 ] ", // 25 USER03
		"[USER04 ] ", // 26 USER04
		"[USER05 ] ", // 27 USER05
		"[USER06 ] ", // 28 USER06
		"[USER07 ] ", // 29 USER07
		"[USER08 ] ", // 30 USER08
		"[USER09 ] ", // 31 USER09
};

const char *_ubiclib_logm_levelname[LOGM_LEVEL__END] = {
		"[SILENT ] ",
		"[FATAL  ] ",
		"[ERROR  ] ",
		"[WARNING] ",
		"[INFO   ] ",
		"[DEBUG  ] ",
		"[VERBOSE] ",
};

int logm_setlevel(int category, int level) {
	int i;

	if (-1 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (0 > level || LOGM_LEVEL__END <= level) {
		return -3;
	}

	if (-1 == category) {
		for (i = 0; i < LOGM_CATEGORY__END; i++) {
			_ubiclib_logm_level[i] = level;
		}
	} else {
		_ubiclib_logm_level[category] = level;
	}

	return 0;
}

int logm_getlevel(int category) {
	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	return _ubiclib_logm_level[category];
}

int logm_printfln(int category, int level, const char *tag, const char *func, int line, const char *format, ...) {
	int n = 0;
	char buf[256];
	int len;
	int i;

	va_list ap;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

#if (INCLUDE__UBINOS__UBIK == 1)
	tickcount_t tc;
	if (_bsp_kernel_active) {
		tc = ubik_gettickcount();
		itoa(tc.low, buf, 10);
		len = strlen(buf);
		n += dtty_puts("[", 128);
		if (len < LOGM_TICK_COUNT_LENGTH) {
			for (i = 0; i < (LOGM_TICK_COUNT_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(buf, 128);
		n += dtty_puts("] ", 128);
	}
#endif /* (INCLUDE__UBINOS__UBIK == 1) */

	n += dtty_puts(_ubiclib_logm_levelname[level], 128);

	n += dtty_puts(_ubiclib_logm_categoryname[category], 128);

	if (NULL != tag) {
		n += dtty_puts("[", 128);
		n += dtty_puts(tag, 128);
		len = strlen(tag);
		if (len < LOGM_TAG_LENGTH) {
			for (i = 0; i < (LOGM_TAG_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts("] ", 128);
	}

	if (NULL != func) {
		n += dtty_puts("", 128);
		n += dtty_puts(func, 128);
		len = strlen(func);
		if (len < LOGM_FUNCTION_NAME_LENGTH) {
			for (i = 0; i < (LOGM_FUNCTION_NAME_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(" : ", 128);
		itoa(line, buf, 10);
		len = strlen(buf);
		if (len < LOGM_LINE_NUMBER_LENGTH) {
			for (i = 0; i < (LOGM_LINE_NUMBER_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(buf, 128);
		n += dtty_puts(" : ", 128);
	}

	va_start(ap, format);
	n += vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);
	n += dtty_puts(buf, sizeof(buf));

	n += dtty_puts(NEWLINE, 128);

	return n;
}

int logm_println(int category, int level, const char *tag, const char *func, int line, const char *msg) {
	int n = 0;
	char buf[128];
	int len;
	int i;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

#if (INCLUDE__UBINOS__UBIK == 1)
	tickcount_t tc;
	if (_bsp_kernel_active) {
		tc = ubik_gettickcount();
		itoa(tc.low, buf, 10);
		len = strlen(buf);
		n += dtty_puts("[", 128);
		if (len < LOGM_TICK_COUNT_LENGTH) {
			for (i = 0; i < (LOGM_TICK_COUNT_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(buf, 128);
		n += dtty_puts("] ", 128);
	}
#endif /* (INCLUDE__UBINOS__UBIK == 1) */

	n += dtty_puts(_ubiclib_logm_levelname[level], 128);

	n += dtty_puts(_ubiclib_logm_categoryname[category], 128);

	if (NULL != tag) {
		n += dtty_puts("[", 128);
		n += dtty_puts(tag, 128);
		len = strlen(tag);
		if (len < LOGM_TAG_LENGTH) {
			for (i = 0; i < (LOGM_TAG_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts("] ", 128);
	}

	if (NULL != func) {
		n += dtty_puts("", 128);
		n += dtty_puts(func, 128);
		len = strlen(func);
		if (len < LOGM_FUNCTION_NAME_LENGTH) {
			for (i = 0; i < (LOGM_FUNCTION_NAME_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(" : ", 128);
		itoa(line, buf, 10);
		len = strlen(buf);
		if (len < LOGM_LINE_NUMBER_LENGTH) {
			for (i = 0; i < (LOGM_LINE_NUMBER_LENGTH - len); i++) {
				n += dtty_puts(" ", 128);
			}
		}
		n += dtty_puts(buf, 128);
		n += dtty_puts(" : ", 128);
	}

	n += dtty_puts(msg, 128);

	n += dtty_puts(NEWLINE, 128);

	return n;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

