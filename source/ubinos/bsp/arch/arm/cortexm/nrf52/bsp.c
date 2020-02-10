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
#if (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA)

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
    unsigned int tmp;
    unsigned int tmp2;
    unsigned char * tmp_p;

    if (NULL == buf) {
        return -2;
    }
    if (8 > max) {
        return -3;
    }

    tmp = (unsigned int) ((NRF_FICR->INFO.PART >> FICR_INFO_PART_PART_Pos) & FICR_INFO_PART_PART_Msk);
    tmp2 = (unsigned int) ((NRF_FICR->INFO.VARIANT >> FICR_INFO_VARIANT_VARIANT_Pos) & FICR_INFO_VARIANT_VARIANT_Msk);

#if (UBINOS__BSP__CPU_ENDIAN__BIG == UBINOS__BSP__CPU_ENDIAN)
    tmp_p = (unsigned char *) &tmp;
    buf[0] = tmp_p[0];
    buf[1] = tmp_p[1];
    buf[2] = tmp_p[2];
    buf[3] = tmp_p[3];
    tmp_p = (unsigned char *) &tmp2;
    buf[4] = tmp_p[4];
    buf[5] = tmp_p[5];
    buf[6] = tmp_p[6];
    buf[7] = tmp_p[7];
#else
    tmp_p = (unsigned char *) &tmp;
    buf[0] = tmp_p[7];
    buf[1] = tmp_p[6];
    buf[2] = tmp_p[5];
    buf[3] = tmp_p[4];
    tmp_p = (unsigned char *) &tmp2;
    buf[4] = tmp_p[3];
    buf[5] = tmp_p[2];
    buf[6] = tmp_p[1];
    buf[7] = tmp_p[0];
#endif

    return 4;
}

#endif /* (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

