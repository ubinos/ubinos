#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubiclib_tester", "build_type": "cmake_ubinos", "app": true}

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52840dk.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib_test.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/ubiclib_tester.cmake)

