set_cache_default(PROJECT_BUILD_TYPE                                            "Debug" STRING "Build type [None | Debug | Release | MinSizeRel]")

set_cache_default(PROJECT_TOOLCHAIN_PREFIX                                      ""      STRING "Toolchain prefix [arm-none-eabi]")
set_cache_default(PROJECT_TOOLCHAIN_GDB_COMMAND                                 ""      STRING "GDB command [arm-none-eabi-gdb]")


########

set(PROJECT_EXE_NAME "app")


string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)


if(PROJECT_BUILD_TYPE STREQUAL "Debug")

    set(CMAKE_BUILD_TYPE "Debug")

elseif(PROJECT_BUILD_TYPE STREQUAL "Release")

    set(CMAKE_BUILD_TYPE "Release")

elseif(PROJECT_BUILD_TYPE STREQUAL "MinSizeRel")

    set(CMAKE_BUILD_TYPE "MinSizeRel")

else()

    set(CMAKE_BUILD_TYPE "None")

endif()

set(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

