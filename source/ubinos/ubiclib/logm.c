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

#define FORMAT_SIZE_MAX		1024
#define OUTPUT_SIZE_MAX		1024
#define DIGIT_SIZE_MAX		128

volatile int	_ubiclib_logm_level[LOGM_CATEGORY__END] = {0, };

const char * 	_ubiclib_logm_levelname[LOGM_LEVEL__END] = {
		"[none   ] ",
		"[always ] ",
		"[fatal  ] ",
		"[error  ] ",
		"[warning] ",
		"[info   ] ",
		"[debug  ] ",
};

int logm_setlevel(int category, int level) {
	int i;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (0 > level || LOGM_LEVEL__END <= level) {
		return -3;
	}

	if (LOGM_CATEGORY__ALL == category) {
		for (i=0; i<LOGM_CATEGORY__END; i++) {
			_ubiclib_logm_level[i] = level;
		}
	}
	else {
		_ubiclib_logm_level[category] = level;
	}

	return 0;
}

int logm_getlevel(int category) {
	if (0 > category || LOGM_CATEGORY__ALL <= category) {
		return -2;
	}

	return _ubiclib_logm_level[category];
}

int logm_printf(int category, int level, const char * tag, const char * format, ...) {
	int n = 0;
	va_list ap;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

	if (NULL != tag) {
		n += dtty_puts(_ubiclib_logm_levelname[level], 128);
		n += dtty_puts(tag , 128);
		n += dtty_puts(": ", 128);
	}

    va_start(ap, format);
    n += vprintf(format, ap);
    va_end(ap);

    n += dtty_puts("\r\n", 128);

    return n;
}

int logm_print(int category, int level, const char * tag, const char * msg) {
	int n = 0;

	if (0 > category || LOGM_CATEGORY__END <= category) {
		return -2;
	}

	if (_ubiclib_logm_level[category] < level) {
		return 0;
	}

	if (NULL != tag) {
		n += dtty_puts(_ubiclib_logm_levelname[level], 128);
		n += dtty_puts(tag , 128);
		n += dtty_puts(": ", 128);
	}

    n += dtty_puts(msg, 128);
    n += dtty_puts("\n\r", 128);

    return n;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

