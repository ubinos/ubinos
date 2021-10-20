/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/ubiclib_test.h>

#include <stdio.h>
#include <stdlib.h>

static void rootfunc(void *arg);

int appmain(int argc, char *argv[]) {
	int r;
	(void) r;

	printf("\n\n\n");
	printf("================================================================================\n");
	printf("ubiclib_test (build time: %s %s)\n", __TIME__, __DATE__);
	printf("================================================================================\n");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 192, "root");
	ubi_assert(r == 0);

	ubik_comp_start();

	return 0;
}

static void rootfunc(void *arg) {
	int r;

	//logm_setlevel(LOGM_CATEGORY__HEAP, LOGM_LEVEL__INFO);

	printf("\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 == r) {
		printf("\n");
		printf("================================================================================\n");
		printf("\n");
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
	printf("\n");

	unsigned int errcount = 0;
	unsigned int testcountmax = 1; //UINT_MAX;

	for (unsigned int i = 0; i < testcountmax; i++) {
		r = ubiclib_test_test_all();
		if (0 != r) {
			errcount++;
		}
		printf("\n");
		printf("<!-- testcount : %8d, errcount : %8d -->\n", i, errcount);
		printf("\n");

		task_sleep(5000);
	}

	printf("\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 == r) {
		printf("\n");
		printf("================================================================================\n");
		printf("\n");
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

}

