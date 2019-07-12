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

#include <stdio.h>
#include <stdlib.h>

/****************************************************************************/

volatile unsigned int	_g_ubik_test_result		= 0;

volatile unsigned int	_g_ubik_test_count1		= 0;
volatile unsigned int	_g_ubik_test_count2		= 0;
volatile unsigned int	_g_ubik_test_count3		= 0;
volatile unsigned int	_g_ubik_test_count4		= 0;

mutex_pt				_g_ubik_test_mutex		= NULL;
mutex_pt				_g_ubik_test_mutex2		= NULL;
signal_pt				_g_ubik_test_signal		= NULL;
condv_pt				_g_ubik_test_condv		= NULL;
sem_pt					_g_ubik_test_sem		= NULL;
msgq_pt					_g_ubik_test_msgq		= NULL;
stimer_pt				_g_ubik_test_stimer		= NULL;
char *					_g_ubik_test_msgbuf		= NULL;

task_pt					_g_ubik_test_task_a[4]	= {NULL, NULL, NULL, NULL};

/****************************************************************************/

int ubik_test_testall(void) {
	int r;
	int testcount = 0;
	int failcount = 0;
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	int r2;
	unsigned int size_old;
	unsigned int count_old;
	unsigned int size;
	unsigned int count;
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	printf("\r\n");
	printf("<testset>\r\n");
	printf("<name>ubik_test</name>\r\n");
	printf("<description>Ubinos Kernel Test</description>\n\r");
	printf("\r\n");

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	ubik_collectgarbage();

	r = heap_getallocatedsize(NULL, &size_old);
	if (0 != r) {
		printf("<message>\n\r");
		printf("fail at heap_getallocatedsize\r\n");
		printf("</message>\n\r");
		r = -1;
		goto end0;
	}

	r = heap_getallocatedcount(NULL, &count_old);
	if (0 != r) {
		printf("<message>\n\r");
		printf("fail at heap_getallocatedcount\r\n");
		printf("</message>\n\r");
		r = -1;
		goto end0;
	}
#endif /* !(UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */


#if !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_misctest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_misctest02();
	if (0 != r) {
		failcount++;
		goto end1;
	}
	ubik_collectgarbage();
#endif /* !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1) */

#if !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET2 == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest05();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest06();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET2 == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_mutextest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_mutextest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_mutextest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_mutextest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_signaltest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_signaltest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_signaltest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_signaltest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_condvtest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_condvtest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_condvtest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_condvtest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_semtest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_semtest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_semtest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_semtest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_msgqtest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_msgqtest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_msgqtest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_msgqtest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) */

#if (1 != UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_stimertest01();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_stimertest02();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_stimertest03();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_stimertest04();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* (1 != UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET) */


#if !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET3 == 1)
	#if ( !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) && \
		  !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1))
	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest07();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
	#endif /* ( !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET == 1) &&
			  !(UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET == 1) && !(UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET == 1) ) */

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest08();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();

	printf("<!-- ====================================================================== -->\r\n");
	testcount++;
	r = ubik_test_tasktest09();
	if (0 != r) {
		failcount++;
	}
	ubik_collectgarbage();
#endif /* !(UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET3 == 1) */


	printf("<!-- ====================================================================== -->\r\n");

#if !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1)
end1:
#endif /* !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1) */
	if (0 == failcount) {
		r = 0;
	}
	else {
		r = -1;
	}

	printf("\r\n");
	printf("<message>\n\r");

	printf("test: %d\r\n", testcount);
	printf("pass: %d\r\n", testcount - failcount);
	printf("fail: %d\r\n", failcount);

	printf("</message>\n\r");
	printf("\r\n");

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	if (0 == r) {
		ubik_collectgarbage();

		r2 = heap_getallocatedsize(NULL, &size);
		if (0 != r2) {
			printf("fail at heap_getallocatedsize\r\n");
			r = -1;
			goto end0;
		}

		r2 = heap_getallocatedcount(NULL, &count);
		if (0 != r2) {
			printf("fail at heap_getallocatedcount\r\n");
			r = -1;
			goto end0;
		}

		if (size_old != size || count_old != count) {
			printf("memory leak was detected\r\n");
			r = -1;
			goto end0;
		}
	}

end0:
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
	printf("<result>");
	if (0 == r) {
		printf("pass");
	}
	else {
		printf("fail");
	}
	printf("</result>\r\n");
	printf("</testset>\r\n");
	printf("\r\n");

	return r;
}
