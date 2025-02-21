#
# Copyright (c) 2025 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubinos", "build_type": "cmake_ubinos"}


set_cache(PROJECT_TOOLCHAIN_F_NO_UNWIND_TABLES FALSE BOOL)

set_cache(PROJECT_TOOLCHAIN_C_STD "NONE" STRING)

set_cache(PROJECT_TOOLCHAIN_CXX_STD "NONE" STRING)
set_cache(PROJECT_TOOLCHAIN_CXX_F_NO_RTTI FALSE BOOL)
set_cache(PROJECT_TOOLCHAIN_CXX_F_NO_EXCEPTIONS FALSE BOOL)
set_cache(PROJECT_TOOLCHAIN_CXX_F_NO_THREADSAFE_STATICS FALSE BOOL)
set_cache(PROJECT_TOOLCHAIN_CXX_W_NO_CXX14_COMPAT FALSE BOOL)

set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_PRESENT TRUE BOOL)
set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_NAME S140 STRING)
set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_BLE_API_VERSION 6 STRING)

set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_FILE "${PROJECT_LIBRARY_DIR}/Adafruit_nRF52_Arduino_wrapper/resource/lib/softdevice/s140_nrf52_6.1.1/s140_nrf52_6.1.1_softdevice.hex" PATH)
set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_INCLUDE_DIR "${PROJECT_LIBRARY_DIR}/Adafruit_nRF52_Arduino_wrapper/resource/lib/softdevice/s140_nrf52_6.1.1/s140_nrf52_6.1.1_API/include" PATH)

set_cache(UBINOS__BSP__NRF52_BOOTLOADER_FILE "${PROJECT_LIBRARY_DIR}/Adafruit_nRF52_Arduino_wrapper/resource/lib/bootloader/adafruitnrf52840e/nrf52_bootloader.hex" PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/gdb_flash_load_softdevice_bootloader.gdb" PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/gdb_flash_reset_softdevice.gdb" PATH)

set_cache(UBINOS__BSP__DEBUG_SERVER_TYPE "JLINK" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_COMMAND "JLinkGDBServer" STRING)


set_cache(UBINOS__BSP__BOARD_MODEL "NOBSP" STRING)
set_cache(UBINOS__BSP__CPU_MODEL "NRF52840XXAA" STRING)

set_cache(UBINOS__BSP__DEBUG_SERVER_HOST "" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_PORT "2331" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_TYPE "NONE" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_COMMAND "" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_SERIAL "" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_TARGET_INTERFACE "SWD" STRING)


include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)

