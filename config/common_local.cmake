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
