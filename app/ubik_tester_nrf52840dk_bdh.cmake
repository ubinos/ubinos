#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

set_cache(UBINOS__BSP__LINKSCRIPT_FILE "${PROJECT_UBINOS_DIR}/source/ubinos/bsp/arch/arm/cortexm/nrf52/xxaa/flash_bdh.ld" PATH)

include(${PROJECT_UBINOS_DIR}/app/ubik_tester_nrf52840dk.cmake)


