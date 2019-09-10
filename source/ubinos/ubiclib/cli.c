/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam... component of the Ubinos.

 GNU General Public License Usage
 This file may be used under the terms of the GNU
 General Public License version 3.0 as published by the Free Software
 Foundation and appearing in the file license_gpl3.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU General Public License version 3.0 requirements will be
 met: http://www.gnu.org/copyleft/gpl.html.

 GNU Lesser General Public License Usage
 Alternatively, this file may be used under the terms of the GNU Lesser
 General Public License version 2.1 as published by the Free Software
 Foundation and appearing in the file license_lgpl.txt included in the
 packaging of this file. Please review the following information to
 ensure the GNU Lesser General Public License version 2.1 requirements
 will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

 Commercial Usage
 Alternatively, licensees holding valid commercial licenses may
 use this file in accordance with the commercial license agreement
 provided with the software or, alternatively, in accordance with the
 terms contained in a written agreement between you and rightful owner.
 */

#include "_ubiclib.h"

#if !(UBINOS__UBICLIB__EXCLUDE_CLI == 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLI_PROMPT__DEFAULT	"cli> "
#define CLI_SLEEP_TICK 1
#define CLI_BUF_SIZE 128
#define CLI_PROMPT_SIZE 16

char _cli_buf[CLI_BUF_SIZE] = { 0, };
char _cli_prompt[CLI_PROMPT_SIZE] = { 0, };

cli_hookfunc_ft _cli_hookfunc = NULL;
void *_cli_hookarg = NULL;

cli_helphookfunc_ft _cli_helphookfunc = NULL;

static int cli_rootfunc(char *str, int max, void *arg);

static int cli_cmdfunc__help(char *str, int max, void *arg);
static int cli_cmdfunc__set(char *str, int max, void *arg);

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
		strncpy(_cli_prompt, prompt, CLI_PROMPT_SIZE);
		r = 0;
	}

	return r;
}

void cli_main(void *arg) {
	int r = 0;
	int len;

	if (strlen(_cli_prompt) == 0) {
		strncpy(_cli_prompt, CLI_PROMPT__DEFAULT, CLI_PROMPT_SIZE);
	}

	printf("\n\r%s", _cli_prompt);
	fflush(stdout);
	while (0 == r) {
		len = dtty_gets(_cli_buf, CLI_BUF_SIZE);
		if (0 < len) {
			printf("\n\r%s\n\r", _cli_buf);

			r = cli_rootfunc(_cli_buf, CLI_BUF_SIZE, arg);
			if (0 != r) {
				if (NULL != _cli_hookfunc) {
					r = _cli_hookfunc(_cli_buf, CLI_BUF_SIZE, arg);
				}
			}
		} else {
			printf("\n\r\n\r");
			r = -1;
		}

		if (0 != r) {
			cli_cmdfunc__help(_cli_buf, CLI_BUF_SIZE, arg);
			if (NULL != _cli_helphookfunc) {
				_cli_helphookfunc();
			}
		}

		printf("\n\r%s", _cli_prompt);
		fflush(stdout);

		r = 0;
	}
}

static int cli_rootfunc(char *str, int max, void *arg) {
	int r = -1;
	char *tstr;
	int tmax;
	void *targ;

	tstr = str;
	tmax = max;
	targ = arg;
	if (4 < tmax && 0 == strncmp(tstr, "set ", 4)) {
		printf("\n\r");
		tstr = &str[4];
		tmax = max - 4;
		targ = arg;
		r = cli_cmdfunc__set(tstr, tmax, targ);
	}
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	else if (3 < tmax && 0 == strncmp(tstr, "mi", 3)) {
		printf("\n\r");
		heap_printheapinfo(NULL);
		r = 0;
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	return r;
}

static int cli_cmdfunc__help(char *str, int max, void *arg) {
	printf("h           : help\n\r");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("mi          : memory information\n\r");
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
	printf("set logm    : set log message level\n\r");
#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */
	printf("set echo    : set echo\n\r");

	return 0;
}

static int cli_cmdfunc__set(char *str, int max, void *arg) {
	int r = -1;
	int len;
	int value;
	int value2;
	char *tstr;
	int tmax;

	tstr = str;
	tmax = max;
	if (0 == strncmp(tstr, "echo", tmax)) {
		printf("    set echo\n\r");
		printf("        on/off?\n\r");
		printf("            on              : 1\n\r");
		printf("            off             : 0\n\r");
		len = dtty_gets(_cli_buf, CLI_BUF_SIZE);
		if (0 < len) {
			printf("%s\n\r", _cli_buf);
			value = atoi(_cli_buf);
			printf("        set echo %s\n\r", value ? "on" : "off");
			r = dtty_setecho(value);
			if (0 == r) {
				printf("            success\n\r");
			} else {
				printf("            fail\n\r");
			}
			r = 0;
		} else {
			r = -1;
		}
	}
#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
	else if (0 == strncmp(tstr, "logm", tmax)) {
		printf("    set log message level\n\r");
		printf("        category?\n\r");
		printf("            all             : %d\n\r", LOGM_CATEGORY__ALL);
		printf("            default         : %d\n\r", LOGM_CATEGORY__DEFAULT);
		printf("            heap            : %d\n\r", LOGM_CATEGORY__HEAP);
		printf("            bitmap          : %d\n\r", LOGM_CATEGORY__BITMAP);
		printf("            user00          : %d\n\r", LOGM_CATEGORY__USER00);
		printf("            user01          : %d\n\r", LOGM_CATEGORY__USER01);
		printf("            user02          : %d\n\r", LOGM_CATEGORY__USER02);
		len = dtty_gets(_cli_buf, CLI_BUF_SIZE);
		if (0 < len) {
			printf("%s\n\r", _cli_buf);
			value = atoi(_cli_buf);
			printf("        level?\n\r");
			printf("            none            : %d\n\r", LOGM_LEVEL__NONE);
			printf("            always          : %d\n\r", LOGM_LEVEL__ALWAYS);
			printf("            fatal           : %d\n\r", LOGM_LEVEL__FATAL);
			printf("            error           : %d\n\r", LOGM_LEVEL__ERROR);
			printf("            warning         : %d\n\r", LOGM_LEVEL__WARNING);
			printf("            info            : %d\n\r", LOGM_LEVEL__INFO);
			printf("            debug           : %d\n\r", LOGM_LEVEL__DEBUG);
			len = dtty_gets(_cli_buf, CLI_BUF_SIZE);
			if (0 < len) {
				printf("%s\n\r", _cli_buf);
				value2 = atoi(_cli_buf);
				printf("        set log message level of category %d to %d\n\r", value, value2);
				r = logm_setlevel(value, value2);
				if (0 == r) {
					printf("            success\n\r");
				} else {
					printf("            fail\n\r");
				}
				r = 0;
			} else {
				r = -1;
			}
		} else {
			r = -1;
		}
	}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

	return r;
}

#endif /* !(UBINOS__UBICLIB__EXCLUDE_CLI == 1) */

