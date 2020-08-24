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

#define NEWLINE "\r\n"

volatile int _ubiclib_logm_level[LOGM_CATEGORY__END] = {
		LOGM_LEVEL, // NONE
		LOGM_LEVEL, // UBINOS
		LOGM_LEVEL, // BSP
		LOGM_LEVEL, // UBIK
		LOGM_LEVEL, // TASK
		LOGM_LEVEL, // SEM
		LOGM_LEVEL, // MSGQ
		LOGM_LEVEL, // CONDV
		LOGM_LEVEL, // SIGNAL
		LOGM_LEVEL, // STIMER
		LOGM_LEVEL, // UBICLIB
		LOGM_LEVEL, // HEAP
		LOGM_LEVEL, // USER00
		LOGM_LEVEL, // USER01
		LOGM_LEVEL, // USER02
};

const char *_ubiclib_logm_categoryname[LOGM_CATEGORY__END] = {
		"[NONE   ] ",
		"[UBINOS ] ",
		"[BSP    ] ",
		"[UBIK   ] ",
		"[TASK   ] ",
		"[SEM    ] ",
		"[MSGQ   ] ",
		"[CONDV  ] ",
		"[SIGNAL ] ",
		"[STIMER ] ",
		"[UBICLIB] ",
		"[HEAP   ] ",
		"[USER00 ] ",
		"[USER01 ] ",
		"[USER02 ] ",
};

const char *_ubiclib_logm_levelname[LOGM_LEVEL__END] = {
		"[NONE   ] ",
		"[ALWAYS ] ",
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
	va_list ap;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

	n += dtty_puts(_ubiclib_logm_levelname[level], 128);

	n += dtty_puts(_ubiclib_logm_categoryname[category], 128);

	if (NULL != tag) {
		n += dtty_puts("[", 128);
		n += dtty_puts(tag, 128);
		n += dtty_puts("] ", 128);
	}

	if (NULL != func) {
		n += dtty_puts("", 128);
		n += dtty_puts(func, 128);
		n += dtty_puts(" : ", 128);
		itoa(line, buf, 10);
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

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

	n += dtty_puts(_ubiclib_logm_levelname[level], 128);

	n += dtty_puts(_ubiclib_logm_categoryname[category], 128);

	if (NULL != tag) {
		n += dtty_puts("[", 128);
		n += dtty_puts(tag, 128);
		n += dtty_puts("] ", 128);
	}

	if (NULL != func) {
		n += dtty_puts("", 128);
		n += dtty_puts(func, 128);
		n += dtty_puts(" : ", 128);
		itoa(line, buf, 10);
		n += dtty_puts(buf, 128);
		n += dtty_puts(" : ", 128);
	}

	n += dtty_puts(msg, 128);

	n += dtty_puts(NEWLINE, 128);

	return n;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

