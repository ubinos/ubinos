#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__CPU_TYPE "ARM926EJ_S" STRING)
set_cache(UBINOS__BSP__CPU_ARMTHUMBSTATE "ARM" STRING)
set_cache(UBINOS__BSP__CPU_MODEL "SAM9XE512" STRING)

set_cache(UBINOS__BSP__BOARD_MODEL "SAM9XE512EK" STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_TYPE "FLASH" STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN  0x00200000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH  0x00080000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN    0x00300000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH    0x00008000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN 0x10000000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH 0x00800000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN   0x20000000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH   0x04000000 STRING)

set_cache(UBINOS__BSP__USE_ICACHE TRUE BOOL)

set_cache(UBINOS__BSP__USE_EXTSDRAM TRUE BOOL)
set_cache(UBINOS__BSP__USE_EXTNORFLASH TRUE BOOL)

set_cache(UBINOS__BSP__CLOCK_FREQ_MAIN 18432 STRING)
set_cache(UBINOS__BSP__CLOCK_FREQ_SLOW 32 STRING)
set_cache(UBINOS__BSP__BUSYWAITCOUNT_PER_MS 49110 STRING)

set_cache(UBINOS__BSP__EXTSDRAM_BUSWIDTH 32 STRING)
set_cache(UBINOS__BSP__EXTNORFLASH_BUSWIDTH 16 STRING)
set_cache(UBINOS__BSP__EXTNORFLASH_ADDR 0x10000000 STRING)

set_cache(UBINOS__BSP__STACK_SIZE 0x20000 STRING)

set_cache(UBINOS__BSP__LINKSCRIPT_FILE "${PROJECT_UBINOS_DIR}/source/ubinos/bsp/arch/arm/classic/sam9xe/512/flash.ld" PATH)

set_cache(UBINOS__BSP__FLASH_WRITER_FILE "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/flash_writer.elf" PATH)
set_cache(UBINOS__BSP__SYS_INIT_FILE "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/sys_init.elf" PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/gdb_flash_load.gdb" PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/gdb_flash_reset.gdb" PATH)

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/t32_flash_load.cmm" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/classic/sam9xexxxek/t32_flash_reset.cmm" PATH)

# maximum size = 64 MiB
set_cache(UBINOS__UBICLIB__HEAP_DIR0_ALGORITHM "GROUP" STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_LOCKTYPE "MUTEX" STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_M 64 STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLCOUNT 12290 STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLBM_BUFSIZE 1596 STRING)

include(${CMAKE_CURRENT_LIST_DIR}/../../arm.cmake)

