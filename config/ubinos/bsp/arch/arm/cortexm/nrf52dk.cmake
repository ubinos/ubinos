set_cache(UBINOS__BSP__CPU_TYPE                                                  "CORTEX_M4"     STRING)
set_cache(UBINOS__BSP__CPU_ARMTHUMBSTATE                                         "THUMB"         STRING)
set_cache(UBINOS__BSP__CPU_MODEL                                                 "NRF52832XXAA"  STRING)

set_cache(UBINOS__BSP__BOARD_MODEL                                               "NRF52DK"       STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_TYPE                                          "FLASH"         STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN                                   0x00000000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH                                   0x00080000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN                                     0x20000000     STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH                                     0x00010000     STRING)

set_cache(UBINOS__BSP__USE_ICACHE                                                 TRUE            BOOL)

set_cache(UBINOS__BSP__CLOCK_FREQ_MAIN                                            64000           STRING)
set_cache(UBINOS__BSP__CLOCK_FREQ_SLOW                                            32              STRING)
set_cache(UBINOS__BSP__BUSYWAITCOUNT_PER_MS                                       21200           STRING)

set_cache(UBINOS__BSP__STACK_SIZE                                                 0x800           STRING)

set_cache(UBINOS__BSP__LINKSCRIPT_FILE                                            "${PROJECT_UBINOS_DIR}/source/ubinos/bsp/arch/arm/cortexm/nrf52/xxaa/flash.ld"                 PATH)

set_cache(UBINOS__BSP__FLASH_WRITER_FILE                                          "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/nrf51.bin"                 PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_load.gdb"                PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET                                       "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/gdb_flash_reset.gdb"               PATH)

set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_flash_load.cmm"        PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET                                       "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_flash_reset.cmm"       PATH)

include(${CMAKE_CURRENT_LIST_DIR}/../../arm.cmake)

