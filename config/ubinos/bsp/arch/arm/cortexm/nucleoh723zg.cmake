#
# Copyright (c) 2022 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__CPU_TYPE "CORTEX_M7" STRING)
set_cache(UBINOS__BSP__CPU_ARMTHUMBSTATE "THUMB" STRING)
set_cache(UBINOS__BSP__CPU_MODEL "STM32H723ZG" STRING)

set_cache(UBINOS__BSP__BOARD_MODEL "NUCLEOH723ZG" STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_TYPE "FLASH" STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN 0x08000000 STRING) # FLASH Bank 1 1024 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH 0x00100000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN   0x20000000 STRING) # DTCM 128 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH   0x00020000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN  0x00000000 STRING) # ITCM 64 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH  0x00010000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN  0x24000000 STRING) # AXI SRAM 128 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH  0x00020000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM4_ORIGIN  0x30000000 STRING) # SRAM 1 16 KB, SRAM 2 16 KB (32 KB)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM4_LENGTH  0x00008000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM5_ORIGIN  0x38000000 STRING) # SRAM 4 16 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM5_LENGTH  0x00004000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM6_ORIGIN  0x38800000 STRING) # Backup SRAM 4 KB
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM6_LENGTH  0x00001000 STRING)

set_cache(UBINOS__BSP__USE_ICACHE TRUE BOOL)
set_cache(UBINOS__BSP__USE_DCACHE TRUE BOOL)

set_cache(UBINOS__BSP__USE_RELOCATED_ISR_VECTOR TRUE BOOL)

set_cache(UBINOS__BSP__CLOCK_FREQ_MAIN 520000 STRING)
set_cache(UBINOS__BSP__CLOCK_FREQ_SLOW 32 STRING)
set_cache(UBINOS__BSP__BUSYWAITCOUNT_PER_MS 399681 STRING)

set_cache(UBINOS__BSP__STACK_SIZE 0x800 STRING)

set_cache(UBINOS__BSP__LINKSCRIPT_FILE "${PROJECT_UBINOS_DIR}/source/ubinos/bsp/arch/arm/cortexm/stm32h723/z/flash.ld" PATH)

# set_cache(UBINOS__BSP__FLASH_WRITER_FILE "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nucleoh723zg/stm32f76x.bin" PATH)

# C:\ST\STM32CubeIDE_1.17.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.openocd.win32_2.4.0.202409170845\tools\bin

set_cache(UBINOS__BSP__OPENOCD_CONFIG_FILE "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nucleoh723zg/openocd.cfg" PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_load_openocd.gdb" PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_reset_openocd.gdb" PATH)

# set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nucleoh723zg/t32_flash_load.cmm" PATH)
# set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nucleoh723zg/t32_flash_reset.cmm" PATH)

set_cache(UBINOS__BSP__DEBUG_SERVER_TYPE "OPENOCD" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_COMMAND "openocd" STRING)

# C:\ST\STM32CubeIDE_1.17.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.openocd.win32_2.4.0.202409170845\tools\bin\openocd.exe "-s" "C:/MyWorks/stm32cubeide/workspace_1.17.0/nucleoh723zg_helloworld" "-s" "C:/ST/STM32CubeIDE_1.17.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.debug.openocd_2.3.0.202411041438/resources/openocd/st_scripts" "-s" "C:/ST/STM32CubeIDE_1.17.0/STM32CubeIDE/plugins/com.st.stm32cube.ide.mpu.debug.opeocd_2.2.0.202409171044/resources/openocd/st_scripts" "-c" "gdb_report_data_abort enable" "-c" "gdb_port 2331" "-c" "tcl_port 2334" "-c" "telnet_port 2337" "-f" "C:/MyWorks/ubinos/ubiworks/output/hi_world_nucleoh723zg_baremetal/openocd.cfg" 

# maximum size = 128 KiB
set_cache(UBINOS__UBICLIB__HEAP_DIR0_ALGORITHM "GROUP" STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_LOCKTYPE "MUTEX" STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_M 8 STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLCOUNT 194 STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLBM_BUFSIZE 32 STRING)

include(${CMAKE_CURRENT_LIST_DIR}/../../arm.cmake)

