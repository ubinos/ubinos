/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam7x256ek component of the Ubinos.

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

#include "../_bsp.h"

#if (INCLUDE__UBINOS__BSP == 1)
#if (UBINOS__BSP__CPU_MODEL__STM32F7XX == 1)

int bsp_getcpuclockfreq(unsigned int * freq_p) {
    if (NULL == freq_p) {
        return -2;
    }

    return -1;
}

int bsp_getcpuclockfreqk(unsigned int * freqk_p) {
    if (NULL == freqk_p) {
        return -2;
    }

    *freqk_p = UBINOS__BSP__CLOCK_FREQ_MAIN;

    return 0;
}

int bsp_getmckfreq(unsigned int * freq_p) {
    return bsp_getcpuclockfreq(freq_p);
}

int bsp_getmckfreqk(unsigned int * freqk_p) {
    return bsp_getcpuclockfreqk(freqk_p);
}

int bsp_getcpuidsize(void) {
    return 8;
}

int bsp_getcpuid(unsigned char * buf, int max) {
    return 4;
}

#endif /* (UBINOS__BSP__CPU_MODEL__STM32F7XX == 1) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

