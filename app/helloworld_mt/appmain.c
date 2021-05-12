/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>


#if (INCLUDE__APP__helloworld_mt == 1)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void helloworld_mt_task1func(void * arg);
static void helloworld_mt_task2func(void * arg);

int appmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n");
	printf("================================================================================\n");
	printf("helloworld_mt (multi-tasking) (build time: %s %s)\n", __TIME__, __DATE__);
	printf("================================================================================\n");
    printf("\n");

    srand(time(NULL));

	r = task_create(NULL, helloworld_mt_task1func, NULL, task_getmiddlepriority(), 0, "task1");
	if (0 != r) {
		logme("fail at task_create");
	}

	r = task_create(NULL, helloworld_mt_task2func, NULL, task_getmiddlepriority(), 0, "task2");
    if (0 != r) {
        logme("fail at task_create");
    }

	ubik_comp_start();

	return 0;
}

static void helloworld_mt_task1func(void * arg) {
	int r;
	unsigned int delayms;

	(void) r;

    printf("\n");

	for (unsigned int i = 0; ; i++) {
	    delayms = (rand() % 10 + 1) * 200;
		printf("1: hello world ! (%u) (delay = %4d ms)\n", i, delayms);
		task_sleepms(delayms);
	}
}

static void helloworld_mt_task2func(void * arg) {
    int r;
    unsigned int delayms;

    (void) r;

    printf("\n");

    for (unsigned int i = 0; ; i++) {
        delayms = (rand() % 10 + 1) * 200;
        printf("2: hello world ! (%u) (delay = %4d ms)\n", i, delayms);
        task_sleepms(delayms);
    }
}


#endif /* (INCLUDE__APP__helloworld_mt == 1) */


