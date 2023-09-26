#
#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubinos", "build_type": "cmake_ubinos"}

set_cache(UBINOS__BSP__BOARD_VARIATION_NAME "THINGY52" STRING)

include(${CMAKE_CURRENT_LIST_DIR}/ubinos_nrf52dk_baremetal.cmake)

