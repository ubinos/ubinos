#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# {ubinos_config_type: [buildable, cmake, app]}

set_cache(PROJECT_BUILD_TYPE                                                    "MinSizeRel"        STRING)
set_cache(UBINOS__BSP__CPU_ARMTHUMBSTATE                                          "THUMB"             STRING)

include(${PROJECT_UBINOS_DIR}/config/ubinos_sam9xe512ek_baremetal_sram.cmake)

include(${PROJECT_UBINOS_DIR}/app/helloworld.cmake)


