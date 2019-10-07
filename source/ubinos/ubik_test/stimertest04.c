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

#if (1 != UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET)

#include <stdio.h>
#include <stdlib.h>

extern volatile unsigned int	_g_ubik_test_result;
extern volatile unsigned int	_g_ubik_test_count1;
extern volatile unsigned int	_g_ubik_test_count2;
extern signal_pt				_g_ubik_test_signal;
extern stimer_pt				_g_ubik_test_stimer;
extern task_pt					_g_ubik_test_task_a[4];


static void stimertest04_task1func(void * arg) {
	int i;
	int r;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms() / 2;

//	printf("task 1 waits a signal from stimer\r\n");
	r = signal_wait(_g_ubik_test_signal);
	if (0 != r) {
		printf("task 1: fail at signal_wait(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

//	printf("\r\n");
//	printf("task 1 receives a signal from stimer\r\n");
//	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

//	printf("task 1 waits a signal from stimer\r\n");
	r = signal_wait(_g_ubik_test_signal);
	if (0 != r) {
		printf("task 1: fail at signal_wait(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

//	printf("\r\n");
//	printf("task 1 receives a signal from stimer\r\n");
//	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 1 ends\r\n");
}

static void stimertest04_task2func(void * arg) {
	int i;
	int r;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms() / 2;

//	printf("task 2 waits a signal from stimer\r\n");
	r = signal_wait(_g_ubik_test_signal);
	if (0 != r) {
		printf("task 2: fail at signal_wait(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

//	printf("\r\n");
//	printf("task 2 receives a signal from stimer\r\n");
//	printf("task 2 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

//	printf("task 2 waits a signal from stimer\r\n");
	r = signal_wait(_g_ubik_test_signal);
	if (0 != r) {
		printf("task 2: fail at signal_wait(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

//	printf("\r\n");
//	printf("task 2 receives a signal from stimer\r\n");
//	printf("task 2 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 2 ends\r\n");
}

int ubik_test_stimertest04(void) {
	int r;
	int r2;
	unsigned int count1;
	unsigned int count2;
	unsigned int sleepvalue = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS) * UBINOS__UBIK_TEST__TASKLOOPCOUNT / 3;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_stimertest04</name>\r\n");
	printf("<description>Test on broadcasting notification function of semaphore timer</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = 0;

	_g_ubik_test_count1 = 0;
	_g_ubik_test_count2 = 0;

	_g_ubik_test_task_a[0] = NULL;
	_g_ubik_test_task_a[1] = NULL;

	r = stimer_create(&_g_ubik_test_stimer);
	if (0 != r) {
		printf("fail at stimer_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = signal_create(&_g_ubik_test_signal);
	if (0 != r) {
		printf("fail at signal_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	printf("create task 1\r\n");
	r = task_create(&_g_ubik_test_task_a[0], stimertest04_task1func, NULL, task_getpriority(NULL)-1, 0, "stimertest04 task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	printf("create task 2\r\n");
	r = task_create(&_g_ubik_test_task_a[1], stimertest04_task2func, NULL, task_getpriority(NULL)-1, 0, "stimertest04 task 2");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end3;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 01: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("set stimer\r\n");
	r = stimer_set_signal(_g_ubik_test_stimer, sleepvalue * 3 * 2, _g_ubik_test_signal, 0, STIMER_OPT__BROADCAST);
	if (0 != r) {
		printf("task 1: fail at stimer_set(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end3;
	}

	printf("start stimer\r\n");
	r = stimer_start(_g_ubik_test_stimer);
	if (0 != r) {
		printf("task 1: fail at stimer_start(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end3;
	}

	task_sleep(sleepvalue - sleepvalue/10);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 02: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 03: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 04: ");
	if (count1 == _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 05: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 06: ");
	if (count1 == _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 07: ");
	if (count1 != _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end3;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	r = stimer_stop(_g_ubik_test_stimer);
	if (0 != r) {
		printf("fail at stimer_stop(), err=%d\r\n", r);
		r = -1;
		goto end3;
	}

	r = 0;

end3:
	r2 = task_join(_g_ubik_test_task_a, NULL, 2);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

end2:
	r2 = signal_delete(&_g_ubik_test_signal);
	if (0 != r2) {
		printf("fail at signal_delete(), err=%d\r\n", r2);
		r = -1;
	}

end1:
	r2 = stimer_delete(&_g_ubik_test_stimer);
	if (0 != r2) {
		printf("fail at stimer_delete(), err=%d\r\n", r2);
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

#endif /* (1 != UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET) */