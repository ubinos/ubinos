#
# Copyright (c) 2019 Sung Ho Park and CSOS
#
# SPDX-License-Identifier: Apache-2.0
#

if(___UBINOS_COMMON_CMAKE)
  return()
endif()
set(___UBINOS_COMMON_CMAKE 1)

set(IGNORE_NOT_USED_WARNING "${PROJECT_CONFIG_DIR} ${PROJECT_CONFIG_NAME} ${PROJECT_LIBRARY_DIR}")

macro(set_cache name value type)
    set(${name} ${value} CACHE ${type} "")
endmacro(set_cache)

macro(set_cache_default name value type helpstr)
    set(${name} ${value} CACHE ${type} "")
    set_property(CACHE ${name} PROPERTY HELPSTRING ${helpstr})
endmacro(set_cache_default)

set(UBINOS__BSP__CMD_LOAD "")
set(UBINOS__BSP__CMD_DSERVER "")
set(UBINOS__BSP__CMD_XDSERVER "")

macro(___project_config_begin)
    file(WRITE ${PROJECT_BINARY_DIR}/ubinos_config.h
        "#ifndef UBINOS_CONFIG_H_\n"
        "#define UBINOS_CONFIG_H_\n"
        "\n"
        "#ifdef  __cplusplus\n"
        "extern \"C\" {\n"
        "#endif\n"
        "\n"
        "\n"
    )

    include_directories(${PROJECT_BINARY_DIR})
    include_directories(${PROJECT_BASE_DIR}/include)
endmacro(___project_config_begin)

macro(___project_config_end)
    set(_tmp_fname "${PROJECT_SOURCE_DIR}/config.h.cmake")
    if(NOT EXISTS "${_tmp_fname}")
        set(_tmp_fname "${PROJECT_UBINOS_DIR}/resource/ubinos/dummy/config.h.cmake")
    endif()
    configure_file(
        ${_tmp_fname}
        ${PROJECT_BINARY_DIR}/___ubinos_config.h
    )
    file(READ ${PROJECT_BINARY_DIR}/___ubinos_config.h _tmp_fdata)
    file(REMOVE ${PROJECT_BINARY_DIR}/___ubinos_config.h)
    file(APPEND ${PROJECT_BINARY_DIR}/ubinos_config.h ${_tmp_fdata})
    file(APPEND ${PROJECT_BINARY_DIR}/ubinos_config.h
        "#ifdef  __cplusplus\n"
        "}\n"
        "#endif\n"
        "\n"
        "#endif /* UBINOS_CONFIG_H_ */\n"
        "\n"
        "\n"
    )

	set(_tmp_include_flags)
    get_property(_tmp_include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach(_dir ${_tmp_include_dirs})
        set(_tmp_include_flags "${_tmp_include_flags} -I${_dir}")
    endforeach()

	set(_tmp_def_flags)
    get_property(_tmp_defs DIRECTORY PROPERTY COMPILE_DEFINITIONS)
    foreach(_def ${_tmp_defs})
        set(_tmp_def_flags "${_tmp_def_flags} -D${_def}")
    endforeach()

    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_asm.txt "${CMAKE_ASM_FLAGS} ${_tmp_def_flags} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_c.txt "${CMAKE_C_FLAGS} ${_tmp_def_flags} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_cxx.txt "${CMAKE_CXX_FLAGS} ${_tmp_def_flags} ${_tmp_include_flags}")

    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/../Default)
    file(COPY ${PROJECT_BINARY_DIR}/compile_flags_asm.txt DESTINATION ${PROJECT_BINARY_DIR}/../Default/)
    file(COPY ${PROJECT_BINARY_DIR}/compile_flags_c.txt DESTINATION ${PROJECT_BINARY_DIR}/../Default/)
    file(COPY ${PROJECT_BINARY_DIR}/compile_flags_cxx.txt DESTINATION ${PROJECT_BINARY_DIR}/../Default/)
endmacro(___project_config_end)

macro(___project_add_app__clean_default_dir)
    # 전체 파일 삭제
    file(GLOB_RECURSE ___files_to_delete
        "${PROJECT_BINARY_DIR}/../Default/*"
    )
    list(REVERSE ___files_to_delete)
    foreach(item IN LISTS ___files_to_delete)
        file(REMOVE_RECURSE "${item}")
    endforeach()

    # 빈 디렉토리 삭제 (깊은 디렉토리부터 먼저)
    file(GLOB_RECURSE ___dirs_to_delete
        LIST_DIRECTORIES true
        "${PROJECT_BINARY_DIR}/../Default/*"
    )
    list(REVERSE ___dirs_to_delete)
    foreach(dir IN LISTS ___dirs_to_delete)
        if(IS_DIRECTORY "${dir}")
            file(REMOVE_RECURSE "${dir}")
        endif()
    endforeach()
endmacro(___project_add_app__clean_default_dir)

macro(___project_add_app)
    add_executable(${PROJECT_EXE_NAME} ${PROJECT_APP_SOURCES})

    ___project_add_app__set_link_flags()

    ___project_add_app__clean_default_dir()

    ___project_add_app__gen_linkscript()

    ___project_add_app__gen_debugscript()

    ___project_add_app__gen_make_target()

    ___project_add_app__gen_binary()

    ___project_add_app__refine_debugscript()

    ___project_add_app__copy_to_default()

    ___project_add_app__show_result()

endmacro(___project_add_app)

macro(___project_show)
    message(STATUS "")
    message(STATUS "============================================================================")
    message(STATUS "PROJECT_NAME                        = ${PROJECT_NAME}")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_CONFIG_NAME                 = ${PROJECT_CONFIG_NAME}")
    message(STATUS "PROJECT_CONFIG_DIR                  = ${PROJECT_CONFIG_DIR}")
    message(STATUS "PROJECT_LIBRARY_DIR                 = ${PROJECT_LIBRARY_DIR}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_UBINOS_DIR                  = ${PROJECT_UBINOS_DIR}")
    message(STATUS "PROJECT_TOOLBOX                     = ${PROJECT_TOOLBOX}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_BASE_DIR                    = ${PROJECT_BASE_DIR}")
    message(STATUS "PROJECT_SOURCE_DIR                  = ${PROJECT_SOURCE_DIR}")
    message(STATUS "PROJECT_BINARY_DIR (OUTPUT_DIR)     = ${PROJECT_BINARY_DIR}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_LIBRARIES                   = ${PROJECT_LIBRARIES}")
    message(STATUS "PROJECT_SOURCES                     = ${PROJECT_SOURCES}")
    message(STATUS "PROJECT_APP_SOURCES                 = ${PROJECT_APP_SOURCES}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "CMAKE_BUILD_TYPE                    = ${CMAKE_BUILD_TYPE}")
    message(STATUS "")
    message(STATUS "CMAKE_SYSTEM_NAME                   = ${CMAKE_SYSTEM_NAME}")
    message(STATUS "CMAKE_GENERATOR                     = ${CMAKE_GENERATOR}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_COMPILER                  = ${CMAKE_ASM_COMPILER}")
    message(STATUS "CMAKE_ASM_COMPILER_AR               = ${CMAKE_ASM_COMPILER_AR}")
    message(STATUS "CMAKE_ASM_COMPILER_RANLIB           = ${CMAKE_ASM_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_C_COMPILER                    = ${CMAKE_C_COMPILER}")
    message(STATUS "CMAKE_C_COMPILER_AR                 = ${CMAKE_C_COMPILER_AR}")
    message(STATUS "CMAKE_C_COMPILER_RANLIB             = ${CMAKE_C_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_CXX_COMPILER                  = ${CMAKE_CXX_COMPILER}")
    message(STATUS "CMAKE_CXX_COMPILER_AR               = ${CMAKE_CXX_COMPILER_AR}")
    message(STATUS "CMAKE_CXX_COMPILER_RANLIB           = ${CMAKE_CXX_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_AR                            = ${CMAKE_AR}")
    message(STATUS "CMAKE_RANLIB                        = ${CMAKE_RANLIB}")
    message(STATUS "CMAKE_LINKER                        = ${CMAKE_LINKER}")
    message(STATUS "CMAKE_NM                            = ${CMAKE_NM}")
    message(STATUS "CMAKE_OBJCOPY                       = ${CMAKE_OBJCOPY}")
    message(STATUS "CMAKE_OBJDUMP                       = ${CMAKE_OBJDUMP}")
    message(STATUS "CMAKE_STRIP                         = ${CMAKE_STRIP}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_FLAGS                     = ${CMAKE_ASM_FLAGS}")
    message(STATUS "CMAKE_ASM_FLAGS_DEBUG               = ${CMAKE_ASM_FLAGS_DEBUG}")
    message(STATUS "CMAKE_ASM_FLAGS_RELEASE             = ${CMAKE_ASM_FLAGS_RELEASE}")
    message(STATUS "CMAKE_ASM_FLAGS_MINSIZEREL          = ${CMAKE_ASM_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_C_FLAGS                       = ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS_DEBUG                 = ${CMAKE_C_FLAGS_DEBUG}")
    message(STATUS "CMAKE_C_FLAGS_RELEASE               = ${CMAKE_C_FLAGS_RELEASE}")
    message(STATUS "CMAKE_C_FLAGS_MINSIZEREL            = ${CMAKE_C_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_CXX_FLAGS                     = ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS_DEBUG               = ${CMAKE_CXX_FLAGS_DEBUG}")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE             = ${CMAKE_CXX_FLAGS_RELEASE}")
    message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL          = ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_STATIC_LIBRARY_PREFIX         = ${CMAKE_STATIC_LIBRARY_PREFIX}")
    message(STATUS "CMAKE_STATIC_LIBRARY_SUFFIX         = ${CMAKE_STATIC_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_EXECUTABLE_SUFFIX             = ${CMAKE_EXECUTABLE_SUFFIX}")
    message(STATUS "CMAKE_SHARED_LIBRARY_PREFIX         = ${CMAKE_SHARED_LIBRARY_PREFIX}")
    message(STATUS "CMAKE_SHARED_LIBRARY_SUFFIX         = ${CMAKE_SHARED_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_LINK_LIBRARY_SUFFIX           = ${CMAKE_LINK_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_DL_LIBS                       = ${CMAKE_DL_LIBS}")
    message(STATUS "CMAKE_FIND_LIBRARY_PREFIXES         = ${CMAKE_FIND_LIBRARY_PREFIXES}")
    message(STATUS "CMAKE_FIND_LIBRARY_SUFFIXES         = ${CMAKE_FIND_LIBRARY_SUFFIXES}")
    message(STATUS "")
    message(STATUS "CMAKE_C_LINK_SHARED_LIBRARY         = ${CMAKE_C_LINK_SHARED_LIBRARY}")
    message(STATUS "CMAKE_C_LINK_MODULE_LIBRARY         = ${CMAKE_C_LINK_MODULE_LIBRARY}")
    message(STATUS "CMAKE_CXX_LINK_SHARED_LIBRARY       = ${CMAKE_CXX_LINK_SHARED_LIBRARY}")
    message(STATUS "CMAKE_CXX_LINK_MODULE_LIBRARY       = ${CMAKE_CXX_LINK_MODULE_LIBRARY}")
    message(STATUS "")
    message(STATUS "FLAGS                               = ${FLAGS}")
    message(STATUS "LINK_FLAGS                          = ${LINK_FLAGS}")
    message(STATUS "CMAKE_ASM_LINK_FLAGS                = ${CMAKE_ASM_LINK_FLAGS}")
    message(STATUS "CMAKE_C_LINK_FLAGS                  = ${CMAKE_C_LINK_FLAGS}")
    message(STATUS "CMAKE_CXX_LINK_FLAGS                = ${CMAKE_CXX_LINK_FLAGS}")
    message(STATUS "CMAKE_SHARED_LINKER_FLAGS           = ${CMAKE_SHARED_LINKER_FLAGS}")
    message(STATUS "CMAKE_STATIC_LINKER_FLAGS           = ${CMAKE_STATIC_LINKER_FLAGS}")
    message(STATUS "CMAKE_SHARED_LINKER_FLAGS           = ${CMAKE_SHARED_LINKER_FLAGS}")
    message(STATUS "CMAKE_MODULE_LINKER_FLAGS           = ${CMAKE_MODULE_LINKER_FLAGS}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS              = ${CMAKE_EXE_LINKER_FLAGS}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_LINK_EXECUTABLE           = ${CMAKE_ASM_LINK_EXECUTABLE}")
    message(STATUS "CMAKE_C_LINK_EXECUTABLE             = ${CMAKE_C_LINK_EXECUTABLE}")
    message(STATUS "CMAKE_CXX_LINK_EXECUTABLE           = ${CMAKE_CXX_LINK_EXECUTABLE}")

    message(STATUS "")
    message(STATUS "CMAKE_ASM_COMPILER_LAUNCHER         = ${CMAKE_ASM_COMPILER_LAUNCHER}")
    message(STATUS "CMAKE_C_COMPILER_LAUNCHER           = ${CMAKE_C_COMPILER_LAUNCHER}")
    message(STATUS "CMAKE_CXX_COMPILER_LAUNCHER         = ${CMAKE_CXX_COMPILER_LAUNCHER}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_CONFIG_NAME                 = ${PROJECT_CONFIG_NAME}")
    message(STATUS "PROJECT_CONFIG_DIR                  = ${PROJECT_CONFIG_DIR}")
    message(STATUS "PROJECT_EXE_NAME                    = ${PROJECT_EXE_NAME}")
    message(STATUS "PROJECT_UBINOS_LIBRARIES            = ${PROJECT_UBINOS_LIBRARIES}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_TOOLCHAIN_PREFIX            = ${PROJECT_TOOLCHAIN_PREFIX}")
    message(STATUS "PROJECT_TOOLCHAIN_GDB_COMMAND       = ${PROJECT_TOOLCHAIN_GDB_COMMAND}")
    message(STATUS "PROJECT_BUILD_TYPE                  = ${PROJECT_BUILD_TYPE}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "UBINOS__VERSION                     = ${UBINOS__VERSION}")
    message(STATUS "")
    message(STATUS "UBINOS__BSP__BOARD_MODEL            = ${UBINOS__BSP__BOARD_MODEL}")
    message(STATUS "UBINOS__BSP__BOARD_REVISION_NO      = ${UBINOS__BSP__BOARD_REVISION_NO}")
    message(STATUS "UBINOS__BSP__BOARD_VARIATION_NAME   = ${UBINOS__BSP__BOARD_VARIATION_NAME}")
    message(STATUS "UBINOS__BSP__CPU_ARCH               = ${UBINOS__BSP__CPU_ARCH}")
    message(STATUS "UBINOS__BSP__CPU_TYPE               = ${UBINOS__BSP__CPU_TYPE}")
    message(STATUS "UBINOS__BSP__CPU_ENDIAN             = ${UBINOS__BSP__CPU_ENDIAN}")
    message(STATUS "UBINOS__BSP__CPU_ARMTHUMBSTATE      = ${UBINOS__BSP__CPU_ARMTHUMBSTATE}")
    message(STATUS "UBINOS__BSP__CPU_MODEL              = ${UBINOS__BSP__CPU_MODEL}")
    message(STATUS "")
    message(STATUS "UBINOS__BSP__LINKSCRIPT_FILE        = ${UBINOS__BSP__LINKSCRIPT_FILE}")
    message(STATUS "")
    message(STATUS "UBINOS__BSP__DEBUG_SERVER_SERIAL    = ${UBINOS__BSP__DEBUG_SERVER_SERIAL}")
    message(STATUS "UBINOS__BSP__DEBUG_SERVER_PORT      = ${UBINOS__BSP__DEBUG_SERVER_PORT}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    get_property(_tmp_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    message(STATUS "INCLUDE_DIRECTORIES             = ${_tmp_dirs}")
    get_property(_tmp_dirs DIRECTORY PROPERTY LINK_DIRECTORIES)
    message(STATUS "LINK_DIRECTORIES                = ${_tmp_dirs}")
    get_property(_tmp_def DIRECTORY PROPERTY COMPILE_DEFINITIONS)
    message(STATUS "COMPILE_DEFINITIONS             = ${_tmp_def}")
    message(STATUS "")
    # message(STATUS "----------------------------------------------------------------------------")
    # message(STATUS "")
    # message(STATUS "UBINOS__BSP__CMD_DSERVER        = ${UBINOS__BSP__CMD_DSERVER}")
    # message(STATUS "UBINOS__BSP__CMD_XDSERVER       = ${UBINOS__BSP__CMD_XDSERVER}")
    # message(STATUS "UBINOS__BSP__CMD_LOAD           = ${UBINOS__BSP__CMD_LOAD}")
    # message(STATUS "")
    message(STATUS "============================================================================")
    message(STATUS "")
endmacro(___project_show)

macro(ubinos_project_begin)
    get_filename_component(_tmp_base_dir "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

    set(PROJECT_BASE_DIR "${_tmp_base_dir}")

    string(STRIP "${PROJECT_CONFIG_NAME}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set_cache(PROJECT_CONFIG_NAME "none" PATH)
    endif()
    string(STRIP "${PROJECT_CONFIG_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set_cache(PROJECT_CONFIG_DIR "${PROJECT_BASE_DIR}/app" PATH)
    endif()

    string(STRIP "${PROJECT_LIBRARY_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        if(EXISTS "${PROJECT_BASE_DIR}/library")
            set_cache(PROJECT_LIBRARY_DIR "${PROJECT_BASE_DIR}/library" PATH)
        else()
            set_cache(PROJECT_LIBRARY_DIR "${PROJECT_BASE_DIR}/.." PATH)
        endif()
    endif()

    string(STRIP "${PROJECT_UBINOS_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set(PROJECT_UBINOS_DIR "${PROJECT_LIBRARY_DIR}/ubinos")
    endif()

    string(STRIP "${PROJECT_TOOLBOX}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set(PROJECT_TOOLBOX "${PROJECT_UBINOS_DIR}/make/toolbox.py")
    endif()
    set(PROJECT_TOOLBOX_RUN_CMD python ${PROJECT_TOOLBOX})

    set_cache_default(PROJECT_CONFIG_NAME "" STRING "Config name")
    set_cache_default(PROJECT_CONFIG_DIR "" PATH "Config directory")
    set_cache_default(PROJECT_LIBRARY_DIR "" PATH "Library directory")

    include("${PROJECT_CONFIG_DIR}/${PROJECT_CONFIG_NAME}.cmake")

    if(UBINOS__BSP__BOARD_MODEL STREQUAL "LOCAL")
        include("${PROJECT_UBINOS_DIR}/config/common_local.cmake")
    elseif(UBINOS__BSP__BOARD_MODEL STREQUAL "NOBSP")
        include("${PROJECT_UBINOS_DIR}/config/common_nobsp.cmake")
    else()
        include("${PROJECT_UBINOS_DIR}/config/common_cross.cmake")
    endif()

    set_cache_default(PROJECT_PICOTOOL "" STRING "picotool path")
endmacro(ubinos_project_begin)

macro(___add_ubinos_library name)
    if(NOT ${PROJECT_NAME} STREQUAL ${name})
        set(_tmp_fname "${PROJECT_LIBRARY_DIR}/${name}/source/config.h.cmake")
        if(EXISTS "${_tmp_fname}")
            configure_file(
                ${_tmp_fname}
                ${PROJECT_BINARY_DIR}/___ubinos_config.h
            )
            file(READ ${PROJECT_BINARY_DIR}/___ubinos_config.h _tmp_fdata)
            file(REMOVE ${PROJECT_BINARY_DIR}/___ubinos_config.h)
            file(APPEND ${PROJECT_BINARY_DIR}/ubinos_config.h ${_tmp_fdata})
        endif()

        set(_tmp_fname "${PROJECT_LIBRARY_DIR}/${name}/include")
        if(EXISTS "${_tmp_fname}")
            include_directories(${PROJECT_LIBRARY_DIR}/${name}/include)
        endif()

        set(_tmp_fname "${PROJECT_LIBRARY_DIR}/${name}/source/sources.cmake")
        if(EXISTS "${_tmp_fname}")
            set(PROJECT_SOURCES)
            include(${_tmp_fname})
            if(PROJECT_SOURCES)
                add_library(${name} STATIC ${PROJECT_SOURCES})
                set(PROJECT_LIBRARIES ${name} ${PROJECT_LIBRARIES})
            endif()
        endif()
    endif()
endmacro(___add_ubinos_library)

macro(ubinos_project_end)
    enable_language(${PROJECT_LANGUAGES})

    ___project_config_begin()

    foreach(_lib ${PROJECT_UBINOS_LIBRARIES})
        ___add_ubinos_library(${_lib})
    endforeach()

    ___project_config_end()

    set(PROJECT_SOURCES)
    set(_tmp_fname "${PROJECT_SOURCE_DIR}/sources.cmake")
    if(EXISTS "${_tmp_fname}")
        include(${_tmp_fname})
    endif()
    set(PROJECT_SOURCES ${PROJECT_SOURCES} "${PROJECT_UBINOS_DIR}/resource/ubinos/dummy/dummy.c")
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
    set(PROJECT_LIBRARIES ${PROJECT_NAME} ${PROJECT_LIBRARIES})

    set(PROJECT_APP_SOURCES ${PROJECT_APP_SOURCES} "${PROJECT_UBINOS_DIR}/resource/ubinos/dummy/dummy.c")

    if(INCLUDE__APP)
        ___project_add_app()
    endif()

    if(NOT ${UBINOS__BSP__DOXYGEN_FILE} STREQUAL "")
        file(COPY ${UBINOS__BSP__DOXYGEN_FILE}
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    set(CMAKE_COLOR_MAKEFILE OFF)
    set(CMAKE_VERBOSE_MAKEFILE OFF)

    ___project_show()
endmacro(ubinos_project_end)

