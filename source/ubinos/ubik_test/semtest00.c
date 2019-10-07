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

#if !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

#define TASKWORKINGTIMEMS   500
#define TASKLOOPCOUNT		10

static sem_pt 	_g_sem		= NULL;

static void semtest00_task1func(void * arg) {
	unsigned int i;

	for (i=0; i<TASKLOOPCOUNT; i++) {
		bsp_busywait((unsigned int) rand() % TASKWORKINGTIMEMS * bsp_getbusywaitcountperms());
		printf("task 1 produces one\r\n");

		sem_give(_g_sem);
	}
}

static void semtest00_task2func(void * arg) {
	unsigned int i;

	for (i=0; i<TASKLOOPCOUNT/2; i++) {
		printf("task 2 waits\r\n");
		sem_take(_g_sem);

		printf("task 2 consumes one\r\n");
		bsp_busywait((unsigned int) rand() % TASKWORKINGTIMEMS * bsp_getbusywaitcountperms());
	}
}

static void semtest00_task3func(void * arg) {
	unsigned int i;

	for (i=0; i<TASKLOOPCOUNT/2; i++) {
		printf("task 3 waits\r\n");
		sem_take(_g_sem);

		printf("task 3 consumes one\r\n");
		bsp_busywait((unsigned int) rand() % TASKWORKINGTIMEMS * bsp_getbusywaitcountperms());
	}
}

int ubik_test_semtest00(void) {
	int r;
	int r2;
	task_pt task_a[3];

	r = sem_create(&_g_sem);
	if (0 != r) {
		printf("fail at sem_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = task_create(&task_a[0], semtest00_task1func, NULL, task_getpriority(NULL)-1, 0, "task 1");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	r = task_create(&task_a[1], semtest00_task2func, NULL, task_getpriority(NULL)-1, 0, "task 2");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	task_sleep(10);

	r = task_create(&task_a[2], semtest00_task3func, NULL, task_getpriority(NULL)-1, 0, "task 3");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	r = 0;

end2:
	r2 = task_join(task_a, NULL, 3);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

end1:
	r2 = sem_delete(&_g_sem);
	if (0 != r2) {
		printf("fail at sem_delete(), err=%d\r\n", r2);
		r = -1;
	}

end0:
	return r;
}

#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) */