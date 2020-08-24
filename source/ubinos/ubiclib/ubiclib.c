/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_ubiclib.h"

#if (INCLUDE__UBINOS__UBICLIB == 1)

#include <assert.h>

#undef LOGM_CATEGORY
#define LOGM_CATEGORY LOGM_CATEGORY__UBICLIB

int ubiclib_comp_init(void) {
	int r = 0;

	r = ubiclib_port_comp_init();

	return r;
}

int ubiclib_comp_init_reent(void) {
	int r = 0;

	r = ubiclib_port_comp_init_reent();

	return r;
}

#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

