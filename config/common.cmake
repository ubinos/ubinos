if(___UBINOS_COMMON_CMAKE)
  return()
endif()
set(___UBINOS_COMMON_CMAKE 1)

macro(set_cache name value type)
    set(${name} ${value} CACHE ${type} "")
endmacro(set_cache)

macro(set_cache_default name value type helpstr)
    set(${name} ${value} CACHE ${type} "")
    set_property(CACHE ${name} PROPERTY HELPSTRING ${helpstr})
endmacro(set_cache_default)

macro(___project_config_begin)
    file(WRITE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h
    "#ifndef ${PROJECT_NAME_UPPER}_CONFIG_H_\n"
    "#define ${PROJECT_NAME_UPPER}_CONFIG_H_\n"
    "\n"
    "#ifdef  __cplusplus\n"
    "extern \"C\" {\n"
    "#endif\n"
    "\n"
    "\n")
endmacro(___project_config_begin)

macro(___project_config_end)
    set(_tmp_fname "${PROJECT_SOURCE_DIR}/config.h.cmake")
    if(NOT EXISTS "${_tmp_fname}")
        set(_tmp_fname "${PROJECT_UBINOS_DIR}/resource/ubinos/dummy/config.h.cmake")
    endif()
    configure_file(
        ${_tmp_fname}
        ${PROJECT_BINARY_DIR}/___${PROJECT_NAME}_config.h
    )
    file(READ ${PROJECT_BINARY_DIR}/___${PROJECT_NAME}_config.h _tmp_fdata)
    file(REMOVE ${PROJECT_BINARY_DIR}/___${PROJECT_NAME}_config.h)
    file(APPEND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h ${_tmp_fdata})

    file(APPEND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h
    "#ifdef  __cplusplus\n"
    "}\n"
    "#endif\n"
    "\n"
    "#endif /* ${PROJECT_NAME_UPPER}_CONFIG_H_ */\n"
    "\n"
    "\n")

    file(WRITE ${PROJECT_BASE_DIR}/include/${PROJECT_NAME}_config.h "#include \"${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h\"\n")
    include_directories(${PROJECT_BASE_DIR}/include)

	set(_tmp_include_flags)
    get_property(_tmp_include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    foreach(_dir ${_tmp_include_dirs})
        set(_tmp_include_flags "${_tmp_include_flags} -I${_dir}")
    endforeach()
    
    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_asm.txt "${CMAKE_ASM_FLAGS} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_c.txt "${CMAKE_C_FLAGS} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/compile_flags_cxx.txt "${CMAKE_CXX_FLAGS} ${_tmp_include_flags}")
    
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/../Default)
    file(WRITE ${PROJECT_BINARY_DIR}/../Default/compile_flags_asm.txt "${CMAKE_ASM_FLAGS} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/../Default/compile_flags_c.txt "${CMAKE_C_FLAGS} ${_tmp_include_flags}")
    file(WRITE ${PROJECT_BINARY_DIR}/../Default/compile_flags_cxx.txt "${CMAKE_CXX_FLAGS} ${_tmp_include_flags}")
endmacro(___project_config_end)

macro(___project_add_app)
    if(NOT ${UBINOS__BSP__LINKSCRIPT_FILE} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__LINKSCRIPT_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld)
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH2"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH3"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH3_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH3_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH4"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH4_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH4_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH5"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH5_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH5_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH6"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH6_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH6_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH7"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH7_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH7_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "FLASH8"
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH8_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_FLASH8_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM2"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM3"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM4"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM4_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM4_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM5"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM5_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM5_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM6"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM6_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM6_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM7"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM7_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM7_LENGTH})
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_linkscript
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
                        "RAM8"
                        ${UBINOS__BSP__LINK_MEMMAP_RAM8_ORIGIN}
                        ${UBINOS__BSP__LINK_MEMMAP_RAM8_LENGTH})
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD}
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb)
    endif()
    
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RESET} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__GDBSCRIPT_FILE_RESET}
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb)
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RUN} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__GDBSCRIPT_FILE_RUN}
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb)
    endif()
    
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG}
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb)
    endif()
    
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH}
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb)
    endif()
    
    if(NOT ${UBINOS__BSP__FLASH_WRITER_FILE} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__FLASH_WRITER_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/flash_writer.elf)
    endif()

    if(NOT ${UBINOS__BSP__OPENOCD_CONFIG_FILE} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__OPENOCD_CONFIG_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/openocd.cfg)
    endif()

    if(NOT ${UBINOS__BSP__SYS_INIT_FILE} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__SYS_INIT_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/sys_init.elf)
    endif()
    
    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__T32SCRIPT_FILE_LOAD}
                        ${CMAKE_CURRENT_BINARY_DIR}/t32_load.cmm)
    endif()
    
    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_RESET} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__T32SCRIPT_FILE_RESET}
                        ${CMAKE_CURRENT_BINARY_DIR}/t32_reset.cmm)
    endif()

    add_executable(${PROJECT_EXE_NAME} ${PROJECT_APP_SOURCES})
    target_link_libraries(${PROJECT_EXE_NAME} -Wl,--start-group ${PROJECT_LIBRARIES} -Wl,--end-group)
    
    add_custom_target(reset
        COMMAND  ${PROJECT_TOOLCHAIN_GDB_COMMAND} -x ./gdb_reset.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(load
        COMMAND  ${PROJECT_TOOLCHAIN_GDB_COMMAND} -x ./gdb_load.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(run
        COMMAND  ${PROJECT_TOOLCHAIN_GDB_COMMAND} -x ./gdb_run.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(debug
        COMMAND  ${PROJECT_TOOLCHAIN_GDB_COMMAND} -x ./gdb_debug.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(attach
        COMMAND  ${PROJECT_TOOLCHAIN_GDB_COMMAND} -x ./gdb_attach.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )

    add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_EXE_NAME}.elf ${PROJECT_EXE_NAME}.bin)
    add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O ihex   ${PROJECT_EXE_NAME}.elf ${PROJECT_EXE_NAME}.hex)
    
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} refine_gdbscript
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        ${PROJECT_EXE_NAME}.bin)
    endif()

    if(NOT ${UBINOS__BSP__GDBSERVER_HOST} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                        "localhost:" "${UBINOS__BSP__GDBSERVER_HOST}:")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                        "localhost:" "${UBINOS__BSP__GDBSERVER_HOST}:")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        "localhost:" "${UBINOS__BSP__GDBSERVER_HOST}:")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                        "localhost:" "${UBINOS__BSP__GDBSERVER_HOST}:")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                        "localhost:" "${UBINOS__BSP__GDBSERVER_HOST}:")
    endif()

    if(NOT ${UBINOS__BSP__GDBSERVER_PORT} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                        ":2331" ":${UBINOS__BSP__GDBSERVER_PORT}")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                        ":2331" ":${UBINOS__BSP__GDBSERVER_PORT}")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                        ":2331" ":${UBINOS__BSP__GDBSERVER_PORT}")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                        ":2331" ":${UBINOS__BSP__GDBSERVER_PORT}")
        add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX} replace_string
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                        ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                        ":2331" ":${UBINOS__BSP__GDBSERVER_PORT}")
    endif()

    if(UBINOS__BSP__NRF52_SOFTDEVICE_PRESENT AND NOT ${UBINOS__BSP__NRF52_SOFTDEVICE_FILE} STREQUAL "")
        add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${UBINOS__BSP__NRF52_SOFTDEVICE_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/nrf52_softdevice.hex)
    endif()

    add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${PROJECT_TOOLBOX} show_mapfile_info
                    ${PROJECT_EXE_NAME}.map)
endmacro(___project_add_app)

macro(___project_show)
    message(STATUS "")
    message(STATUS "============================================================================")
    message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_CONFIG_NAME             = ${PROJECT_CONFIG_NAME}")
    message(STATUS "PROJECT_CONFIG_DIR              = ${PROJECT_CONFIG_DIR}")
    message(STATUS "PROJECT_LIBRARY_DIR             = ${PROJECT_LIBRARY_DIR}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_UBINOS_DIR              = ${PROJECT_UBINOS_DIR}")
    message(STATUS "PROJECT_TOOLBOX                 = ${PROJECT_TOOLBOX}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_BASE_DIR                = ${PROJECT_BASE_DIR}")
    message(STATUS "PROJECT_SOURCE_DIR              = ${PROJECT_SOURCE_DIR}")
    message(STATUS "PROJECT_BINARY_DIR (OUTPUT_DIR) = ${PROJECT_BINARY_DIR}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_LIBRARIES               = ${PROJECT_LIBRARIES}")
    message(STATUS "PROJECT_SOURCES                 = ${PROJECT_SOURCES}")
    message(STATUS "PROJECT_APP_SOURCES             = ${PROJECT_APP_SOURCES}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "CMAKE_BUILD_TYPE                = ${CMAKE_BUILD_TYPE}")
    message(STATUS "")
    message(STATUS "CMAKE_SYSTEM_NAME               = ${CMAKE_SYSTEM_NAME}")
    message(STATUS "CMAKE_GENERATOR                 = ${CMAKE_GENERATOR}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_COMPILER              = ${CMAKE_ASM_COMPILER}")
    message(STATUS "CMAKE_ASM_COMPILER_AR           = ${CMAKE_ASM_COMPILER_AR}")
    message(STATUS "CMAKE_ASM_COMPILER_RANLIB       = ${CMAKE_ASM_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_C_COMPILER                = ${CMAKE_C_COMPILER}")
    message(STATUS "CMAKE_C_COMPILER_AR             = ${CMAKE_C_COMPILER_AR}")
    message(STATUS "CMAKE_C_COMPILER_RANLIB         = ${CMAKE_C_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_CXX_COMPILER              = ${CMAKE_CXX_COMPILER}")
    message(STATUS "CMAKE_CXX_COMPILER_AR           = ${CMAKE_CXX_COMPILER_AR}")
    message(STATUS "CMAKE_CXX_COMPILER_RANLIB       = ${CMAKE_CXX_COMPILER_RANLIB}")
    message(STATUS "")
    message(STATUS "CMAKE_AR                        = ${CMAKE_AR}")
    message(STATUS "CMAKE_RANLIB                    = ${CMAKE_RANLIB}")
    message(STATUS "CMAKE_LINKER                    = ${CMAKE_LINKER}")
    message(STATUS "CMAKE_NM                        = ${CMAKE_NM}")
    message(STATUS "CMAKE_OBJCOPY                   = ${CMAKE_OBJCOPY}")
    message(STATUS "CMAKE_OBJDUMP                   = ${CMAKE_OBJDUMP}")
    message(STATUS "CMAKE_STRIP                     = ${CMAKE_STRIP}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_FLAGS                 = ${CMAKE_ASM_FLAGS}")
    message(STATUS "CMAKE_ASM_FLAGS_RELEASE         = ${CMAKE_ASM_FLAGS_RELEASE}")
    message(STATUS "CMAKE_ASM_FLAGS_MINSIZEREL      = ${CMAKE_ASM_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_C_FLAGS                   = ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS_RELEASE           = ${CMAKE_C_FLAGS_RELEASE}")
    message(STATUS "CMAKE_C_FLAGS_MINSIZEREL        = ${CMAKE_C_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_CXX_FLAGS                 = ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS_RELEASE         = ${CMAKE_CXX_FLAGS_RELEASE}")
    message(STATUS "CMAKE_CXX_FLAGS_MINSIZEREL      = ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    message(STATUS "")
    message(STATUS "CMAKE_STATIC_LIBRARY_PREFIX     = ${CMAKE_STATIC_LIBRARY_PREFIX}")
    message(STATUS "CMAKE_STATIC_LIBRARY_SUFFIX     = ${CMAKE_STATIC_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_EXECUTABLE_SUFFIX         = ${CMAKE_EXECUTABLE_SUFFIX}")
    message(STATUS "CMAKE_SHARED_LIBRARY_PREFIX     = ${CMAKE_SHARED_LIBRARY_PREFIX}")
    message(STATUS "CMAKE_SHARED_LIBRARY_SUFFIX     = ${CMAKE_SHARED_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_LINK_LIBRARY_SUFFIX       = ${CMAKE_LINK_LIBRARY_SUFFIX}")
    message(STATUS "CMAKE_DL_LIBS                   = ${CMAKE_DL_LIBS}")
    message(STATUS "CMAKE_FIND_LIBRARY_PREFIXES     = ${CMAKE_FIND_LIBRARY_PREFIXES}")
    message(STATUS "CMAKE_FIND_LIBRARY_SUFFIXES     = ${CMAKE_FIND_LIBRARY_SUFFIXES}")
    message(STATUS "")
    message(STATUS "CMAKE_C_LINK_SHARED_LIBRARY     = ${CMAKE_C_LINK_SHARED_LIBRARY}")
    message(STATUS "CMAKE_C_LINK_MODULE_LIBRARY     = ${CMAKE_C_LINK_MODULE_LIBRARY}")
    message(STATUS "CMAKE_CXX_LINK_SHARED_LIBRARY   = ${CMAKE_CXX_LINK_SHARED_LIBRARY}")
    message(STATUS "CMAKE_CXX_LINK_MODULE_LIBRARY   = ${CMAKE_CXX_LINK_MODULE_LIBRARY}")
    message(STATUS "")
    message(STATUS "CMAKE_ASM_LINK_FLAGS            = ${CMAKE_ASM_LINK_FLAGS}")
    message(STATUS "CMAKE_C_LINK_FLAGS              = ${CMAKE_C_LINK_FLAGS}")
    message(STATUS "CMAKE_CXX_LINK_FLAGS            = ${CMAKE_CXX_LINK_FLAGS}")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS          = ${CMAKE_EXE_LINKER_FLAGS}")
    message(STATUS "CMAKE_STATIC_LINKER_FLAGS       = ${CMAKE_STATIC_LINKER_FLAGS}")
    message(STATUS "CMAKE_SHARED_LINKER_FLAGS       = ${CMAKE_SHARED_LINKER_FLAGS}")
    message(STATUS "CMAKE_MODULE_LINKER_FLAGS       = ${CMAKE_MODULE_LINKER_FLAGS}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_CONFIG_NAME             = ${PROJECT_CONFIG_NAME}")
    message(STATUS "PROJECT_CONFIG_DIR              = ${PROJECT_CONFIG_DIR}")
    message(STATUS "PROJECT_EXE_NAME                = ${PROJECT_EXE_NAME}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "PROJECT_TOOLCHAIN_PREFIX         = ${PROJECT_TOOLCHAIN_PREFIX}")
    message(STATUS "PROJECT_TOOLCHAIN_GDB_COMMAND    = ${PROJECT_TOOLCHAIN_GDB_COMMAND}")
    message(STATUS "PROJECT_BUILD_TYPE               = ${PROJECT_BUILD_TYPE}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    message(STATUS "UBINOS__VERSION_MAJOR            = ${UBINOS__VERSION_MAJOR}")
    message(STATUS "UBINOS__VERSION_MINOR            = ${UBINOS__VERSION_MINOR}")
    message(STATUS "UBINOS__VERSION_PATCH            = ${UBINOS__VERSION_PATCH}")
    message(STATUS "UBINOS__VERSION_TWEAK            = ${UBINOS__VERSION_TWEAK}")
    message(STATUS "UBINOS__VERSION                  = ${UBINOS__VERSION}")
    message(STATUS "")
    message(STATUS "UBINOS__BSP__BOARD_MODEL         = ${UBINOS__BSP__BOARD_MODEL}")
    message(STATUS "UBINOS__BSP__CPU_ARCH            = ${UBINOS__BSP__CPU_ARCH}")
    message(STATUS "UBINOS__BSP__CPU_TYPE            = ${UBINOS__BSP__CPU_TYPE}")
    message(STATUS "UBINOS__BSP__CPU_ENDIAN          = ${UBINOS__BSP__CPU_ENDIAN}")
    message(STATUS "UBINOS__BSP__CPU_ARMTHUMBSTATE   = ${UBINOS__BSP__CPU_ARMTHUMBSTATE}")
    message(STATUS "UBINOS__BSP__CPU_MODEL           = ${UBINOS__BSP__CPU_MODEL}")
    message(STATUS "")
    message(STATUS "UBINOS__BSP__LINKSCRIPT_FILE     = ${UBINOS__BSP__LINKSCRIPT_FILE}")
    message(STATUS "")
    message(STATUS "----------------------------------------------------------------------------")
    message(STATUS "")
    get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
    message(STATUS "INCLUDE_DIRECTORIES   = ${dirs}")
    get_property(dirs DIRECTORY PROPERTY LINK_DIRECTORIES)
    message(STATUS "LINK_DIRECTORIES      = ${dirs}")
    message(STATUS "")
    message(STATUS "============================================================================")
    message(STATUS "")
endmacro(___project_show)

macro(project_begin)
    get_filename_component(_tmp_base_dir "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

    set(PROJECT_BASE_DIR "${_tmp_base_dir}")

    string(STRIP "${PROJECT_CONFIG_NAME}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set_cache(PROJECT_CONFIG_NAME "default" STRING)
    endif()

    string(STRIP "${PROJECT_CONFIG_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set_cache(PROJECT_CONFIG_DIR "${PROJECT_BASE_DIR}/app" PATH)
    endif()

    string(STRIP "${PROJECT_LIBRARY_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        if(PROJECT_NAME STREQUAL "ubinos")
            set_cache(PROJECT_LIBRARY_DIR "${PROJECT_BASE_DIR}/.." PATH)
        else()
            set_cache(PROJECT_LIBRARY_DIR "${PROJECT_BASE_DIR}/library" PATH)
        endif()
    endif()
    
    string(STRIP "${PROJECT_UBINOS_DIR}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        if(PROJECT_NAME STREQUAL "ubinos")
            set(PROJECT_UBINOS_DIR "${PROJECT_BASE_DIR}")
        else()
            set(PROJECT_UBINOS_DIR "${PROJECT_LIBRARY_DIR}/ubinos")
        endif()
    endif()
    
    string(STRIP "${PROJECT_TOOLBOX}" _tmp_str)
    if("${_tmp_str}"  STREQUAL "")
        set(PROJECT_TOOLBOX "${PROJECT_UBINOS_DIR}/make/toolbox.py")
    endif()

    set_cache_default(PROJECT_CONFIG_NAME                                       ""      STRING "Config name")
    set_cache_default(PROJECT_CONFIG_DIR                                        ""      PATH "Config directory")
    set_cache_default(PROJECT_LIBRARY_DIR                                       ""      PATH "Library directory")

    include("${PROJECT_CONFIG_DIR}/${PROJECT_CONFIG_NAME}.cmake")
    
    ___project_config_begin()
endmacro(project_begin)

macro(project_add_library name)
    configure_file(
        ${PROJECT_LIBRARY_DIR}/${name}/source/config.h.cmake
        ${PROJECT_BINARY_DIR}/___${name}_config.h
    )
    file(READ   ${PROJECT_BINARY_DIR}/___${name}_config.h _tmp_fdata)
    file(REMOVE ${PROJECT_BINARY_DIR}/___${name}_config.h)
    file(APPEND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h ${_tmp_fdata})

    file(WRITE ${PROJECT_LIBRARY_DIR}/${name}/include/${name}_config.h "#include \"${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.h\"\n")
    include_directories(${PROJECT_LIBRARY_DIR}/${name}/include)

    set(PROJECT_SOURCES)
    include(${PROJECT_LIBRARY_DIR}/${name}/source/sources.cmake)
    if(PROJECT_SOURCES)
        add_library(${name} STATIC ${PROJECT_SOURCES})
        set(PROJECT_LIBRARIES ${name} ${PROJECT_LIBRARIES})
    endif()
endmacro(project_add_library)

macro(project_end)
    ___project_config_end()

    set(PROJECT_SOURCES)
    set(_tmp_fname "${PROJECT_SOURCE_DIR}/sources.cmake")
    if(NOT EXISTS "${_tmp_fname}")
        set(_tmp_fname "${PROJECT_UBINOS_DIR}/resource/ubinos/dummy/sources.cmake")
    endif()
    include(${_tmp_fname})
    if(PROJECT_SOURCES)
        add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
        set(PROJECT_LIBRARIES ${PROJECT_NAME} ${PROJECT_LIBRARIES})
    endif()

    if(INCLUDE__APP)
        ___project_add_app()
    endif()
    
    if(NOT ${UBINOS__BSP__DOXYGEN_FILE} STREQUAL "")
        file(COPY ${UBINOS__BSP__DOXYGEN_FILE}
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    
    if(CMAKE_VERBOSE_MAKEFILE)
        ___project_show()
    endif(CMAKE_VERBOSE_MAKEFILE)
endmacro(project_end)


