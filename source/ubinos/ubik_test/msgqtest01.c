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

#if !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

extern volatile unsigned int	_g_ubik_test_result;
extern volatile unsigned int	_g_ubik_test_count1;
extern volatile unsigned int	_g_ubik_test_count2;
extern msgq_pt					_g_ubik_test_msgq;
extern task_pt					_g_ubik_test_task_a[4];

static void msgqtest01_task1func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();
	unsigned int waittick = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS * UBINOS__UBIK_TEST__TASKLOOPCOUNT);
	unsigned char msg[UBINOS__UBIK_TEST__MSGQSIZE];

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 tries to receive a message\r\n");
	r = msgq_receive(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 1: fail at msgq_receive(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}
	printf("task 1 receives a message\r\n");
	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		if (i+0x00 != msg[i]) {
			printf("task 1: wrong message\r\n");
			_g_ubik_test_result = -1;
			goto end0;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 tries to sleep (for %d ms)\r\n", ubik_ticktotimems(waittick * 3));
	task_sleep(waittick * 3);
	printf("\r\n");
	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 tries to receive a message\r\n");
	r = msgq_receive(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 1: fail at msgq_receive(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}
	printf("task 1 receives a message\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		if (i+0x10 != msg[i]) {
			printf("task 1: wrong message\r\n");
			_g_ubik_test_result = -1;
			goto end0;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 tries to receive a message\r\n");
	r = msgq_receive(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 1: fail at msgq_receive(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}
	printf("task 1 receives a message\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		if (i+0x20 != msg[i]) {
			printf("task 1: wrong message\r\n");
			_g_ubik_test_result = -1;
			goto end0;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 tries to receive a message with timeout (for %d ms)\r\n", ubik_ticktotimems(waittick));
	r = msgq_receive_timed(_g_ubik_test_msgq, msg, waittick);
	if (UBIK_ERR__TIMEOUT != r) {
		printf("task 1: fail at msgq_receive_timed(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}
	printf("\r\n");
	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 1 ends\r\n");
}

static void msgqtest01_task2func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();
	unsigned char msg[UBINOS__UBIK_TEST__MSGQSIZE];

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		msg[i] = i+0x00;
	}

	printf("task 2 sends a message\r\n");
	r = msgq_send(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 2: fail at msgq_send(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		msg[i] = i+0x10;
	}

	printf("task 2 sends a message\r\n");
	r = msgq_send(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 2: fail at msgq_send(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		msg[i] = i+0x20;
	}

	printf("task 2 sends a message\r\n");
	r = msgq_send(_g_ubik_test_msgq, msg);
	if (0 != r) {
		printf("task 2: fail at msgq_send(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 3; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 2 ends\r\n");
}

int ubik_test_msgqtest01(void) {
	int r;
	int r2;
	unsigned int count1;
	unsigned int count2;
	unsigned int sleepvalue = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS) * UBINOS__UBIK_TEST__TASKLOOPCOUNT / 3;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_msgqtest01</name>\r\n");
	printf("<description>Test on basic functions of message queue</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = 0;

	_g_ubik_test_count1 = 0;
	_g_ubik_test_count2 = 0;

	_g_ubik_test_task_a[0] = NULL;
	_g_ubik_test_task_a[1] = NULL;

	r = msgq_create(&_g_ubik_test_msgq, UBINOS__UBIK_TEST__MSGQSIZE, UBINOS__UBIK_TEST__MSGQMAXCOUNT);
	if (0 != r) {
		printf("fail at msgq_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	printf("create task 1\r\n");
	r = task_create(&_g_ubik_test_task_a[1-1], msgqtest01_task1func, NULL, task_getpriority(NULL)-1, 0, "msgqtest01 task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	printf("create task 2\r\n");
	r = task_create(&_g_ubik_test_task_a[2-1], msgqtest01_task2func, NULL, task_getpriority(NULL)-2, 0, "msgqtest01 task 2");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 01: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 02: ");
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
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
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
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
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
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
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
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
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
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
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 08: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 09: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 10: ");
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 11: ");
	if (count1 == _g_ubik_test_count1 || count2 != _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue * 2);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 12: ");
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	r = 0;

end2:
	r2 = task_join(_g_ubik_test_task_a, NULL, 2);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

end1:
	r2 = msgq_delete(&_g_ubik_test_msgq);
	if (0 != r2) {
		printf("fail at msgq_delete(), err=%d\r\n", r2);
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

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) */