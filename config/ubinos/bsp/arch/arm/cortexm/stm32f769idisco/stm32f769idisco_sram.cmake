set_cache(UBINOS__BSP__BOARD_MODEL                                                "STM32F769IDISCO"  STRING)

set_cache(UBINOS__BSP__OPENOCD_CONFIG_FILE                                        "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/stm32f769idisco/openocd.cfg"          PATH)

set_cache(STM32CUBEF7__BOARD_NAME                                                 "STM32F769I_DISCO" STRING)

include(${CMAKE_CURRENT_LIST_DIR}/../stm32f769ieval/stm32f769ieval_sram.cmake)

