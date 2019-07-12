set_cache(UBINOS__UBICLIB__USE_MALLOC_RETARGETING                                 TRUE   BOOL)
set_cache(UBINOS__UBICLIB__EXCLUDE_HEAP                                           FALSE  BOOL)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_ALGORITHM                                    "GROUP"     STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_LOCKTYPE                                     "MUTEX"     STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_M                                            4           STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLCOUNT                                     200         STRING)
set_cache(UBINOS__UBICLIB__HEAP_DIR0_FBLBM_BUFSIZE                                32          STRING)

include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain/arch/arm/arm-none-eabi.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/toolchain.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp/arch/arm/classic/sam9xexxxek/sam9xe512ek.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/bsp.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubiclib.cmake)
include(${PROJECT_UBINOS_DIR}/config/ubinos/ubik.cmake)


