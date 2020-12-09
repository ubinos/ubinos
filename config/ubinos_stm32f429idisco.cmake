#
# Copyright (c) 2020 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__UBICLIB__USE_MALLOC_RETARGETING TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_HEAP FALSE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp/arch/arm/cortexm/stm32f429idisco/stm32f429idisco.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubik.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubidrv.cmake)

