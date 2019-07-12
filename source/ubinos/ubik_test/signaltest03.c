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

#if !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

static void signaltest03_task1func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1); i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("Task 1 waits signal\r\n");
	r = signal_wait(_g_ubik_test_signal);
	if (UBINOS__UBIK_TEST__SIGTYPE != r) {
		printf("Task 1: fail at signal_wait(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}
	printf("Task 1 receives signal\r\n");

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1); i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("Task 1 ends\r\n");
}

static void signaltest03_task2func(void * arg) {
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1); i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("Task 2 ends\r\n");
}

static void signaltest03_task3func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 3); i++) {
		_g_ubik_test_count3++;
		printf("3");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("Task 3 sends signal\r\n");
	r = signal_send(_g_ubik_test_signal, UBINOS__UBIK_TEST__SIGTYPE);
	if (0 != r) {
		printf("Task 3: fail at signal_send(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<(UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1); i++) {
		_g_ubik_test_count3++;
		printf("3");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("Cancels sender setting\r\n");
	r = signal_setsender(_g_ubik_test_signal, NULL);
	if (0 != r) {
		printf("Task 3: fail at signal_setsender(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

end0:
	printf("Task 3 ends\r\n");
}

int ubik_test_signaltest03(void) {
	int r;
	int r2;
	unsigned int count1;
	unsigned int count2;
	unsigned int count3;
	unsigned int sleepvalue = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS) * UBINOS__UBIK_TEST__TASKLOOPCOUNT / 3;
	int pri;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_signaltest03</name>\r\n");
	printf("<description>Priority inheritance test of signal</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = 0;

	_g_ubik_test_count1 = 0;
	_g_ubik_test_count2 = 0;
	_g_ubik_test_count3 = 0;

	_g_ubik_test_task_a[0] = NULL;
	_g_ubik_test_task_a[1] = NULL;
	_g_ubik_test_task_a[2] = NULL;

	r = signal_create(&_g_ubik_test_signal);
	if (0 != r) {
		printf("fail at signal_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	printf("Task 3 begins\r\n");
	r = task_create(&_g_ubik_test_task_a[3-1], signaltest03_task3func, NULL, task_getpriority(NULL)-3, 0, "signaltest03 task 3");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	printf("Set task 3 as a sender\r\n");
	r = signal_setsender(_g_ubik_test_signal, _g_ubik_test_task_a[2]);
	if (0 != r) {
		printf("fail at signal_setsender(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 01: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 == _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("\r\n");
	printf("Task 1 begins\r\n");
	r = task_create(&_g_ubik_test_task_a[1-1], signaltest03_task1func, NULL, task_getpriority(NULL)-1, 0, "signaltest03 task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 02: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 != _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	pri = task_getpriority(_g_ubik_test_task_a[0]);
	printf("Priority of task 1 is %d\r\n", pri);
	pri = task_getpriority(_g_ubik_test_task_a[2]);
	printf("Priority of task 3 is %d\r\n", pri);

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	pri = task_getpriority(_g_ubik_test_task_a[2]);
	printf("Priority of task 3 is %d\r\n", pri);
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 03: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 == _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("\r\n");
	printf("Task 2 begins\r\n");
	r = task_create(&_g_ubik_test_task_a[2-1], signaltest03_task2func, NULL, task_getpriority(NULL)-2, 0, "signaltest03 task 2");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 04: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 == _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	pri = task_getpriority(_g_ubik_test_task_a[2]);
	printf("Priority of task 3 is %d\r\n", pri);
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 05: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 != _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 06: ");
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2 || count3 != _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	count3 = _g_ubik_test_count3;
	printf("\r\n");
	printf("Checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("Check point 07: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2 || count3 == _g_ubik_test_count3) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	r = 0;

end2:
	r2 = task_join(_g_ubik_test_task_a, NULL, 3);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

end1:
	r2 = signal_delete(&_g_ubik_test_signal);
	if (0 != r2) {
		printf("fail at signal_delete(), err=%d\r\n", r2);
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

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) */
