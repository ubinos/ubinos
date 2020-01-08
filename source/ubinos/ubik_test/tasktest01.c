/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the lib_ubik_test component of the Ubinos.

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

#include <ubinos/ubik_test.h>

#if !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

#define TASKARG				((void *) -3)
#define TASKWORKINGTIMEMS   1000

extern volatile unsigned int	_g_ubik_test_result;
extern task_pt					_g_ubik_test_task_a[4];

static void tasktest01_task1func(void * arg) {
	unsigned int waitvalue = TASKWORKINGTIMEMS * bsp_getbusywaitcountperms();

	if (TASKARG == arg) {
		printf("task 1 is running\r\n");

		bsp_busywait(waitvalue);

		_g_ubik_test_result = 0;
	}
	else {
		printf("task 1 received wrong argument\r\n");
	}

	printf("task 1 ends\r\n");
}

int ubik_test_tasktest01(void) {
	int r;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_tasktest01</name>\r\n");
	printf("<description>Test on basic functions of task</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = -1;

	printf("create task 1\r\n");
	r = task_create(&_g_ubik_test_task_a[0], tasktest01_task1func, TASKARG, task_getpriority(NULL)-1, 0, "tasktest01 task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = task_join(_g_ubik_test_task_a, NULL, 1);
	if (0 != r) {
		printf("fail at task_join(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = 0;

end0:
	if (0 != r || 0 > _g_ubik_test_result) {
		r = -1;
	}
	else {
		r = 0;
	}

	printf("</message>\n\r");

	printf("<result>");
	if (0 == r) {
		printf("pass");
	}
	else {
		printf("fail");
	}
	printf("</result>\r\n");
	printf("</test>\r\n");
	printf("\r\n");
	return r;
}

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1) */
