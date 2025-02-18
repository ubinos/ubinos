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
    if(${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "OPENOCD")
        set(__tmp_dserver_cmd ${UBINOS__BSP__DEBUG_SERVER_COMMAND} -f ${CMAKE_CURRENT_BINARY_DIR}/openocd.cfg)
    endif()

    execute_process(COMMAND ${PROJECT_TOOLBOX_RUN_CMD} system_name OUTPUT_VARIABLE __tmp_system_name)

    if(${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "OPENOCD")
        if(NOT ${UBINOS__BSP__DEBUG_SERVER_PORT} STREQUAL "")
            set(_tmp_debug_port "${UBINOS__BSP__DEBUG_SERVER_PORT}")
        else()
            set(_tmp_debug_port "2331")
        endif()
        math(EXPR _tmp_tcl_port "${_tmp_debug_port} + 3")
        math(EXPR _tmp_telnet_port "${_tmp_debug_port} + 6")

        set(__tmp_dserver_params
            "-c" "\"gdb_port" "${_tmp_debug_port}\""
            "-c" "\"tcl_port" "${_tmp_tcl_port}\""
            "-c" "\"telnet_port" "${_tmp_telnet_port}\""
        )
        if (${__tmp_system_name} MATCHES "Darwin")
            set(__tmp_dserver_params_with_start_cmd
                "-c" "\\\"gdb_port" "${_tmp_debug_port}\\\""
                "-c" "\\\"tcl_port" "${_tmp_tcl_port}\\\""
                "-c" "\\\"telnet_port" "${_tmp_telnet_port}\\\""
            )
        else()
            set(__tmp_dserver_params_with_start_cmd ${__tmp_dserver_params})
        endif()
        if(NOT ${UBINOS__BSP__DEBUG_SERVER_SERIAL} STREQUAL "")
            set(__tmp_dserver_params ${__tmp_dserver_params}
                "-c" "\"hla_serial" "${UBINOS__BSP__DEBUG_SERVER_SERIAL}\""
            )
            if (${__tmp_system_name} MATCHES "Darwin")
                set(__tmp_dserver_params_with_start_cmd ${__tmp_dserver_params_with_start_cmd}
                    "-c" "\\\"hla_serial" "${UBINOS__BSP__DEBUG_SERVER_SERIAL}\\\""
                )
            else()
                set(__tmp_dserver_params_with_start_cmd ${__tmp_dserver_params})
            endif()
        endif()

        add_custom_target(dserver
            COMMAND ${__tmp_dserver_cmd} ${__tmp_dserver_params}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
        )

        if (${__tmp_system_name} MATCHES "Linux")
            add_custom_target(xdserver
                COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd} &
                COMMAND sleep 1
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
        else()
            add_custom_target(xdserver
                COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
        endif()

        set(UBINOS__BSP__CMD_DSERVER ${__tmp_dserver_cmd} ${__tmp_dserver_params})
        set(UBINOS__BSP__CMD_XDSERVER ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd})
    elseif(${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "JLINK")
        if(NOT ${UBINOS__BSP__DEBUG_SERVER_PORT} STREQUAL "")
            set(_tmp_debug_port "${UBINOS__BSP__DEBUG_SERVER_PORT}")
        else()
            set(_tmp_debug_port "2331")
        endif()
        math(EXPR _tmp_swo_port "${_tmp_debug_port} + 3")
        math(EXPR _tmp_telnet_port "${_tmp_debug_port} + 6")

        set(_tmp_device_model "")
        if(${UBINOS__BSP__CPU_MODEL} STREQUAL "NRF52832XXAA")
            set(_tmp_device_model "nRF52832_xxAA")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "NRF52840XXAA")
            set(_tmp_device_model "nRF52840_xxAA")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32F217IG")
            set(_tmp_device_model "STM32F217IG")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32F207ZG")
            set(_tmp_device_model "STM32F207ZG")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32L476ZG")
            set(_tmp_device_model "STM32L476ZG")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32L476RG")
            set(_tmp_device_model "STM32L476RG")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32L475VG")
            set(_tmp_device_model "STM32L475VG")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32F769NI")
            set(_tmp_device_model "STM32F769NI")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32F429NI")
            set(_tmp_device_model "STM32F429NI")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "STM32F429ZI")
            set(_tmp_device_model "STM32F429ZI")
        elseif(${UBINOS__BSP__CPU_MODEL} STREQUAL "SAM9XE512")
            set(_tmp_device_model "AT91SAM9XE512")
        endif()

        if(NOT ${_tmp_device_model} STREQUAL "")
            if(NOT ${UBINOS__BSP__DEBUG_SERVER_SERIAL} STREQUAL "")
                set(__tmp_dserver_params
                    "-select" "USB=${UBINOS__BSP__DEBUG_SERVER_SERIAL}"
                )
            else()
                set(__tmp_dserver_params
                    "-select" "USB"
                )
            endif()
            set(__tmp_dserver_params ${__tmp_dserver_params}
                    "-device" "${_tmp_device_model}"
                    "-port"  "${_tmp_debug_port}"
                    "-swoport"  "${_tmp_swo_port}"
                    "-telnetport"  "${_tmp_telnet_port}"
                    "-endian" "little"
            )
            if(${UBINOS__BSP__DEBUG_SERVER_TARGET_INTERFACE} STREQUAL "JTAG")
                set(__tmp_dserver_params ${__tmp_dserver_params}
                    "-if" "JTAG"
                )
            else()
                set(__tmp_dserver_params ${__tmp_dserver_params}
                    "-if" "SWD"
                )
            endif()
            set(__tmp_dserver_params ${__tmp_dserver_params}
                    "-speed" "auto"
                    "-ir"
                    "-LocalhostOnly"
            )
            set(__tmp_dserver_params_with_start_cmd ${__tmp_dserver_params})

            add_custom_target(dserver
                COMMAND ${__tmp_dserver_cmd} ${__tmp_dserver_params}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )

            if (${__tmp_system_name} MATCHES "Linux")
                add_custom_target(xdserver
                    COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd} &
                    COMMAND sleep 1
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    USES_TERMINAL
                )
            else()
                add_custom_target(xdserver
                    COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    USES_TERMINAL
                )
            endif()

            set(UBINOS__BSP__CMD_DSERVER ${__tmp_dserver_cmd} ${__tmp_dserver_params})
            set(UBINOS__BSP__CMD_XDSERVER ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd})
        else()
            add_custom_target(dserver
                COMMAND  "echo" "not supported device model"
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
            add_custom_target(xdserver
                COMMAND  "echo" "not supported device model"
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
        endif()
    elseif(${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "QEMU")
        add_custom_target(dserver
            COMMAND  "echo" "not needed"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
        )
        add_custom_target(xdserver
            COMMAND  "echo" "not needed"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
        )
    else()
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
    endif()
    add_custom_target(reset
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_reset.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )

    if(${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "QEMU")
        if(NOT ${UBINOS__BSP__DEBUG_SERVER_PORT} STREQUAL "")
            set(_tmp_debug_port "${UBINOS__BSP__DEBUG_SERVER_PORT}")
        else()
            set(_tmp_debug_port "2331")
        endif()
        set(__tmp_dserver_params_with_start_cmd
            "-gdb" "tcp::${_tmp_debug_port}"
            "-kernel" "app${CMAKE_EXECUTABLE_SUFFIX}"
        )

        if (${__tmp_system_name} MATCHES "Linux")
            add_custom_target(load
                COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd} &
                COMMAND sleep 1
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
        else()
            add_custom_target(load
                COMMAND ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                USES_TERMINAL
            )
        endif()

        set(UBINOS__BSP__CMD_LOAD ${__tmp_start_cmd} ${__tmp_dserver_cmd} ${__tmp_dserver_params_with_start_cmd})
    else()
        add_custom_target(load
            COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_load.gdb
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
        )
        set(UBINOS__BSP__CMD_LOAD ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -batch -x ./gdb_load.gdb)
    endif()

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
