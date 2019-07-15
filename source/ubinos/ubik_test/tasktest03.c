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

extern volatile unsigned int	_g_ubik_test_result;
extern volatile unsigned int	_g_ubik_test_count1;
extern task_pt					_g_ubik_test_task_a[4];

static void tasktest03_task1func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 2); i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 suspends itself\r\n");
	r = task_suspend(NULL);
	if (0 != r) {
		printf("task 1: fail at task_suspend(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1); i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 1 ends\r\n");
}

int ubik_test_tasktest03(void) {
	int r;
	int r2;
	unsigned int count1;
	unsigned int sleepvalue = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS) * UBINOS__UBIK_TEST__TASKLOOPCOUNT / 3;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_tasktest03</name>\r\n");
	printf("<description>Test on suspend and resume function of task</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = 0;

	_g_ubik_test_count1 = 0;

	printf("create task 1\r\n");
	r = task_create(&_g_ubik_test_task_a[0], tasktest03_task1func, NULL, task_getpriority(NULL)-1, 0, "tasktest03 task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 01: ");
	if (count1 == _g_ubik_test_count1) {
		printf("fail\r\n");
		r = -1;
		goto end1;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("\r\n");
	printf("suspend task 1\r\n");
	r = task_suspend(_g_ubik_test_task_a[0]);
	if (0 != r) {
		printf("fail at task_suspend(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("check point 02: ");
	if (count1 != _g_ubik_test_count1) {
		printf("fail\r\n");
		r = -1;
		goto end1;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("resume task 1\r\n");
	r = task_resume(_g_ubik_test_task_a[0]);
	if (0 != r) {
		printf("fail at task_resume(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 03: ");
	if (count1 == _g_ubik_test_count1) {
		printf("fail\r\n");
		r = -1;
		goto end1;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("check point 04: ");
	if (count1 != _g_ubik_test_count1) {
		printf("fail\r\n");
		r = -1;
		goto end1;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("resume task 1\r\n");
	r = task_resume(_g_ubik_test_task_a[0]);
	if (0 != r) {
		printf("fail at task_resume(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 05: ");
	if (count1 == _g_ubik_test_count1) {
		printf("fail\r\n");
		r = -1;
		goto end1;
	}
	printf("pass\r\n");

	r = 0;

end1:
	r2 = task_join(_g_ubik_test_task_a, NULL, 1);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

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
