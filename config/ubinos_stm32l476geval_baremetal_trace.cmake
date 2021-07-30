#
# Copyright (c) 2021 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, lib]}

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/stm32l476geval/t32_flash_load_trace.cmm" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/stm32l476geval/t32_flash_reset_trace.cmm" PATH)

set_cache(UBINOS__BSP__STM32_ENABLE_TRACE TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32l476geval_baremetal.cmake)
