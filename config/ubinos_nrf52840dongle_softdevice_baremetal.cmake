#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

set_cache(UBINOS__BSP__BOARD_MODEL "NRF52840DONGLE" STRING)
set_cache(UBINOS__BSP__USE_DTTY FALSE BOOL)

include(${CMAKE_CURRENT_LIST_DIR}/ubinos_nrf52840dk_softdevice_baremetal.cmake)


