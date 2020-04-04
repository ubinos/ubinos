set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN 0x08000000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH 0x001C0000 STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN 0x081C0000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH 0x00040000 STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN 0x20020000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH 0x0005C000 STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN 0x2007C000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH 0x00000200 STRING)

set_cache(UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN 0x2007C200 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH 0x00003E00 STRING)

set_cache(UBINOS__BSP__LINKSCRIPT_FILE "${PROJECT_UBINOS_DIR}/source/ubinos/bsp/arch/arm/cortexm/stm32f769/i/flash_ethernet_aws.ld" PATH)

set_cache(UBINOS__BSP__STACK_SIZE 0x00002000 STRING)

set_cache(UBINOS__BSP__STM32_ENABLE_ETHERNET TRUE BOOL)

include(${CMAKE_CURRENT_LIST_DIR}/stm32f769idisco.cmake)

