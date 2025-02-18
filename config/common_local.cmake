
macro(___project_add_app__set_link_flags)
    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_EXE_NAME}.map,--cref")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u main")
    elseif(PROJECT_TOOLCHAIN_TYPE STREQUAL "LLVM")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-map,${PROJECT_EXE_NAME}.map")
    else()
        message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_TYPE")
    endif()
endmacro(___project_add_app__set_link_flags)

macro(___project_add_app__gen_linkscript)
endmacro(___project_add_app__gen_linkscript)

macro(___project_add_app__gen_debugscript)
endmacro(___project_add_app__gen_debugscript)

macro(___project_add_app__gen_make_target)

    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        target_link_libraries(${PROJECT_EXE_NAME} ${PROJECT_LIBRARIES})
    elseif(PROJECT_TOOLCHAIN_TYPE STREQUAL "LLVM")
        target_link_libraries(${PROJECT_EXE_NAME} ${PROJECT_LIBRARIES})
    else()
        message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_TYPE")
    endif()

    execute_process(COMMAND ${PROJECT_TOOLBOX_RUN_CMD} get_start_command_for_cmake OUTPUT_VARIABLE __tmp_start_cmd)
    string(STRIP "${__tmp_start_cmd}" __tmp_start_cmd)
    separate_arguments(__tmp_start_cmd)

    set(__tmp_dserver_cmd ${UBINOS__BSP__DEBUG_SERVER_COMMAND})
    string(STRIP "${__tmp_dserver_cmd}" __tmp_dserver_cmd)
    separate_arguments(__tmp_dserver_cmd)

    execute_process(COMMAND ${PROJECT_TOOLBOX_RUN_CMD} system_name OUTPUT_VARIABLE __tmp_system_name)

    add_custom_target(dserver
        COMMAND  "echo" "not supported debug server type"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(xdserver
        COMMAND  "echo" "not supported debug server type"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )

    add_custom_target(reset
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_reset.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )

    add_custom_target(load
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_load.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    set(UBINOS__BSP__CMD_LOAD ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_load.gdb)

    add_custom_target(run
        COMMAND ./app
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(xrun
        COMMAND ${__tmp_start_cmd} ./app
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )

    add_custom_target(debug
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_debug.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(xdebug
        COMMAND ${__tmp_start_cmd} ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_debug.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(attach
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_attach.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(xattach
        COMMAND ${__tmp_start_cmd} ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_attach.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
endmacro(___project_add_app__gen_make_target)

macro(___project_add_app__gen_binary)
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -d -l
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX} > ${PROJECT_EXE_NAME}.s
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -t
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX} > ${PROJECT_EXE_NAME}.syms.s
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -s -j ${PROJECT_TOOLCHAIN_DATA_SECTION_NAME}
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX} > ${PROJECT_EXE_NAME}.data.txt
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove -f
        ${PROJECT_EXE_NAME}.data${CMAKE_EXECUTABLE_SUFFIX}
    )
endmacro(___project_add_app__gen_binary)

macro(___project_add_app__refine_debugscript)
endmacro(___project_add_app__refine_debugscript)

macro(___project_add_app__copy_to_default)
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        ../Default/
    )

    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.s
        ../Default/
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.syms.s
        ../Default/
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.data.txt
        ../Default/
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.map
        ../Default/
    )

    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        compile_commands.json
        ../Default/
    )
endmacro(___project_add_app__copy_to_default)

macro(___project_add_app__show_result)
    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} show_mapfile_info
            ${PROJECT_EXE_NAME}.map
            local_gcc
        )
    elseif(PROJECT_TOOLCHAIN_TYPE STREQUAL "LLVM")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} show_mapfile_info
            ${PROJECT_EXE_NAME}.map
            local_llvm
        )
    else()
        message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_TYPE")
    endif()
endmacro(___project_add_app__show_result)

