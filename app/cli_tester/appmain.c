#include <ubinos.h>

#if (INCLUDE__APP__cli_tester == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int clihookfunc(char *str, int max, void *arg);
static void clihelphookfunc();

int appmain(int argc, char *argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("command line interface tester (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");
	printf("\n\r");

	r = cli_sethookfunc(clihookfunc, NULL);
	if (0 != r) {
		logme("fail at cli_sethookfunc\n\r");
	}

	r = cli_sethelphookfunc(clihelphookfunc);
	if (0 != r) {
		logme("fail at cli_sethelphookfunc\n\r");
	}

	r = cli_setprompt("cli_tester> ");
	if (0 != r) {
		logme("fail at cli_setprompt\n\r");
	}

	r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
	if (0 != r) {
		logme("fail at task_create\n\r");
	}

	ubik_comp_start();

	return 0;
}

static int clihookfunc(char *str, int max, void *arg) {
	int r = -1;
	char *tstr;
	int tmax;
	void *targ;

	tstr = str;
	tmax = max;
	targ = arg;
	(void) targ;
#if !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1)
	if (3 < tmax && 0 == strncmp(tstr, "ki", 3)) {
		printf("\n\r");
		ubik_printkernelinfo();
		r = 0;
	}
#endif /* !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) */

	return r;
}

static void clihelphookfunc() {
#if !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1)
	printf("ki          : kernel information\n\r");
#endif /* !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) */
}

#endif /* (INCLUDE__APP__cli_tester == 1) */

