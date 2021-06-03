#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52840dk.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib_test.cmake)

include(${PROJECT_UBINOS_DIR}/app/ubiclib_tester.cmake)


