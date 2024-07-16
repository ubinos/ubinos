/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void root_func(void *arg);

static void cli_help_hook_func();
static int cli_hook_func(char *str, int len, void *arg);

static int cli_cmd_hello(char *str, int len, void *arg);
static int cli_cmd_add(char *str, int len, void *arg);
static int cli_cmd_sub(char *str, int len, void *arg);

int appmain(int argc, char *argv[])
{
    int r;
    (void) r;

    r = task_create(NULL, root_func, NULL, task_getmiddlepriority(), 0, "root");
    ubi_assert(r == 0);

    ubik_comp_start();

    return 0;
}

static void root_func(void *arg)
{
    int r;
    (void) r;

    printf("\n\n\n");
    printf("================================================================================\n");
    printf("command line interface tester (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(cli_hook_func, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(cli_help_hook_func);
    ubi_assert(r == 0);

    r = cli_setprompt("cli_tester> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);
}

static int cli_hook_func(char *str, int len, void *arg)
{
    int r = -1;
    char *tmpstr;
    int tmplen;
    char *cmd = NULL;
    int cmdlen;

    tmpstr = str;
    tmplen = len;

    do
    {
        cmd = "hello";
        cmdlen = strlen(cmd);
        if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
        {
            tmpstr = &tmpstr[cmdlen];
            tmplen -= cmdlen;

            r = cli_cmd_hello(tmpstr, tmplen, arg);
            break;
        }

        cmd = "add ";
        cmdlen = strlen(cmd);
        if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
        {
            tmpstr = &tmpstr[cmdlen];
            tmplen -= cmdlen;

            r = cli_cmd_add(tmpstr, tmplen, arg);
            break;
        }

        cmd = "sub ";
        cmdlen = strlen(cmd);
        if (tmplen >= cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
        {
            tmpstr = &tmpstr[cmdlen];
            tmplen -= cmdlen;

            r = cli_cmd_sub(tmpstr, tmplen, arg);
            break;
        }

        break;
    } while (1);

    return r;
}

static void cli_help_hook_func()
{
    printf("hello                                   : say hello\n");
    printf("    ex: hello\n");

    printf("add <operand1> <operand2>               : add two operands\n");
    printf("    ex: add 2 5\n");

    printf("sub <operand1> <operand2>               : subtract two operands\n");
    printf("    ex: sub 2 5\n");
}

static int cli_cmd_hello(char *str, int len, void *arg)
{
    printf("    Hello, nice to meet you.\n");

    return 0;
}

static int cli_cmd_add(char *str, int len, void *arg)
{
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;

    ubi_assert_not_null(str);
    ubi_assert(len > 0);

    sscanf(str, "%d %d", &operand1, &operand2);
    result = operand1 + operand2;
    printf("    result = %d\n", result);

    return 0;
}

static int cli_cmd_sub(char *str, int len, void *arg)
{
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;

    ubi_assert_not_null(str);
    ubi_assert(len > 0);

    sscanf(str, "%d %d", &operand1, &operand2);
    result = operand1 - operand2;
    printf("    result = %d\n", result);

    return 0;
}

