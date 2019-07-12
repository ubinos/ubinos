set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD                                      "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_flash_load_trace.cmm"        PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET                                     "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/t32_flash_reset_trace.cmm"       PATH)

set_cache(UBINOS__BSP__NRF52_ENABLE_TRACE                                       TRUE    BOOL)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52dk_baremetal.cmake)


