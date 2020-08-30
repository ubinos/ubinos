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

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)
static int cli_cmdfunc__heap(char *str, int len, void *arg);
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */

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

	printf("\n%s", _cli_prompt_buf);
	fflush(stdout);
	for (;;) {
		len = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
		if (0 < len) {
			printf("\n%s\n", _cli_cmd_buf);

			r = cli_rootfunc(_cli_cmd_buf, len, arg);
			if (0 != r) {
				if (NULL != _cli_hookfunc) {
					r = _cli_hookfunc(_cli_cmd_buf, len, arg);
				}
			}
		} else {
			printf("\n");
			r = -1;
		}

		if (0 != r) {
			cli_cmdfunc__help(_cli_cmd_buf, len, arg);
			if (NULL != _cli_helphookfunc) {
				_cli_helphookfunc();
			}
		}

		printf("\n%s", _cli_prompt_buf);
		fflush(stdout);
	}
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

			printf("\n");

			r = cli_cmdfunc__set(tmpstr, tmplen, arg);
			break;
		}

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
		cmd = "mi";
		cmdlen = strlen(cmd);
		if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			printf("\n");
			heap_printheapinfo(NULL);

			r = 0;
			break;
		}
#endif

#if ( (INCLUDE__UBINOS__UBIK == 1) && !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) )
		cmd = "ki";
		cmdlen = strlen(cmd);
		if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			printf("\n");
			ubik_printkernelinfo();

			r = 0;
			break;
		}
#endif

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)
		cmd = "heap ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			printf("\n");

			r = cli_cmdfunc__heap(tmpstr, tmplen, arg);
			break;
		}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */

		break;
	} while (1);

	return r;
}

static int cli_cmdfunc__help(char *str, int len, void *arg) {
	printf("\n");
	printf("h                                   : help\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("mi                                  : memory information\n");
#endif
#if ( (INCLUDE__UBINOS__UBIK == 1) && !(UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING == 1) )
	printf("ki                                  : kernel information\n");
#endif
	printf("set echo <on|off>                   : set echo on/off\n");
	printf("set autocr <on|off>                 : set auto carriage return on/off\n");
#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
	printf("set logm                            : set log message level\n");
#endif
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)
	printf("heap param <algorithm> <size> (m)   : calculate heap parameters\n");
	printf("    algorithm: heap algorithm\n");
	printf("        group    : group system\n");
	printf("        pgroup   : pure group system (without tailing) \n");
	printf("        bbuddy   : binary buddy system\n");
	printf("        wbuddy   : weighted buddy system\n");
	printf("        bestfit  : best fit\n");
	printf("        firstfit : first fit\n");
	printf("        nextfit  : next fit\n");
	printf("    size: heap size \n");
	printf("    m: M value for group system and pure group system\n");
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */
	printf("\n");
	return 0;
}

static int cli_cmdfunc__set(char *str, int len, void *arg) {
	int r = -1;
	char *tmpstr;
	int tmplen;
	char *cmd = NULL;
	int cmdlen;

	tmpstr = str;
	tmplen = len;

	do {
		cmd = "echo ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			cmd = "on";
			cmdlen = strlen(cmd);
			if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				r = dtty_setecho(1);
				if (0 == r) {
					printf("    success\n");
				} else {
					printf("    fail\n");
				}
				break;
			}

			cmd = "off";
			cmdlen = strlen(cmd);
			if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				r = dtty_setecho(0);
				if (0 == r) {
					printf("    success\n");
				} else {
					printf("    fail\n");
				}
				break;
			}
		}

		cmd = "autocr ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			cmd = "on";
			cmdlen = strlen(cmd);
			if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				r = dtty_setautocr(1);
				if (0 == r) {
					printf("    success\n");
				} else {
					printf("    fail\n");
				}
				break;
			}

			cmd = "off";
			cmdlen = strlen(cmd);
			if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				r = dtty_setautocr(0);
				if (0 == r) {
					printf("    success\n");
				} else {
					printf("    fail\n");
				}
				break;
			}
		}

#if !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1)
		cmd = "logm";
		cmdlen = strlen(cmd);
		if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			int id;
			int level;

			printf("    input category id\n\n");

			printf("        %4d : [ALL    ]\n", -1);
			for (int i = 0; i < LOGM_CATEGORY__END; i++) {
				printf("        %4d : %s\n", i, _ubiclib_logm_categoryname[i]);
			}

			tmplen = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
			if (0 >= tmplen) {
				r = -1;
				break;
			}
			printf("%s\n", _cli_cmd_buf);
			id = atoi(_cli_cmd_buf);

			printf("    input level\n\n");

			for (int i = 1; i < LOGM_LEVEL__END; i++) {
				printf("        %4d : %s\n", i, _ubiclib_logm_levelname[i]);
			}

			tmplen = dtty_gets(_cli_cmd_buf, CLI_CMD_SIZE_MAX);
			if (0 >= tmplen) {
				r = -1;
				break;
			}
			printf("%s\n", _cli_cmd_buf);
			level = atoi(_cli_cmd_buf);

			r = logm_setlevel(id, level);
			if (0 == r) {
				printf("            success\n");
			} else {
				printf("            fail\n");
			}
		}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_LOGM == 1) */

		break;
	} while (1);

	return r;
}

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)
static int cli_cmdfunc__heap(char *str, int len, void *arg) {
	int r = -1;
	char *tmpstr;
	int tmplen;
	char *cmd = NULL;
	int cmdlen;

	tmpstr = str;
	tmplen = len;

	do {
		cmd = "param ";
		cmdlen = strlen(cmd);
		if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
			tmpstr = &tmpstr[cmdlen];
			tmplen -= cmdlen;

			unsigned int region_size;
			unsigned int region_m;
			unsigned int fbl_count;
			unsigned int fbl_memsize;
			unsigned int bitmap_memsize;

			r = -1;

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__GROUP == 1)
			cmd = "group ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				tmpstr = &tmpstr[cmdlen];
				tmplen -= cmdlen;

				sscanf(tmpstr, "%u %u", &region_size, &region_m);

				fbl_count = heap_group_calc_fblcount(region_size, region_m);
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__GROUP\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__GROUP == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__PGROUP == 1)
			cmd = "pgroup ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				tmpstr = &tmpstr[cmdlen];
				tmplen -= cmdlen;

				sscanf(tmpstr, "%u %u", &region_size, &region_m);

				fbl_count = heap_pgroup_calc_fblcount(region_size, region_m);
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__PGROUP\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__PGROUP == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BBUDDY == 1)
			cmd = "bbuddy ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				tmpstr = &tmpstr[cmdlen];
				tmplen -= cmdlen;

				sscanf(tmpstr, "%u", &region_size);
				region_m = 2;

				fbl_count = heap_pgroup_calc_fblcount(region_size, region_m);
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__BBUDDY\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BBUDDY == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__WBUDDY == 1)
			cmd = "wbuddy ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				tmpstr = &tmpstr[cmdlen];
				tmplen -= cmdlen;

				sscanf(tmpstr, "%u", &region_size);
				region_m = 2;

				fbl_count = heap_wbuddy_calc_fblcount(region_size, region_m);
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__WBUDDY\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__WBUDDY == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BESTFIT == 1)
			cmd = "bestfit ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0) {
				region_m = 2;

				fbl_count = 2;
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__BESTFIT\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BESTFIT == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__FIRSTFIT == 1)
			cmd = "firstfit ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				region_m = 2;

				fbl_count = 2;
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__FIRSTFIT\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__FIRSTFIT == 1) */
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__NEXTFIT == 1)
			cmd = "nextfit ";
			cmdlen = strlen(cmd);
			if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
			{
				region_m = 2;

				fbl_count = 2;
				fbl_memsize = sizeof(edlist_t) * fbl_count;
				bitmap_memsize = bitmap_getmemsize(fbl_count);

				r = 0;

				printf("    UBINOS__UBICLIB__HEAP_DIR...\n");
				printf("        algorithm                           (..._ALGORITHM)     : UBINOS__UBICLIB__HEAP_ALGORITHM__NEXTFIT\n");
			}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__NEXTFIT == 1) */

			if (r == 0) {
				printf("        m value                             (..._M)             : %u\n", region_m);
				printf("        fbl (free block list)\n");
				printf("            fbl count minimum value         (..._FBLCOUNT)      : %u\n", fbl_count);
				printf("            fbl memory size                                     : %u bytes\n", fbl_memsize);
				printf("        fblbm (bitmap for indexing free block list)\n");
				printf("            fblbm memory size minimum value (..._FBLBM_BUFSIZE) : %u\n", bitmap_memsize);

				r = 0;
				break;
			} else {
				printf(" not supported\n");
				r = 0;
				break;
			}
		}

		break;
	} while (1);

	return r;
}
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */

#endif /* !(UBINOS__UBICLIB__EXCLUDE_CLI == 1) */

