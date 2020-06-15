/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
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

extern void SystemInit2(void);

int main(void) {
    unsigned char * buf_p;
    unsigned int heapaddr;
    unsigned int heapsize;
    int r = 0;

    (void) buf_p;
    (void) heapaddr;
    (void) heapsize;
    (void) r;

    SystemInit2();

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

