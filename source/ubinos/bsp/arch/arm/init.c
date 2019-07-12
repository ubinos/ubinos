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
#if (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM)

#if (INCLUDE__UBINOS__UBICLIB == 1)
#include <ubinos/ubiclib.h>
#endif
#if (INCLUDE__UBINOS__UBIK == 1)
#include <ubinos/ubik.h>
#endif

int main(void) {
    unsigned char * buf_p;
    unsigned int heapaddr;
    unsigned int heapsize;
    int r = 0;

    (void) buf_p;
    (void) heapaddr;
    (void) heapsize;
    (void) r;

    r = bsp_comp_init();
    if (0 != r) {
        dtty_puts("bsp_comp_init : fail\r\n", 80);
        bsp_abortsystem();
    }

#if (INCLUDE__UBINOS__UBICLIB == 1)
    r = ubiclib_comp_init();
    if (0 != r) {
        dtty_puts("ubiclib_comp_init : fail\r\n", 80);
        bsp_abortsystem();
    }

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
    extern char   end;           /* Set by linker.  */
    extern char   __stack_limit; /* Set by linker.  */
    heapaddr = (unsigned int) &end;
    heapsize = ((unsigned int) &__stack_limit) - heapaddr;
    r = ubiclib_heap_comp_init(heapaddr, heapsize);
    if (HEAP_ERR__UNSUPPORTED == r) {
        dtty_puts("heap_comp_init : unsupported\r\n", 80);
    }
    else if (0 != r) {
        dtty_puts("heap_comp_init : fail\r\n", 80);
        bsp_abortsystem();
    }
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

#if !(UBINOS__UBICLIB__NOSTDLIB == 1)
    r = stdlib_port_comp_init();
    if (0 != r) {
        dtty_puts("stdlib_port_comp_init : fail\r\n", 80);
        bsp_abortsystem();
    }
#endif

#if (INCLUDE__UBINOS__UBIK == 1)
    r = ubik_comp_init(UBINOS__UBIK__IDLETASK_STACK_DEPTH);
    if (0 != r) {
        dtty_puts("ubik_comp_init : fail\r\n", 80);
        bsp_abortsystem();
    }
#endif

#if (INCLUDE__UBINOS__UBICLIB == 1)
    r = ubiclib_comp_init_reent();
    if (0 != r) {
        dtty_puts("ubiclib_comp_init_reent : fail\r\n", 80);
        bsp_abortsystem();
    }

#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
    r = ubiclib_heap_comp_init_reent();
    if (HEAP_ERR__UNSUPPORTED == r) {
        dtty_puts("heap_comp_init_reent : unsupported\r\n", 80);
    }
    else if (0 != r) {
        dtty_puts("heap_comp_init_reent : fail\r\n", 80);
        bsp_abortsystem();
    }
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */
#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */

#if !(UBINOS__UBICLIB__NOSTDLIB == 1)
    r = stdlib_port_comp_init_reent();
    if (0 != r) {
        dtty_puts("stdlib_port_init_reent : fail\r\n", 80);
        bsp_abortsystem();
    }
#endif

    appmain(0, 0x0);

    for (;;) {
    }

    return 0;
}

#endif /* (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM) */
#endif /* (INCLUDE__UBINOS__BSP == 1) */

