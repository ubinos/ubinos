/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/ubik_test.h>

#if !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

int ubik_test_misctest01(void) {
	int r;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_misctest01</name>\r\n");
	printf("<description>System information</description>\n\r");

	printf("<message>\n\r");

	printf("\n\r");
	printf("----------------------------------------------------------------------------------------------------\r\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 < r) {
		printf("fail at heap_printheapinfo\r\n");
		r = -1;
		goto end0;
	}
	printf("----------------------------------------------------------------------------------------------------\r\n");
	printf("\r\n");
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	r = ubik_printkernelinfo();
	if (0 != r) {
		printf("fail at ubik_printkernelinfo\r\n");
		r = -1;
		goto end0;
	}

end0:
	printf("</message>\n\r");

	printf("<result>");
	if (0 == r) {
		printf("pass");
	}
	else {
		printf("fail");
	}
	printf("</result>\r\n");
	printf("</test>\r\n");
	printf("\r\n");
	return r;
}

#endif /* !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1) */
