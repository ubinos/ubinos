#include <ubinos/ubik_test.h>


#if (INCLUDE__APP__ubik_tester == 1)


#include <stdio.h>
#include <stdlib.h>


static void rootfunc(void * arg);

int appmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("ubik_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 192, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void rootfunc(void * arg) {
	int r;

	//logm_setlevel(LOGM_CATEGORY__HEAP, LOGM_LEVEL__INFO);

	printf("\n\r");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 == r) {
		printf("\n\r");
		printf("================================================================================\n\r");
		printf("\n\r");
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
	printf("\n\r");

	unsigned int errcount = 0;
	unsigned int testcountmax = 1; //UINT_MAX;

	for (unsigned int i = 0; i < testcountmax; i++) {
		r = ubik_test_testall();
		if (0 != r) {
			errcount++;
		}
		printf("\r\n");
		printf("<!-- testcount : %8d, errcount : %8d -->\r\n", i, errcount);
		printf("\r\n");

		task_sleep(5000);
	}

    printf("\n\r");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
    r = heap_printheapinfo(NULL);
    if (0 == r) {
        printf("\n\r");
        printf("================================================================================\n\r");
        printf("\n\r");
    }
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

}


#endif /* (INCLUDE__APP__ubik_tester == 1) */


