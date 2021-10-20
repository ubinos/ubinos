#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "helloworld", "build_type": "cmake_ubinos", "app": true}

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32f769ieval_baremetal_sram.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/helloworld.cmake)

