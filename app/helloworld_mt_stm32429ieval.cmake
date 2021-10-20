#
# Copyright (c) 2020 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "helloworld_mt", "build_type": "cmake_ubinos", "app": true}

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32429ieval.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/helloworld_mt.cmake)

