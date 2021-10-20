/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/bsp.h>
#include <ubinos/ubiclib.h>

#include <stdio.h>

int appmain(int argc, char * argv[]) {
    int r;
    (void) r;

    printf("\n\n\n");
	printf("================================================================================\n");
	printf("helloworld (build time: %s %s)\n", __TIME__, __DATE__);
	printf("================================================================================\n");
	printf("\n");
    printf("\n");

	for (unsigned int i = 0; ; i++) {
		printf("hello world ! (%u)\n", i);
		bsp_busywaitms(1000);
	}

	return 0;
}

