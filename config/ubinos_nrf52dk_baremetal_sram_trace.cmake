#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, lib]}

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_sram_load_trace.cmm" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_sram_reset_trace.cmm" PATH)

set_cache(UBINOS__BSP__NRF52_ENABLE_TRACE TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52dk_baremetal_sram.cmake)


