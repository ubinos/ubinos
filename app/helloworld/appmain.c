#include <ubinos/bsp.h>
#include <ubinos/ubiclib.h>

#if (INCLUDE__APP__helloworld == 1)

#include <stdio.h>


int appmain(int argc, char * argv[]) {
    int r;

    (void) r;

    printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("helloworld (build time: %s %s)\n\r", __TIME__, __DATE__);
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
    printf("\n\r");

	for (unsigned int i = 0; ; i++) {
		printf("hello world ! (%u)\n\r", i);
		bsp_busywaitms(1000);
	}

	return 0;
}


#endif /* (INCLUDE__APP__HELLOWORLD == 1) */


