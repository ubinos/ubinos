#
# Copyright (c) 2025 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

# ubinos_config_info {"name_base": "ubinos", "build_type": "cmake_ubinos"}

set_cache(UBINOS__UBICLIB__EXCLUDE_HEAP TRUE  BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_LOGM TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_LIST TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_DLIST TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_CIRBUF TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_CBUF TRUE BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_BITMAP TRUE BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/aarch64/aarch64-none-elf.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp/arch/aarch64/cortexa/cortex_a53_qemu_virt/cortex_a53_qemu_virt.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib.cmake)

