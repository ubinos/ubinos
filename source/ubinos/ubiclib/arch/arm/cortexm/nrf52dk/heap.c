/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../_heap.h"

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1)
#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1)

#include <ubinos/bsp/arch.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#undef LOGM_CATEGORY
#define LOGM_CATEGORY LOGM_CATEGORY__HEAP

#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DONGLE) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__ARDUINONANO33BLE)

typedef struct _mem_layout_region {
    unsigned int addr;
    uint8_t number;
    uint32_t control_bit;
} mem_layout_region;

#define MEM_LAYOUT_REGION_COUNT 22

const mem_layout_region _mem_layout[MEM_LAYOUT_REGION_COUNT + 1] = {
    {0x20000000, 0, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, //  0
    {0x20001000, 0, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, //  1
    {0x20002000, 1, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, //  2
    {0x20003000, 1, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, //  3
    {0x20004000, 2, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, //  4
    {0x20005000, 2, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, //  5
    {0x20006000, 3, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, //  6
    {0x20007000, 3, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, //  7
    {0x20008000, 4, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, //  8
    {0x20009000, 4, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, //  9
    {0x2000A000, 5, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, // 10
    {0x2000B000, 5, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, // 11
    {0x2000C000, 6, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, // 12
    {0x2000D000, 6, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, // 13
    {0x2000E000, 7, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, // 14
    {0x2000F000, 7, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, // 15
    {0x20010000, 8, (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)}, // 16
    {0x20018000, 8, (POWER_RAM_POWER_S1POWER_On << POWER_RAM_POWER_S1POWER_Pos)}, // 17
    {0x20020000, 8, (POWER_RAM_POWER_S2POWER_On << POWER_RAM_POWER_S2POWER_Pos)}, // 18
    {0x20028000, 8, (POWER_RAM_POWER_S3POWER_On << POWER_RAM_POWER_S3POWER_Pos)}, // 19
    {0x20030000, 8, (POWER_RAM_POWER_S4POWER_On << POWER_RAM_POWER_S4POWER_Pos)}, // 20
    {0x20038000, 8, (POWER_RAM_POWER_S5POWER_On << POWER_RAM_POWER_S5POWER_Pos)}, // 21
    {0x20040000, 0, 0}, // end address
};

uint8_t _mem_layout_region_on[MEM_LAYOUT_REGION_COUNT] = {
    0, //  0
    0, //  1
    0, //  2
    0, //  3
    0, //  4
    0, //  5
    0, //  6
    0, //  7
    0, //  8
    0, //  9
    0, // 10
    0, // 11
    0, // 12
    0, // 13
    0, // 14
    0, // 15
    0, // 16
    0, // 17
    0, // 18
    0, // 19
    0, // 20
    0, // 21
};

#if (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1))

_heap_block_t _mem_layout_block_infos[UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX];

#endif /* (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)) */

int _heap_power_off_unused_area(_heap_pt heap, unsigned int nomal_resign_end, unsigned int reverse_resign_addr) {
    int r = 0;
    int ni, ri;

    if (NULL == heap) {
        heap = _ubiclib_heap;
    }
    if (NULL == heap) {
        logme("heap is NULL");
        bsp_abortsystem();
    }

    assert(nomal_resign_end <= reverse_resign_addr);

    logmfd("nomal_resign_end = 0x%08x,  reverse_resign_addr = 0x%08x", nomal_resign_end, reverse_resign_addr);

    for (int i = 0; i < MEM_LAYOUT_REGION_COUNT; i++) {
        if (heap->addr > _mem_layout[i].addr)
        {
            _mem_layout_region_on[i] = 1;
        }
        else
        {
            _mem_layout_region_on[i] = 0;
        }
    }

    if (heap->region_dir_on[0])
    {
        for (ni = 0; ni < MEM_LAYOUT_REGION_COUNT; ni++) {
            if (nomal_resign_end <= _mem_layout[ni].addr) {
                break;
            }
            _mem_layout_region_on[ni] = 1;
        }
    }

    if (heap->region_dir_on[1])
    {
        for (ri = MEM_LAYOUT_REGION_COUNT - 1; ri >= 0; ri--) {
            if (_mem_layout[ri + 1].addr <= reverse_resign_addr) {
                break;
            }
            _mem_layout_region_on[ri] = 1;
        }
    }

    for (int i = 0; i < MEM_LAYOUT_REGION_COUNT; i++) {
        logmfd("index = %d,  on = %d", i, _mem_layout_region_on[i]);

        if (_mem_layout_region_on[i]) {
            NRF_POWER->RAM[_mem_layout[i].number].POWERSET = _mem_layout[i].control_bit;
        }
        else {
            NRF_POWER->RAM[_mem_layout[i].number].POWERCLR = _mem_layout[i].control_bit;
        }
    }

    r = 0;

    return r;
}

int _heap_print_power_infos(_heap_pt heap) {
    int r = 0;

    if (NULL == heap) {
        heap = _ubiclib_heap;
    }
    if (NULL == heap) {
        logme("heap is NULL");
        bsp_abortsystem();
    }

#if !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)
    printf("(%d, %d) ", heap->region_dir_on[0], heap->region_dir_on[1]);
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1) */

    for (int i = 0; i < MEM_LAYOUT_REGION_COUNT; i++) {
        printf(" %d", _mem_layout_region_on[i]);
    }

    return r;
}

int _heap_save_block_infos(_heap_pt heap, int dir)
{
#if (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1))
    int r = 0;

    if (NULL == heap) {
        heap = _ubiclib_heap;
    }
    if (NULL == heap) {
        logme("heap is NULL");
        bsp_abortsystem();
    }

    if (0 != dir && 1 != dir) {
        logme("dir is wrong");
        bsp_abortsystem();
    }

    unsigned int idx;
    _heap_region_pt region;
    _heap_block_pt bx = 0;
    edlist_pt fbl;

    idx = 0;

    region = &heap->region[dir];

    bx = _heap_blocklist_head(&(region->abl));
    while(bx != NULL) {
        _mem_layout_block_infos[idx++] = *bx;
        if (idx >= UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX)
        {
            logmfe("block count is larger than HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX");
            bsp_abortsystem();
        }
        bx = _heap_blocklist_next(bx);
    }

    for (unsigned int i = 0; i < region->fblcount; i++) {
        fbl = &region->fbl_ap[i];
        if (fbl->count != 0) {
            bx = _heap_blocklist_head(fbl);
            while(bx != NULL) {
                _mem_layout_block_infos[idx++] = *bx;
                if (idx >= UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX)
                {
                    logmfe("block count is larger than HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX");
                    bsp_abortsystem();
                }
                bx = _heap_blocklist_next(bx);
            }
        }
    }

    return r;
#else /* (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)) */
    return -1;
#endif /* (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)) */
}

int _heap_restore_block_infos(_heap_pt heap, int dir)
{
#if (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1))
    int r = 0;

    if (NULL == heap) {
        heap = _ubiclib_heap;
    }
    if (NULL == heap) {
        logme("heap is NULL");
        bsp_abortsystem();
    }

    if (0 != dir && 1 != dir) {
        logme("dir is wrong");
        bsp_abortsystem();
    }

    unsigned int idx;
    _heap_region_pt region;
    _heap_block_pt bx = 0;
    edlist_pt fbl;
    unsigned int log2m/*, m, maskm, min*/;

    idx = 0;

    region = &heap->region[dir];
    log2m = region->log2m;

    bx = _heap_blocklist_head(&(region->abl));
    while(bx != NULL) {
        *bx = _mem_layout_block_infos[idx++];
        _block_set_tag(bx, bx->tag, log2m);
        if (idx >= UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX)
        {
            logmfe("block count is larger than HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX");
            bsp_abortsystem();
        }
        bx = _heap_blocklist_next(bx);
    }

    for (unsigned int i = 0; i < region->fblcount; i++) {
        fbl = &region->fbl_ap[i];
        if (fbl->count != 0) {
            bx = _heap_blocklist_head(fbl);
            while(bx != NULL) {
                *bx = _mem_layout_block_infos[idx++];
                _block_set_tag(bx, bx->tag, log2m);
                if (idx >= UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX)
                {
                    logmfe("block count is larger than HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX");
                    bsp_abortsystem();
                }
                bx = _heap_blocklist_next(bx);
            }
        }
    }

    return r;
#else /* (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)) */
    return -1;
#endif /* (!(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) && !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF == 1)) */
}

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DONGLE) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__ARDUINONANO33BLE) */

#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM == 1) */
#endif /* !(UBINOS__UBICLIB__EXCLUDE_HEAP == 1) */
