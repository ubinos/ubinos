#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "cli_tester", "build_type": "cmake_ubinos", "app": true}

set_cache(UBINOS__UBICLIB__EXCLUDE_CLI FALSE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32l475eiot01.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/cli_tester.cmake)

