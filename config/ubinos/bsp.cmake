set(UBINOS__VERSION_MAJOR 3)
set(UBINOS__VERSION_MINOR 0)
set(UBINOS__VERSION_PATCH 1)
set(UBINOS__VERSION_TWEAK 1)
set(UBINOS__VERSION "${UBINOS__VERSION_MAJOR}.${UBINOS__VERSION_MINOR}.${UBINOS__VERSION_PATCH}-${UBINOS__VERSION_TWEAK}")


########


set(INCLUDE__UBINOS__BSP                                                        TRUE)


set_cache_default(UBINOS__BSP__CPU_ARCH                                         ""      STRING "CPU Architecture [ARM]")
set_cache_default(UBINOS__BSP__CPU_TYPE                                         ""      STRING "CPU Type [ARM7TDMI | ARM926EJ_S | CORTEX_M4]")
set_cache_default(UBINOS__BSP__CPU_ENDIAN                                       ""      STRING "CPU endian [LITTLE | BIG]")
set_cache_default(UBINOS__BSP__CPU_MODEL                                        ""      STRING "CPU model [SAM7X256 | SAM7X512 | SAM9XE512 | NRF52832XXAA]")

set_cache_default(UBINOS__BSP__BOARD_MODEL                                      ""      STRING "Board model [SAM7X256EK | SAM7X512EK | SAM9XE512EK | NRF52DK]")

set_cache_default(UBINOS__BSP__LINK_MEMMAP_TYPE                                 ""      STRING "Link memory map type [FLASH | SRAM | SDRAM | FLASH_SDRAM | SRAM_SDRAM]")

set_cache_default(UBINOS__BSP__USE_MMU                                          FALSE   BOOL "Use MMU")
set_cache_default(UBINOS__BSP__USE_ICACHE                                       FALSE   BOOL "Use i-cache")
set_cache_default(UBINOS__BSP__USE_DCACHE                                       FALSE   BOOL "Use d-cache")

set_cache_default(UBINOS__BSP__CLOCK_FREQ_MAIN                                  0       STRING "Main clock frequency (KHz)")
set_cache_default(UBINOS__BSP__CLOCK_FREQ_SLOW                                  0       STRING "Slow clock frequency (KHz)")
set_cache_default(UBINOS__BSP__BUSYWAITCOUNT_PER_MS                             0       STRING "Busy wait count per millisecond")

set_cache_default(UBINOS__BSP__USE_DTTY                                         TRUE    BOOL "Use dtty (debug tty)")

set_cache_default(UBINOS__BSP__USE_EXTSDRAM                                     FALSE   BOOL "Use external SDRAM")
set_cache_default(UBINOS__BSP__USE_EXTNORFLASH                                  FALSE   BOOL "Use external NOR Flash")

set_cache_default(UBINOS__BSP__EXTSDRAM_BUSWIDTH                                0       STRING "External SDRAM bus width")
set_cache_default(UBINOS__BSP__EXTNORFLASH_BUSWIDTH                             0       STRING "External NORFLASH bus width")
set_cache_default(UBINOS__BSP__EXTNORFLASH_ADDR                                 0       STRING "External NORFLASH address")

set_cache_default(UBINOS__BSP__STACK_SIZE                                       0       STRING "Stack size (ARM cortexm: Master stack size, ARM classic: total stack size of ISR handlers)")
set_cache_default(UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN                      0       STRING "Stack overflow check margin")


if(UBINOS__BSP__CPU_ARCH STREQUAL "ARM")

set_cache_default(UBINOS__BSP__USE_RELOCATED_ISR_VECTOR                         TRUE    BOOL "Use relocated ISR vector")

    if(UBINOS__BSP__CPU_TYPE STREQUAL "ARM926EJ_S")
    
set_cache_default(UBINOS__BSP__CPU_ARMTHUMBSTATE                                ""      STRING "CPU default ARM/THUMB state [ARM | THUMB]")
set_cache_default(UBINOS__BSP__INCLUDE_INTERRUPT_DISABLE_ENABLE_RETRY           TRUE    BOOL "Include interrupt disable enable retry")

    elseif(UBINOS__BSP__CPU_TYPE STREQUAL "CORTEX_M4")
    
    else()
    
        message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_TYPE")
        
    endif()


    if(UBINOS__BSP__CPU_MODEL STREQUAL "SAM9XE512")

    elseif(UBINOS__BSP__CPU_MODEL STREQUAL "NRF52832XXAA")

set_cache_default(UBINOS__BSP__NRF52_NRF52                                      TRUE    BOOL "")
set_cache_default(UBINOS__BSP__NRF52_NRF52832_XXAA                              TRUE    BOOL "")
set_cache_default(UBINOS__BSP__NRF52_NRF52_PAN_74                               TRUE    BOOL "")
set_cache_default(UBINOS__BSP__NRF52_FLOAT_ABI_HARD                             TRUE    BOOL "")

    else()

        message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_MODEL")

    endif()


    if(UBINOS__BSP__BOARD_MODEL STREQUAL "SAM9XE512EK")

    elseif(UBINOS__BSP__BOARD_MODEL STREQUAL "NRF52DK")

set_cache_default(UBINOS__BSP__NRF52_CONFIG_GPIO_AS_PINRESET                    TRUE    BOOL "")
set_cache_default(UBINOS__BSP__NRF52_ENABLE_SWO                                 FALSE   BOOL "")
set_cache_default(UBINOS__BSP__NRF52_ENABLE_TRACE                               FALSE   BOOL "")

    else()

        message(FATAL_ERROR "Unsupported UBINOS__BSP__BOARD_MODEL")

    endif()

else()

    message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_ARCH")

endif()


set_cache_default(UBINOS__BSP__LINKSCRIPT_FILE                                  ""      PATH "Link script file")

set_cache_default(UBINOS__BSP__FLASH_WRITER_FILE                                ""      PATH "Flash writer file")
set_cache_default(UBINOS__BSP__SYS_INIT_FILE                                    ""      PATH "System initiation file")

set_cache_default(UBINOS__BSP__GDBSCRIPT_FILE_ATTACH                            ""      PATH "Gdb script file to attach")
set_cache_default(UBINOS__BSP__GDBSCRIPT_FILE_DEBUG                             ""      PATH "Gdb script file to debug")
set_cache_default(UBINOS__BSP__GDBSCRIPT_FILE_RUN                               ""      PATH "Gdb script file to run")

set_cache_default(UBINOS__BSP__GDBSCRIPT_FILE_LOAD                              ""      PATH "GDB script file to load")
set_cache_default(UBINOS__BSP__GDBSCRIPT_FILE_RESET                             ""      PATH "GDB script file to reset")

set_cache_default(UBINOS__BSP__T32SCRIPT_FILE_LOAD                              ""      PATH "Trace32 script file to load")
set_cache_default(UBINOS__BSP__T32SCRIPT_FILE_RESET                             ""      PATH "Trace32 script file to reset")

set_cache_default(UBINOS__BSP__DOXYGEN_FILE                                     "${PROJECT_UBINOS_DIR}/resource/ubinos/doc/Doxyfile" PATH "Doxygen file")

########


set(_tmp_all_flags "")

if(UBINOS__BSP__CPU_ARCH STREQUAL "ARM")

    if( UBINOS__BSP__CPU_TYPE STREQUAL "ARM926EJ_S")
    
        set(_tmp_all_flags "${_tmp_all_flags} -mcpu=arm926ej-s")
        
    elseif( UBINOS__BSP__CPU_TYPE STREQUAL "CORTEX_M4")
    
        set(_tmp_all_flags "${_tmp_all_flags} -mcpu=cortex-m4")
        
    else()
    
        message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_TYPE")
        
    endif()


    if(UBINOS__BSP__CPU_ENDIAN STREQUAL "LITTLE")
    
        set(_tmp_all_flags "${_tmp_all_flags} -mlittle-endian")
        
    elseif(UBINOS__BSP__CPU_ENDIAN STREQUAL "BIG")
    
        set(_tmp_all_flags "${_tmp_all_flags} -mbig-endian")
        
    else()
    
        message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_ENDIAN")
        
    endif()
    

    if(UBINOS__BSP__CPU_MODEL STREQUAL "SAM9XE512")
    
        if(UBINOS__BSP__CPU_ARMTHUMBSTATE STREQUAL "ARM")
        
            set(_tmp_all_flags "${_tmp_all_flags} -marm")
            
        elseif(UBINOS__BSP__CPU_ARMTHUMBSTATE STREQUAL "THUMB")
        
            set(_tmp_all_flags "${_tmp_all_flags} -mthumb -mthumb-interwork")
            
        else()
        
            message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_ARMTHUMBSTATE")
            
        endif()
        
        set(_tmp_all_flags "${_tmp_all_flags} -msoft-float")
        set(_tmp_all_flags "${_tmp_all_flags} -fomit-frame-pointer")
        
    elseif(UBINOS__BSP__CPU_MODEL STREQUAL "NRF52832XXAA")
    
        set(_tmp_all_flags "${_tmp_all_flags} -mthumb")
        set(_tmp_all_flags "${_tmp_all_flags} -mfloat-abi=hard")
        set(_tmp_all_flags "${_tmp_all_flags} -mfpu=fpv4-sp-d16")
        
        if(UBINOS__BSP__NRF52_NRF52)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DNRF52")
            
        endif()
        
        if(UBINOS__BSP__NRF52_NRF52832_XXAA)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DNRF52832_XXAA")
            
        endif()
        
        if(UBINOS__BSP__NRF52_NRF52_PAN_74)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DNRF52_PAN_74")
            
        endif()
        
        if(UBINOS__BSP__NRF52_FLOAT_ABI_HARD)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DFLOAT_ABI_HARD")
            
        endif()
        
    else()
    
       message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_MODEL")
       
    endif()


    if(UBINOS__BSP__BOARD_MODEL STREQUAL "SAM9XE512EK")
    
    elseif(UBINOS__BSP__BOARD_MODEL STREQUAL "NRF52DK")
    
        if(UBINOS__BSP__NRF52_CONFIG_GPIO_AS_PINRESET)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DCONFIG_GPIO_AS_PINRESET")
            
        endif()
        
        if(UBINOS__BSP__NRF52_ENABLE_SWO)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DENABLE_SWO")
            
        endif()

        if(UBINOS__BSP__NRF52_ENABLE_TRACE)
        
            set(_tmp_all_flags "${_tmp_all_flags} -DENABLE_TRACE")
            
        endif()
        
    else()
    
        message(FATAL_ERROR "Unsupported UBINOS__BSP__BOARD_MODEL")
        
    endif()
    

    set(_tmp_all_flags "${_tmp_all_flags} -D__STACK_SIZE=${UBINOS__BSP__STACK_SIZE}")

    set(_tmp_all_flags "${_tmp_all_flags} -mabi=aapcs")
    set(_tmp_all_flags "${_tmp_all_flags} -ffunction-sections")
    set(_tmp_all_flags "${_tmp_all_flags} -fdata-sections")
    set(_tmp_all_flags "${_tmp_all_flags} -fno-strict-aliasing")
    set(_tmp_all_flags "${_tmp_all_flags} -fno-builtin")
    set(_tmp_all_flags "${_tmp_all_flags} -fshort-enums")
    set(_tmp_all_flags "${_tmp_all_flags} -falign-functions=8")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} gcc)
    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} c)
    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} nosys)
    set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} m)
    
else()

    message(FATAL_ERROR "Unsupported UBINOS__BSP__CPU_ARCH")
    
endif()


set(_tmp_all_flags "${_tmp_all_flags} -g3")
set(_tmp_all_flags "${_tmp_all_flags} -Wall -Werror -fmessage-length=0")

set(CMAKE_ASM_FLAGS "${_tmp_all_flags} ${CMAKE_ASM_FLAGS} -x assembler-with-cpp -D__ASSEMBLY__")
set(CMAKE_C_FLAGS   "${_tmp_all_flags} ${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${_tmp_all_flags} ${CMAKE_CXX_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -u main")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_EXE_NAME}.map,--cref")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${PROJECT_BINARY_DIR}/linkscript.ld\"")


