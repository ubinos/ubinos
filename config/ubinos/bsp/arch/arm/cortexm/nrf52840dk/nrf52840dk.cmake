#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__CPU_MODEL                                                 "NRF52840XXAA"  STRING)

set_cache(UBINOS__BSP__BOARD_MODEL                                               "NRF52840DK"    STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN                                   0x00000000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH                                   0x00100000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN                                     0x20000000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH                                     0x00040000     STRING)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/gdb_flash_load.gdb"        PATH)

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/t32_flash_load.cmm"        PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET                                       "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/t32_flash_reset.cmm"       PATH)

include(${CMAKE_CURRENT_LIST_DIR}/../nrf52dk.cmake)
