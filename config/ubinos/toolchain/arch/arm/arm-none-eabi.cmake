#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

set(_tmp_prefix "arm-none-eabi")

########

set_cache(PROJECT_TOOLCHAIN_PREFIX "${_tmp_prefix}" STRING)
set_cache(PROJECT_TOOLCHAIN_GDB_COMMAND "${_tmp_prefix}-gdb" STRING)

########

set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_C_COMPILER ${_tmp_prefix}-gcc)
set(CMAKE_CXX_COMPILER ${_tmp_prefix}-g++)

enable_language(ASM C CXX)

set(CMAKE_ASM_COMPILER ${_tmp_prefix}-gcc)
set(CMAKE_ASM_COMPILER_AR ${_tmp_prefix}-gcc-ar)
set(CMAKE_ASM_COMPILER_RANLIB ${_tmp_prefix}-gcc-ranlib)

set(CMAKE_C_COMPILER_AR ${_tmp_prefix}-gcc-ar)
set(CMAKE_C_COMPILER_RANLIB ${_tmp_prefix}-gcc-ranlib)

set(CMAKE_CXX_COMPILER_AR ${_tmp_prefix}-gcc-ar)
set(CMAKE_CXX_COMPILER_RANLIB ${_tmp_prefix}-gcc-ranlib)


set(CMAKE_AR ${_tmp_prefix}-ar)
set(CMAKE_RANLIB ${_tmp_prefix}-ranlib)
set(CMAKE_LINKER ${_tmp_prefix}-ld)
set(CMAKE_NM ${_tmp_prefix}-nm)
set(CMAKE_OBJCOPY ${_tmp_prefix}-objcopy)
set(CMAKE_OBJDUMP ${_tmp_prefix}-objdump)
set(CMAKE_STRIP ${_tmp_prefix}-strip)

set(CMAKE_ASM_LINK_FLAGS)
set(CMAKE_C_LINK_FLAGS)
set(CMAKE_CXX_LINK_FLAGS)
set(CMAKE_EXE_LINKER_FLAGS)
set(CMAKE_STATIC_LINKER_FLAGS)
set(CMAKE_SHARED_LINKER_FLAGS)
set(CMAKE_MODULE_LINKER_FLAGS)

set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
set(CMAKE_LINK_LIBRARY_SUFFIX)
set(CMAKE_DL_LIBS)
set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
set(CMAKE_C_LINK_SHARED_LIBRARY)
set(CMAKE_C_LINK_MODULE_LIBRARY)
set(CMAKE_CXX_LINK_SHARED_LIBRARY)
set(CMAKE_CXX_LINK_MODULE_LIBRARY)

set(CMAKE_ASM_FLAGS)
set(CMAKE_C_FLAGS)
set(CMAKE_CXX_FLAGS)
set(CMAKE_EXE_LINKER_FLAGS)

