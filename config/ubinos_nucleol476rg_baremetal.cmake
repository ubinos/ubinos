#
# Copyright (c) 2021 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubinos", "build_type": "cmake_ubinos"}

set_cache(UBINOS__UBICLIB__EXCLUDE_HEAP FALSE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp/arch/arm/cortexm/nucleol476rg/nucleol476rg.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib.cmake)

