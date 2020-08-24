/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../../_ubiclib.h"

#if (INCLUDE__UBINOS__UBICLIB == 1)
#if (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM)

#undef LOGM_CATEGORY
#define LOGM_CATEGORY LOGM_CATEGORY__UBICLIB

int ubiclib_port_comp_init(void) {
	return 0;
}

int ubiclib_port_comp_init_reent(void) {
	return 0;
}

#endif /* (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM) */
#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

