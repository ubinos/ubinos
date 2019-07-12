#include <ubinos.h>


#if (INCLUDE__APP__helloworld_mt == 1)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void helloworld_mt_task1func(void * arg);
static void helloworld_mt_task2func(void * arg);

int appmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("helloworld_mt (multi-tasking) (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");
    printf("\n\r");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
    r = heap_printheapinfo(NULL);
    if (0 == r) {
        printf("\n\r");
        printf("================================================================================\n\r");
        printf("\n\r");
    }
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

    srand(time(NULL));

	r = task_create(NULL, helloworld_mt_task1func, NULL, task_getmiddlepriority(), 0, "task1");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, helloworld_mt_task2func, NULL, task_getmiddlepriority(), 0, "task2");
    if (0 != r) {
        logme("fail at task_create\r\n");
    }

	ubik_comp_start();

	return 0;
}

static void helloworld_mt_task1func(void * arg) {
	int r;
	unsigned int delayms;

	(void) r;

    printf("\n\r");

	for (unsigned int i = 0; ; i++) {
	    delayms = (rand() % 10 + 1) * 200;
		printf("1: hello world ! (%u) (delay = %4d ms)\n\r", i, delayms);
		task_sleep(delayms);
	}
}

static void helloworld_mt_task2func(void * arg) {
    int r;
    unsigned int delayms;

    (void) r;

    printf("\n\r");

    for (unsigned int i = 0; ; i++) {
        delayms = (rand() % 10 + 1) * 200;
        printf("2: hello world ! (%u) (delay = %4d ms)\n\r", i, delayms);
        task_sleep(delayms);
    }
}


#endif /* (INCLUDE__APP__HELLOWORLD_MT == 1) */


