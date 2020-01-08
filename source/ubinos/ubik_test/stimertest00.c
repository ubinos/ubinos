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

#define TASKLOOPCOUNT		10
#define TASKLOOPINTERVALMS	1000

static stimer_pt 	_g_stimer		= NULL;
static sem_pt		_g_sem			= NULL;

static void stimertest00_taskfunc(void * arg) {
	unsigned int i;

	for (i=0; i<TASKLOOPCOUNT; i++) {
		sem_take(_g_sem);

		printf("hello world!\r\n");
		bsp_busywait((unsigned int) rand() % TASKLOOPINTERVALMS / 2 * bsp_getbusywaitcountperms());
	}
}

int ubik_test_stimertest00(void) {
	int r;
	int r2;
	task_pt task;

	r = semb_create(&_g_sem);
	if (0 != r) {
		printf("fail at semb_create(), err=%d\r\n", r);
		r = -1;
		goto end0;
	}

	r = stimer_create(&_g_stimer);
	if (0 != r) {
		printf("fail at stimer_create(), err=%d\r\n", r);
		r = -1;
		goto end1;
	}

	r = task_create(&task, stimertest00_taskfunc, NULL, task_getpriority(NULL)-1, 0, "stimertest00 task");
	if (0 != r) {
		printf("fail at task_create(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	r = stimer_set(_g_stimer, ubik_timemstotick(TASKLOOPINTERVALMS), _g_sem, 0);
	if (0 != r) {
		printf("fail at stimer_set(), err=%d\r\n", r);
		r = -1;
		goto end2;
	}

	r = stimer_start(_g_stimer);
	if (0 != r) {
		printf("fail at stimer_start(), err=%d\r\n", r);
		r = -1;
		goto end3;
	}

	r = 0;

end3:
	r2 = task_join(&task, NULL, 1);
	if (0 != r2) {
		printf("fail at task_join(), err=%d\r\n", r2);
		r = -1;
	}

	r2 = stimer_stop(_g_stimer);
	if (0 != r2) {
		printf("fail at stimer_stop(), err=%d\r\n", r2);
		r = -1;
	}

end2:
	r2 = stimer_delete(&_g_stimer);
	if (0 != r2) {
		printf("fail at stimer_delete(), err=%d\r\n", r2);
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

#endif /* (1 != UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET) */
