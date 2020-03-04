set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN 0x00026000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH 0x000DA000 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN 0x20002400 STRING)
set_cache(UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH 0x0003DC00 STRING)

set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_PRESENT TRUE BOOL)
set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_NAME S140 STRING)
set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_BLE_API_VERSION 6 STRING)

set_cache(UBINOS__BSP__NRF52_SOFTDEVICE_FILE "${PROJECT_LIBRARY_DIR}/nrf5sdk/source/nRF5_SDK/components/softdevice/s140/hex/s140_nrf52_6.1.1_softdevice.hex" PATH)

set_cache(UBINOS__BSP__GDBSCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/gdb_flash_load_softdevice_jlink.gdb" PATH)
set_cache(UBINOS__BSP__GDBSCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52dk/gdb_flash_reset_softdevice.gdb" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_LOAD "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/t32_flash_load_softdevice.cmm" PATH)
set_cache(UBINOS__BSP__T32SCRIPT_FILE_RESET "${PROJECT_UBINOS_DIR}/resource/ubinos/bsp/arch/arm/cortexm/nrf52840dk/t32_flash_reset_softdevice.cmm" PATH)

include(${PROJECT_UBINOS_DIR}/config/ubinos_nrf52840dk.cmake)

