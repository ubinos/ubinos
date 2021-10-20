/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void rootfunc(void *arg);
static void clihelphookfunc();
static int clihookfunc(char *str, int len, void *arg);
static int mycmd(char *str, int len, void *arg);

int appmain(int argc, char *argv[])
{
    int r;
    (void) r;

    r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 0, "root");
    ubi_assert(r == 0);

    ubik_comp_start();

    return 0;
}

static void rootfunc(void *arg)
{
    int r;
    (void) r;

    printf("\n\n\n");
    printf("================================================================================\n");
    printf("command line interface tester (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(clihookfunc, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(clihelphookfunc);
    ubi_assert(r == 0);

    r = cli_setprompt("cli_tester> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);
}

static int clihookfunc(char *str, int len, void *arg)
{
    int r = -1;
    char *tmpstr;
    int tmplen;
    char *cmd = NULL;
    int cmdlen;

    tmpstr = str;
    tmplen = len;

    cmd = "mc";
    cmdlen = strlen(cmd);
    if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
    {
        tmpstr = &tmpstr[cmdlen];
        tmplen -= cmdlen;

        r = mycmd(tmpstr, tmplen, arg);
    }

    return r;
}

static void clihelphookfunc()
{
    printf("mc                                      : my command\n");
}

static int mycmd(char *str, int len, void *arg)
{
    printf("\n");
    printf("done\n");

    return 0;
}

