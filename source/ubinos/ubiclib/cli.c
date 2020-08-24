/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "_ubiclib.h"

#if !(UBINOS__UBICLIB__EXCLUDE_CLI == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLI_SLEEP_TICK 1
#define CLI_CMD_SIZE_MAX 127
#define CLI_PROMPT_SIZE_MAX 31
#define CLI_PROMPT__DEFAULT	"cli> "

char _cli_cmd_buf[CLI_CMD_SIZE_MAX + 1] = { 0, };
char _cli_prompt_buf[CLI_PROMPT_SIZE_MAX + 1] = { 0, };

cli_hookfunc_ft _cli_hookfunc = NULL;
void *_cli_hookarg = NULL;

cli_helphookfunc_ft _cli_helphookfunc = NULL;

static int cli_rootfunc(char *str, int len, void *arg);

static int cli_cmdfunc__help(char *str, int len, void *arg);
static int cli_cmdfunc__set(char *str, int len, void *arg);

int cli_sethookfunc(cli_hookfunc_ft hookfunc, void *arg) {
	_cli_hookfunc = hookfunc;
	_cli_hookarg = arg;

	return 0;
}

int cli_sethelphookfunc(cli_helphookfunc_ft helphookfunc) {
	_cli_helphookfunc = helphookfunc;

	return 0;
}

int cli_setprompt(char *prompt) {
	int r = -1;

	if (prompt) {
		strncpy(_cli_prompt_buf, prompt, CLI_PROMPT_SIZE_MAX);
		r = 0;
	}

	return r;
}

void cli_main(void *arg) {
	int r = -1;
	int len;

	if (strlen(_cli_prompt_buf) == 0) {
		strncpy(_cli_prompt_buf, CLI_PROMPT__DEFAULT, CLI_PROMPT_SIZE_MAX);
	}

	printf("\r\n%s", _cli_prompt_buf);
	fflush(stdout);
	do {
		len = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
		if (0 < len) {
			printf("\r\n%s\r\n", _cli_cmd_buf);

			r = cli_rootfunc(_cli_cmd_buf, len, arg);
			if (0 != r) {
				if (NULL != _cli_hookfunc) {
					r = _cli_hookfunc(_cli_cmd_buf, len, arg);
				}
			}
		} else {
			printf("\r\n");
			r = -1;
		}

		if (0 != r) {
			cli_cmdfunc__help(_cli_cmd_buf, len, arg);
			if (NULL != _cli_helphookfunc) {
				_cli_helphookfunc();
			}
		}

		printf("\r\n%s", _cli_prompt_buf);
		fflush(stdout);
	} while (1);
}

static int cli_rootfunc(char *str, int len, void *arg) {
	int r = -1;
	char *tmpstr;
	int tmplen;
	char *cmd = NULL;
	int cmdlen;

	tmpstr = str;
	tmplen = len;

	do {
		cmd = "set ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			printf("\r\n");

			r = cli_cmdfunc__set(tmpstr, tmplen, arg);
			break;
		}

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
		cmd = "mi";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			printf("\r\n");
			heap_printheapinfo(NULL);

			r = 0;
			break;
		}
#endif

#if ( (INCLUDE__UBINOS__UBIK == 1) && !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) )
		cmd = "ki";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			printf("\r\n");
			ubik_printkernelinfo();

			r = 0;
			break;
		}
#endif
	} while(0);

	return r;
}

static int cli_cmdfunc__help(char *str, int len, void *arg) {
	printf("h                       : help\r\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("mi                      : memory information\r\n");
#endif
#if ( (INCLUDE__UBINOS__UBIK == 1) && !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) )
	printf("ki                      : kernel information\r\n");
#endif
	printf("set echo <on|off>       : set echo on/off\r\n");
#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
	printf("set logm                : set log message level\r\n");
#endif

	return 0;
}

static int cli_cmdfunc__set(char *str, int len, void *arg) {
	int r = -1;
	char *tmpstr;
	int tmplen;
	char *cmd = NULL;
	int cmdlen;

	int id;
	int level;

	tmpstr = str;
	tmplen = len;

	do
	{
		cmd = "echo ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
		{
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			cmd = "on";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				r = dtty_setecho(1);
				if (0 == r) {
					printf("    success\r\n");
				} else {
					printf("    fail\r\n");
				}
				break;
			}

			cmd = "off";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				r = dtty_setecho(0);
				if (0 == r) {
					printf("    success\r\n");
				} else {
					printf("    fail\r\n");
				}
				break;
			}
		}

#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
		cmd = "logm";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
		{
			printf("    input category id\r\n");
			printf("        %4d : all    \r\n", -1);
			printf("        %4d : none   \r\n", LOGM_CATEGORY__NONE);
			printf("        %4d : ubinos \r\n", LOGM_CATEGORY__UBINOS);
			printf("        %4d : bsp    \r\n", LOGM_CATEGORY__BSP);
			printf("        %4d : ubik   \r\n", LOGM_CATEGORY__UBIK);
			printf("        %4d : task   \r\n", LOGM_CATEGORY__TASK);
			printf("        %4d : sem    \r\n", LOGM_CATEGORY__SEM);
			printf("        %4d : msgq   \r\n", LOGM_CATEGORY__MSGQ);
			printf("        %4d : condv  \r\n", LOGM_CATEGORY__CONDV);
			printf("        %4d : signal \r\n", LOGM_CATEGORY__SIGNAL);
			printf("        %4d : stimer \r\n", LOGM_CATEGORY__STIMER);
			printf("        %4d : ubiclib\r\n", LOGM_CATEGORY__UBICLIB);
			printf("        %4d : heap   \r\n", LOGM_CATEGORY__HEAP);
			printf("        %4d : user00 \r\n", LOGM_CATEGORY__USER00);
			printf("        %4d : user01 \r\n", LOGM_CATEGORY__USER01);
			printf("        %4d : user02 \r\n", LOGM_CATEGORY__USER02);

			tmplen = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
			if (0 >= tmplen) {
				r = -1;
				break;
			}
			printf("%s\r\n", _cli_cmd_buf);
			id = atoi(_cli_cmd_buf);

			printf("    input level\r\n");
			printf("        %4d : none    \r\n", LOGM_LEVEL__NONE);
			printf("        %4d : always  \r\n", LOGM_LEVEL__ALWAYS);
			printf("        %4d : fatal   \r\n", LOGM_LEVEL__FATAL);
			printf("        %4d : error   \r\n", LOGM_LEVEL__ERROR);
			printf("        %4d : warning \r\n", LOGM_LEVEL__WARNING);
			printf("        %4d : info    \r\n", LOGM_LEVEL__INFO);
			printf("        %4d : debug   \r\n", LOGM_LEVEL__DEBUG);
			printf("        %4d : verbose \r\n", LOGM_LEVEL__VERBOSE);

			tmplen = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
			if (0 >= tmplen) {
				r = -1;
				break;
			}
			printf("%s\r\n", _cli_cmd_buf);
			level = atoi(_cli_cmd_buf);

			r = logm_setlevel(id, level);
			if (0 == r) {
				printf("            success\r\n");
			} else {
				printf("            fail\r\n");
			}
		}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */
	} while (0);

	return r;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_CLI == 1) */

