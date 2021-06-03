#
# Copyright (c) 2020 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

set_cache(UBINOS__UBICLIB__EXCLUDE_CLI FALSE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_stm32f429idisco.cmake)

include(${PROJECT_UBINOS_DIR}/app/cli_tester.cmake)

