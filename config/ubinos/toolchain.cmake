#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

set_cache_default(PROJECT_BUILD_TYPE "Debug" STRING "Build type [None | Debug | Release | MinSizeRel]")

set_cache_default(PROJECT_TOOLCHAIN_PREFIX "" STRING "Toolchain prefix [arm-none-eabi]")
set_cache_default(PROJECT_TOOLCHAIN_GDB_COMMAND "" STRING "GDB command [arm-none-eabi-gdb]")

set_cache_default(PROJECT_TOOLCHAIN_C_STD "C99" STRING "C standard version [C99 | GNU11]")

set_cache_default(PROJECT_TOOLCHAIN_CXX_STD "GNU++98" STRING "C++ standard version [GNU++98 | GNU++14]")
set_cache_default(PROJECT_TOOLCHAIN_CXX_F_NO_RTTI TRUE BOOL "-fno-rtti")
set_cache_default(PROJECT_TOOLCHAIN_CXX_F_NO_EXCEPTIONS TRUE BOOL "-fno-exceptions")
set_cache_default(PROJECT_TOOLCHAIN_CXX_W_NO_CXX14_COMPAT TRUE BOOL "-Wno-c++14-compat")

########

set(PROJECT_EXE_NAME "app")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(REPLACE "-" "_" PROJECT_NAME_UPPER ${PROJECT_NAME_UPPER})

if(PROJECT_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE "Debug")
elseif(PROJECT_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Release")
elseif(PROJECT_BUILD_TYPE STREQUAL "MinSizeRel")
    set(CMAKE_BUILD_TYPE "MinSizeRel")
else()
    set(CMAKE_BUILD_TYPE "None")
endif()

if(PROJECT_TOOLCHAIN_C_STD STREQUAL "C99")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=c99")
elseif(PROJECT_TOOLCHAIN_C_STD STREQUAL "GNU11")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=gnu11")
else()
    message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_C_STD")
endif()

if(PROJECT_TOOLCHAIN_CXX_STD STREQUAL "GNU++98")
    set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=gnu++98")
elseif(PROJECT_TOOLCHAIN_CXX_STD STREQUAL "GNU++14")
    set(CMAKE_CXX_FLAGS   "${CMAKE_CXX_FLAGS} -std=gnu++14")
else()
    message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_CXX_STD")
endif()
if(PROJECT_TOOLCHAIN_CXX_F_NO_RTTI)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()
if(PROJECT_TOOLCHAIN_CXX_F_NO_EXCEPTIONS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
endif()
if(PROJECT_TOOLCHAIN_CXX_W_NO_CXX14_COMPAT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++14-compat")
endif()

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp -D__ASSEMBLY__")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_MAKEFILE OFF)
#set(CMAKE_VERBOSE_MAKEFILE ON)


