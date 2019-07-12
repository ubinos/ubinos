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

#if ( !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET3 == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) && \
	  !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) )

#include <stdio.h>
#include <stdlib.h>

#define SIGOBJCOUNT		5

extern volatile unsigned int	_g_ubik_test_result;
extern volatile unsigned int	_g_ubik_test_count1;
extern volatile unsigned int	_g_ubik_test_count2;
extern mutex_pt					_g_ubik_test_mutex;
extern mutex_pt					_g_ubik_test_mutex2;
extern signal_pt				_g_ubik_test_signal;
extern condv_pt					_g_ubik_test_condv;
extern sem_pt					_g_ubik_test_sem;
extern msgq_pt					_g_ubik_test_msgq;
extern task_pt					_g_ubik_test_task_a[4];

static void tasktest07_task1func(void * arg) {
	int r;
	int i;
	int j;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();
	unsigned int waittick = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS * UBINOS__UBIK_TEST__TASKLOOPCOUNT);
	unsigned char msg[UBINOS__UBIK_TEST__MSGQSIZE];

	void * 	sigobj_a[SIGOBJCOUNT];
	int		sigtype_a[SIGOBJCOUNT];
	void * 	param_a[SIGOBJCOUNT];

	sigobj_a[0] =_g_ubik_test_mutex;
	sigobj_a[1] =_g_ubik_test_signal;
	sigobj_a[2] =_g_ubik_test_condv;
	sigobj_a[3] =_g_ubik_test_sem;
	sigobj_a[4] =_g_ubik_test_msgq;

	param_a[0]  = NULL;
	param_a[1]  = NULL;
	param_a[2]  = (void *) _g_ubik_test_mutex2;
	param_a[3]  = NULL;
	param_a[4]  = (void *) msg;

	r = task_setmaxwaitsigobj(NULL, SIGOBJCOUNT);
	if (0 != r) {
		printf("task 1: fail at task_setmaxwaitsigobj(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 waits for multiple signals (without all option)\r\n");

	r = mutex_lock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = task_waitforsigobjs(sigobj_a, sigtype_a, param_a, SIGOBJCOUNT, 0);
	if (0 != r) {
		printf("task 1: fail at task_waitforsigobjs(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = mutex_unlock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<SIGOBJCOUNT; i++) {
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 5:
			if (-1 != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			break;
		case 4:
			if (0 != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			for (j=0; j<UBINOS__UBIK_TEST__MSGQSIZE; j++) {
				if (j != msg[j]) {
					printf("task 1: received message is wrong\r\n");
					_g_ubik_test_result = -1;
					goto end0;
				}
			}
			break;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 waits for multiple signals with all option\r\n");

	r = mutex_lock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = task_waitforsigobjs(sigobj_a, sigtype_a, param_a, SIGOBJCOUNT, TASK_WAITOPT__ALL);
	if (0 != r) {
		printf("task 1: fail at task_waitforsigobjs(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = mutex_unlock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<SIGOBJCOUNT; i++) {
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			if (0 != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			break;
		case 4:
			if (0 != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			for (j=0; j<UBINOS__UBIK_TEST__MSGQSIZE; j++) {
				if ((UBINOS__UBIK_TEST__MSGQSIZE - j) != msg[j]) {
					printf("task 1: received message is wrong\r\n");
					_g_ubik_test_result = -1;
					goto end0;
				}
			}
			break;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 unlocks mutex\r\n");
	r = mutex_unlock(_g_ubik_test_mutex);
	if (0 != r) {
		printf("task 1: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	printf("task 1 tries to sleep (for %d ms)\r\n", ubik_ticktotimems(waittick));
	task_sleep(waittick);
	printf("\r\n");
	printf("task 1 wakes up\r\n");

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 1 waits for multiple signals with all option and timeout (for %d ms)\r\n", ubik_ticktotimems(waittick * 2));

	r = mutex_lock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = task_waitforsigobjs_timed(sigobj_a, sigtype_a, param_a, SIGOBJCOUNT, TASK_WAITOPT__ALL, waittick * 2);
	if (UBIK_ERR__TIMEOUT != r) {
		printf("task 1: fail at task_waitforsigobjs(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = mutex_unlock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 1: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	printf("\r\n");
	printf("task 1 wakes up\r\n");

	for (i=0; i<SIGOBJCOUNT; i++) {
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 4:
			if (UBIK_ERR__TIMEOUT != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			break;
		case 3:
			if (0 != sigtype_a[i]) {
				printf("task 1: sigtype_a[%d] value is wrong\r\n", i);
				_g_ubik_test_result = -1;
				goto end0;
			}
			break;
		}
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 1; i++) {
		_g_ubik_test_count1++;
		printf("1");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

end0:
	printf("task 1 ends\r\n");
}

static void tasktest07_task2func(void * arg) {
	int r;
	int i;
	unsigned int waitvalue = UBINOS__UBIK_TEST__TASKWAITTIMEMS * bsp_getbusywaitcountperms();
	unsigned char msg[UBINOS__UBIK_TEST__MSGQSIZE];

	printf("task 2 locks mutex\r\n");
	r = mutex_lock(_g_ubik_test_mutex);
	if (0 != r) {
		printf("task 2: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 2; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 2 sends one signal\r\n");
	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		msg[i] = i;
	}
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

	printf("task 2 sends one signal\r\n");
	for (i=0; i<UBINOS__UBIK_TEST__MSGQSIZE; i++) {
		msg[i] = UBINOS__UBIK_TEST__MSGQSIZE - i;
	}
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

	printf("task 2 sends all other signals\r\n");

	r = mutex_unlock(_g_ubik_test_mutex);
	if (0 != r) {
		printf("task 2: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = signal_send(_g_ubik_test_signal, 0);
	if (0 != r) {
		printf("task 2: fail at signal_send(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = mutex_lock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 2: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = condv_signal(_g_ubik_test_condv);
	if (0 != r) {
		printf("task 2: fail at condv_signal(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = mutex_unlock(_g_ubik_test_mutex2);
	if (0 != r) {
		printf("task 2: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	r = sem_give(_g_ubik_test_sem);
	if (0 != r) {
		printf("task 2: fail at sem_give(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	printf("task 2 locks mutex\r\n");
	r = mutex_lock(_g_ubik_test_mutex);
	if (0 != r) {
		printf("task 2: fail at mutex_lock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 2; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 2 sends one signal\r\n");
	r = sem_give(_g_ubik_test_sem);
	if (0 != r) {
		printf("task 2: fail at sem_give(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

	for (i=0; i<UBINOS__UBIK_TEST__TASKLOOPCOUNT * 2; i++) {
		_g_ubik_test_count2++;
		printf("2");
		bsp_busywait(waitvalue);
	}
	printf("\r\n");

	printf("task 2 unlocks mutex\r\n");
	r = mutex_unlock(_g_ubik_test_mutex);
	if (0 != r) {
		printf("task 2: fail at mutex_unlock(), err=%d\r\n", r);
		_g_ubik_test_result = -1;
		goto end0;
	}

end0:
	printf("task 2 ends\r\n");
}

int ubik_test_tasktest07(void) {
	int r;
	int r2;
	unsigned int count1;
	unsigned int count2;
	unsigned int sleepvalue = ubik_timemstotick(UBINOS__UBIK_TEST__TASKWAITTIMEMS) * UBINOS__UBIK_TEST__TASKLOOPCOUNT / 3;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_tasktest07</name>\r\n");
	printf("<description>Test on wait for multiple signal objects function of task</description>\n\r");

	printf("<message>\n\r");

	_g_ubik_test_result = 0;

	_g_ubik_test_count1 = 0;
	_g_ubik_test_count2 = 0;

	_g_ubik_test_task_a[0] = NULL;
	_g_ubik_test_task_a[1] = NULL;

	_g_ubik_test_mutex	= NULL;
	_g_ubik_test_mutex2	= NULL;
	_g_ubik_test_signal	= NULL;
	_g_ubik_test_condv	= NULL;
	_g_ubik_test_sem	= NULL;
	_g_ubik_test_msgq	= NULL;

	r = mutex_create(&_g_ubik_test_mutex);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = mutex_create(&_g_ubik_test_mutex2);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = signal_create(&_g_ubik_test_signal);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = condv_create(&_g_ubik_test_condv);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = sem_create(&_g_ubik_test_sem);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = msgq_create(&_g_ubik_test_msgq, UBINOS__UBIK_TEST__MSGQSIZE, UBINOS__UBIK_TEST__MSGQMAXCOUNT);
	if (0 != r) {
		printf("fail at mutex_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	printf("create task 2\r\n");
	r = task_create(&_g_ubik_test_task_a[2-1], tasktest07_task2func, NULL, task_getpriority(NULL)-2, 256, "tasktest07 task 2");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	task_sleep(sleepvalue);

	count1 = _g_ubik_test_count1;
	count2 = _g_ubik_test_count2;
	printf("\r\n");
	printf("checking\r\n");
	task_sleep(sleepvalue);
	printf("\r\n");
	printf("check point 01: ");
	if (count1 != _g_ubik_test_count1 || count2 == _g_ubik_test_count2) {
		printf("fail\r\n");
		r = -1;
		goto end2;
	}
	printf("pass\r\n");

	task_sleep(sleepvalue);

	printf("\r\n");
	printf("create task 1\r\n");
	r = task_create(&_g_ubik_test_task_a[1-1], tasktest07_task1func, NULL, task_getpriority(NULL)-1, 256, "tasktest07 task 1");
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
	printf("check point 02: ");
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
	printf("check point 03: ");
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
	printf("check point 04: ");
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
	printf("check point 12: ");
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
	printf("check point 13: ");
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
	if (NULL != _g_ubik_test_mutex) {
		r2 = mutex_delete(&_g_ubik_test_mutex);
		if (0 != r2) {
			printf("fail at mutex_delete(), err=%d\r\n", r2);
			r = -1;
		}
	}
	if (NULL != _g_ubik_test_mutex2) {
		r2 = mutex_delete(&_g_ubik_test_mutex2);
		if (0 != r2) {
			printf("fail at mutex_delete(), err=%d\r\n", r2);
			r = -1;
		}
	}
	if (NULL != _g_ubik_test_signal) {
		r2 = signal_delete(&_g_ubik_test_signal);
		if (0 != r2) {
			printf("fail at signal_delete(), err=%d\r\n", r2);
			r = -1;
		}
	}
	if (NULL != _g_ubik_test_condv) {
		r2 = condv_delete(&_g_ubik_test_condv);
		if (0 != r2) {
			printf("fail at condv_delete(), err=%d\r\n", r2);
			r = -1;
		}
	}
	if (NULL != _g_ubik_test_sem) {
		r2 = sem_delete(&_g_ubik_test_sem);
		if (0 != r2) {
			printf("fail at sem_delete(), err=%d\r\n", r2);
			r = -1;
		}
	}
	if (NULL != _g_ubik_test_msgq) {
		r2 = msgq_delete(&_g_ubik_test_msgq);
		if (0 != r2) {
			printf("fail at msgq_delete(), err=%d\r\n", r2);
			r = -1;
		}
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

#endif /* ( !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET3 == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) &&
	      !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) ) */
