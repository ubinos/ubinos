/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos/ubik_test.h>

#if !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

int ubik_test_msgqtest04(void) {
	int r;
	int r2;
	int i;
	int j;
	msgq_pt * msgq_p;
	unsigned int size_old;
	unsigned int count_old;
	unsigned int size;
	unsigned int count;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_msgqtest04</name>\r\n");
	printf("<description>Memory leak test of message queue</description>\n\r");

	printf("<message>\n\r");

	ubik_collectgarbage();

	r = heap_getallocatedsize(NULL, &size_old);
	if (0 != r) {
		printf("fail at heap_getallocatedsize\r\n");
		goto end0;
	}

	r = heap_getallocatedcount(NULL, &count_old);
	if (0 != r) {
		printf("fail at heap_getallocatedcount\r\n");
		goto end0;
	}

	msgq_p = malloc(sizeof(msgq_pt) * UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT);
	if (NULL == msgq_p) {
		printf("fail at malloc()\r\n");
		goto end0;
	}

	r = 0;

	printf("|----------|\r\n ");
	for (i=0; i<UBINOS__UBIK_TEST__MEMLEAK_TESTCOUNT; i++) {
		for (j=0; j<UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT; j++) {
			msgq_p[j] = NULL;
		}
		for (j=0; j<UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT; j++) {
			r = msgq_create(&msgq_p[j], UBINOS__UBIK_TEST__MSGQSIZE, 1);
			if (0 != r) {
				printf("\r\n");
				printf("test %d, msgq %d\r\n", i, j);
				printf("fail at msgq_create(), err=%d\r\n", r);
				r = -1;
				break;
			}
		}
		for (j=0; j<UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT; j++) {
			if (NULL != msgq_p[j]) {
				r2 = msgq_delete(&msgq_p[j]);
				if (0 != r2) {
					printf("\r\n");
					printf("fail at msgq_delete(), err=%d\r\n", r2);
					r = -1;
					break;
				}
			}
		}
		if (0 != r) {
			break;
		}
		if (0 == i%(UBINOS__UBIK_TEST__MEMLEAK_TESTCOUNT/10)) {
			printf("+");
		}
	}
	if (0 == r) {
		printf("\r\n");
		printf("pass %d tests creating and deleting %d message queue\r\n", i, j);
	}

	free(msgq_p);

	if (0 == r) {
		ubik_collectgarbage();

		r2 = heap_getallocatedsize(NULL, &size);
		if (0 != r2) {
			printf("fail at heap_getallocatedsize\r\n");
			r = -1;
			goto end0;
		}

		r2 = heap_getallocatedcount(NULL, &count);
		if (0 != r2) {
			printf("fail at heap_getallocatedcount\r\n");
			r = -1;
			goto end0;
		}

		if (size_old != size || count_old != count) {
			printf("memory leak was detected\r\n");
			r = -1;
			goto end0;
		}
	}

end0:
	if (0 != r) {
		r = -1;
	}
	else {
		r = 0;
	}

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

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) */
