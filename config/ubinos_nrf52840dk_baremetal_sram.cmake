#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__UBICLIB__EXCLUDE_LOGM TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_LIST TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_DLIST TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_CIRBUF TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_CBUF TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_BITMAP TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp/arch/arm/cortexm/nrf52840dk/nrf52840dk_sram.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib.cmake)


