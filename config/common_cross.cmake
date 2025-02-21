
macro(___project_add_app__set_link_flags)
    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_EXE_NAME}.map,--cref")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${PROJECT_BINARY_DIR}/linkscript.ld\"")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u main")
    else()
        message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_TYPE")
    endif()
endmacro(___project_add_app__set_link_flags)

macro(___project_add_app__gen_linkscript)
    if(NOT ${UBINOS__BSP__LINKSCRIPT_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__LINKSCRIPT_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH2"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH3"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH3_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH3_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH4"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH4_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH4_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH5"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH5_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH5_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH6"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH6_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH6_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH7"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH7_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH7_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "FLASH8"
            ${UBINOS__BSP__LINK_MEMMAP_FLASH8_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_FLASH8_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM"
            ${UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM2"
            ${UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM3"
            ${UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM4"
            ${UBINOS__BSP__LINK_MEMMAP_RAM4_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM4_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM5"
            ${UBINOS__BSP__LINK_MEMMAP_RAM5_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM5_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM6"
            ${UBINOS__BSP__LINK_MEMMAP_RAM6_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM6_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM7"
            ${UBINOS__BSP__LINK_MEMMAP_RAM7_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM7_LENGTH}
        )
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_linkscript
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            ${CMAKE_CURRENT_BINARY_DIR}/linkscript.ld
            "RAM8"
            ${UBINOS__BSP__LINK_MEMMAP_RAM8_ORIGIN}
            ${UBINOS__BSP__LINK_MEMMAP_RAM8_LENGTH}
        )
    endif()
endmacro(___project_add_app__gen_linkscript)

macro(___project_add_app__gen_debugscript)
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RESET} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_RESET}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RUN} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_RUN}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_INIT} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_INIT}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_init.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH}
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
        )
    endif()

    if(NOT ${UBINOS__BSP__FLASH_WRITER_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__FLASH_WRITER_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/flash_writer.elf
        )
    endif()

    if(NOT ${UBINOS__BSP__SYS_INIT_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__SYS_INIT_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/sys_init.elf
        )
    endif()

    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__T32SCRIPT_FILE_LOAD}
            ${CMAKE_CURRENT_BINARY_DIR}/t32_load.cmm
        )
    endif()

    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_RESET} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__T32SCRIPT_FILE_RESET}
            ${CMAKE_CURRENT_BINARY_DIR}/t32_reset.cmm
        )
    endif()

    if(NOT ${UBINOS__BSP__NRF52_SOFTDEVICE_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__NRF52_SOFTDEVICE_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/nrf52_softdevice.hex
        )
    endif()

    if(NOT ${UBINOS__BSP__NRF52_BOOTLOADER_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__NRF52_BOOTLOADER_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/nrf52_bootloader.hex
        )
    endif()

    if((${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "OPENOCD") AND (NOT ${UBINOS__BSP__OPENOCD_CONFIG_FILE} STREQUAL ""))
        add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${UBINOS__BSP__OPENOCD_CONFIG_FILE}
            ${CMAKE_CURRENT_BINARY_DIR}/openocd.cfg
        )
    endif()
endmacro(___project_add_app__gen_debugscript)

macro(___project_add_app__gen_make_target)
    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        target_link_libraries(${PROJECT_EXE_NAME} -Wl,--start-group ${PROJECT_LIBRARIES} -Wl,--end-group)
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
        COMMAND ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_run.gdb
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
    )
    add_custom_target(xrun
        COMMAND ${__tmp_start_cmd} ${PROJECT_TOOLCHAIN_GDB_COMMAND} -q -x ./gdb_run.gdb
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
        COMMAND ${CMAKE_OBJCOPY} -O binary
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        ${PROJECT_EXE_NAME}.bin
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        ${PROJECT_EXE_NAME}.hex
    )

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
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} refine_gdbscript
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
            ${PROJECT_EXE_NAME}.bin
        )
    endif()

    if(NOT ${UBINOS__BSP__DEBUG_SERVER_HOST} STREQUAL "")
        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                "localhost:" "${UBINOS__BSP__DEBUG_SERVER_HOST}:"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                "localhost:" "${UBINOS__BSP__DEBUG_SERVER_HOST}:"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                "localhost:" "${UBINOS__BSP__DEBUG_SERVER_HOST}:"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RESET} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                "localhost:" "${UBINOS__BSP__DEBUG_SERVER_HOST}:"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RUN} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                "localhost:" "${UBINOS__BSP__DEBUG_SERVER_HOST}:"
            )
        endif()
    endif()

    if(NOT ${UBINOS__BSP__DEBUG_SERVER_PORT} STREQUAL "")
        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_ATTACH} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_attach.gdb
                ":2331" ":${UBINOS__BSP__DEBUG_SERVER_PORT}"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_DEBUG} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_debug.gdb
                ":2331" ":${UBINOS__BSP__DEBUG_SERVER_PORT}"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_LOAD} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_load.gdb
                ":2331" ":${UBINOS__BSP__DEBUG_SERVER_PORT}"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RESET} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_reset.gdb
                ":2331" ":${UBINOS__BSP__DEBUG_SERVER_PORT}"
            )
        endif()

        if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_RUN} STREQUAL "")
            add_custom_command(
                TARGET ${PROJECT_EXE_NAME} POST_BUILD
                COMMAND ${PROJECT_TOOLBOX_RUN_CMD} replace_string
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                ${CMAKE_CURRENT_BINARY_DIR}/gdb_run.gdb
                ":2331" ":${UBINOS__BSP__DEBUG_SERVER_PORT}"
            )
        endif()
    endif()
endmacro(___project_add_app__refine_debugscript)

macro(___project_add_app__copy_to_default)
    if(NOT ${UBINOS__BSP__GDBSCRIPT_FILE_INIT} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/gdb_init.gdb
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__FLASH_WRITER_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/flash_writer.elf
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__SYS_INIT_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/sys_init.elf
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__SYS_INIT_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/sys_init.elf
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_LOAD} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/t32_load.cmm
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__T32SCRIPT_FILE_RESET} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/t32_reset.cmm
            ../Default/
        )
    endif()

    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        ../Default/
    )

    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.bin
        ../Default/
    )
    add_custom_command(
        TARGET ${PROJECT_EXE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_EXE_NAME}.hex
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

    if(NOT ${UBINOS__BSP__NRF52_SOFTDEVICE_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            nrf52_softdevice.hex
            ../Default/
        )
    endif()

    if(NOT ${UBINOS__BSP__NRF52_BOOTLOADER_FILE} STREQUAL "")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            nrf52_bootloader.hex
            ../Default/
        )
    endif()

    if((${UBINOS__BSP__DEBUG_SERVER_TYPE} STREQUAL "OPENOCD") AND (NOT ${UBINOS__BSP__OPENOCD_CONFIG_FILE} STREQUAL ""))
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            openocd.cfg
            ../Default/
        )
    endif()
endmacro(___project_add_app__copy_to_default)

macro(___project_add_app__show_result)
    if(PROJECT_TOOLCHAIN_TYPE STREQUAL "GCC")
        add_custom_command(
            TARGET ${PROJECT_EXE_NAME} POST_BUILD
            COMMAND ${PROJECT_TOOLBOX_RUN_CMD} show_mapfile_info
            ${PROJECT_EXE_NAME}.map
            gcc
        )
    else()
        message(FATAL_ERROR "Unsupported PROJECT_TOOLCHAIN_TYPE")
    endif()
endmacro(___project_add_app__show_result)

