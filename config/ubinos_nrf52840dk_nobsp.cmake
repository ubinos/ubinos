#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubinos", "build_type": "cmake_ubinos"}

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

