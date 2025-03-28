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

set_cache(UBINOS__BSP__OPENOCD_CONFIG_FILE "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/rp2040/openocd.cfg" PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_load_openocd.gdb" PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_reset_openocd.gdb" PATH)

set_cache(UBINOS__BSP__DEBUG_SERVER_TYPE "OPENOCD" STRING)
set_cache(UBINOS__BSP__DEBUG_SERVER_COMMAND "openocd" STRING)


set_cache(UBINOS__BSP__BOARD_MODEL "NOBSP" STRING)
set_cache(UBINOS__BSP__CPU_MODEL "RP2040" STRING)


include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)

