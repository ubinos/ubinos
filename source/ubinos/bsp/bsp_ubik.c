/*
 Copyright (C) 2009 Sung Ho Park
 Contact: ubinos.org@gmail.com

 This file is part of the bsp_sam... component of the Ubinos.

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

#include <ubinos/bsp.h>

#if (INCLUDE__UBINOS__BSP == 1)

#include <ubinos/bsp_ubik.h>
#if (INCLUDE__UBINOS__UBIK == 1)
#include <ubinos/ubik.h>
#endif

void bsp_ubik_entercrit(void) {
#if (INCLUDE__UBINOS__UBIK == 1)
    ubik_entercrit();
#endif
}

void bsp_ubik_exitcrit(void) {
#if (INCLUDE__UBINOS__UBIK == 1)
    ubik_exitcrit();
#endif
}

int bsp_mutex_create(bsp_mutex_pt * bsp_mutex_p) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return mutex_create((mutex_pt *) bsp_mutex_p);
#else
    return 0;
#endif
}

int bsp_mutex_delete(bsp_mutex_pt * bsp_mutex_p) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return mutex_delete((mutex_pt *) bsp_mutex_p);
#else
    return 0;
#endif
}

int bsp_mutex_lock(bsp_mutex_pt bsp_mutex) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return mutex_lock((mutex_pt) bsp_mutex);
#else
    return 0;
#endif
}

int bsp_mutex_lock_timed(bsp_mutex_pt bsp_mutex, unsigned int tick) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return mutex_lock_timed((mutex_pt) bsp_mutex, tick);
#else
    return 0;
#endif
}

int bsp_mutex_unlock(bsp_mutex_pt bsp_mutex) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return mutex_unlock((mutex_pt) bsp_mutex);
#else
    return 0;
#endif
}

void * bsp_task_getcur() {
#if (INCLUDE__UBINOS__UBIK == 1)
    return task_getcur();
#else
    return 0;
#endif
}

int bsp_task_sleepms(unsigned int timems) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return task_sleepms(timems);

#else
    bsp_busywait(bsp_timemstobwc(timems));
    return 0;
#endif
}

int bsp_ubik_isrt(void) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return ubik_isrt();
#else
    return bsp_isintr();
#endif
}

int bsp_ubik_iscrit(void) {
#if (INCLUDE__UBINOS__UBIK == 1)
    return ubik_iscrit();
#else
    return bsp_isintr();
#endif
}

void bsp_ubik_task_schedule_irq(void) {
#if (INCLUDE__UBINOS__UBIK == 1)
    extern void _ubik_task_schedule_irq();
    _ubik_task_schedule_irq();
#else
    dtty_puts("\r\n\r\bsp_ubik_task_schedule_irq\r\n\r\n", 80);
    bsp_abortsystem();
#endif
}

void bsp_ubik_tickisr() {
#if (INCLUDE__UBINOS__UBIK == 1)
    extern void _ubik_tickisr(void);
    _ubik_tickisr();
#else
    dtty_puts("\r\n\r\bsp_ubik_tickisr\r\n\r\n", 80);
    bsp_abortsystem();
#endif
}

void bsp_ubik_swisr(unsigned int swino) {
#if (INCLUDE__UBINOS__UBIK == 1)
    extern void _ubik_swisr(unsigned int swino);
    _ubik_swisr(swino);
#else
    dtty_puts("\r\n\r\bsp_ubik_swisr\r\n\r\n", 80);
    bsp_abortsystem();
#endif
}

#endif /* (INCLUDE__UBINOS__BSP == 1) */

