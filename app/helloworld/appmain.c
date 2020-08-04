/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/bsp.h>
#include <ubinos/ubiclib.h>

#if (INCLUDE__APP__helloworld == 1)

#include <stdio.h>


int appmain(int argc, char * argv[]) {
    int r;

    (void) r;

    printf("\n\n\r\n");
	printf("================================================================================\r\n");
	printf("helloworld (build time: %s %s)\r\n", __TIME__, __DATE__);
	printf("================================================================================\r\n");
	printf("\r\n");
    printf("\r\n");

	for (unsigned int i = 0; ; i++) {
		printf("hello world ! (%u)\r\n", i);
		bsp_busywaitms(1000);
	}

	return 0;
}


#endif /* (INCLUDE__APP__HELLOWORLD == 1) */


