#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN 0x64000000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH 0x00080000 STRING)

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/stm3221geval/t32_flash_load_trace.cmm" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/stm3221geval/t32_flash_reset_trace.cmm" PATH)

set_cache(UBINOS__BSP__STM32_ENABLE_TRACE TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm3221geval_baremetal_flash_extsram_aws.cmake)


