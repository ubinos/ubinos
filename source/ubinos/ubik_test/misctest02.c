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

#if !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1)

#include <stdio.h>
#include <stdlib.h>

int ubik_test_misctest02(void) {
	int r;
	tickcount_t tickcount1;
	tickcount_t tickcount2;
	unsigned int waitvalue;
	unsigned int rtick;
	unsigned int itick;
	unsigned int rloopcount;
	unsigned int iloopcount;
	unsigned int errorrate;

	printf("\r\n");
	printf("<test>\r\n");
	printf("<name>ubik_test_misctest02</name>\r\n");
	printf("<description>Test for accuracy of UBINOS__BSP__BUSYWAITCOUNT_PER_MS</description>\n\r");

	printf("<message>\n\r");

	printf("it tasks %d ms\r\n", UBINOS__UBIK_TEST__BUSYWAITCOUNTTESTTIMEMS);

	waitvalue = bsp_getbusywaitcountperms() * UBINOS__UBIK_TEST__BUSYWAITCOUNTTESTTIMEMS;
	tickcount1 = ubik_gettickcount();
	bsp_busywait(waitvalue);
	tickcount2 = ubik_gettickcount();
	tickcount1 = ubik_gettickdiff(tickcount1, tickcount2);

	rtick = tickcount1.low;
	itick = ubik_gettickpersec() * UBINOS__UBIK_TEST__BUSYWAITCOUNTTESTTIMEMS / 1000;
	rloopcount = bsp_getbusywaitcountperms();
	iloopcount = rloopcount * itick / rtick;

	printf("current value is %d\r\n", rloopcount);
	printf("recommended value is %d\r\n", iloopcount);

	if (rtick >= itick) {
		errorrate = (rtick - itick) * 100 / itick;
	}
	else {
		errorrate = (itick - rtick) * 100 / itick;
	}
	printf("accuracy is %d percent\r\n", 100 - errorrate);

	if (errorrate <= 1) {
		r = 0;
	}
	else {
		r = -1;
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

#endif /* !( UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET == 1) */
