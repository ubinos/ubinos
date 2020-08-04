/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#if (INCLUDE__APP__cli_tester == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void clihelphookfunc();
static int clihookfunc(char *str, int len, void *arg);
static int mycmd(char *str, int len, void *arg);

int appmain(int argc, char *argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("command line interface tester (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");
	printf("\n\r");

	dtty_setecho(1);

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

static int clihookfunc(char *str, int len, void *arg) {
	int r = -1;
	char *tmpstr;
	int tmplen;
	char *cmd = NULL;
	int cmdlen;

	tmpstr = str;
	tmplen = len;

	cmd = "mc";
	cmdlen = strlen(cmd);
	if (tmplen >= cmdlen && strncmp(tmpstr, cmd, tmplen) == 0) {
		tmpstr = &tmpstr[cmdlen];
		tmplen -= cmdlen;

		r = mycmd(tmpstr, tmplen, arg);
	}

	return r;
}

static void clihelphookfunc() {
	printf("mc                      : my command\n\r");
}

static int mycmd(char *str, int len, void *arg) {
	printf("\n\r");
	printf("do my command\n\r");

	return 0;
}

#endif /* (INCLUDE__APP__cli_tester == 1) */

