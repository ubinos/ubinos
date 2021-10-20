#
# Copyright (c) 2020 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubik_tester", "build_type": "cmake_ubinos", "app": true}

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32f429idisco.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubik_test.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/ubik_tester.cmake)

