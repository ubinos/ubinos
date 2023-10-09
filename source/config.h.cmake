////////


#define PROJECT_BUILD_TYPE "@PROJECT_BUILD_TYPE@"


////////


#define UBINOS__VERSION_MAJOR @UBINOS__VERSION_MAJOR@
#define UBINOS__VERSION_MINOR @UBINOS__VERSION_MINOR@
#define UBINOS__VERSION_PATCH @UBINOS__VERSION_PATCH@
#define UBINOS__VERSION_TWEAK @UBINOS__VERSION_TWEAK@
#define UBINOS__VERSION "@UBINOS__VERSION@"


////////


#cmakedefine01 INCLUDE__UBINOS__BSP

#if (INCLUDE__UBINOS__BSP == 1)

#define UBINOS__BSP__CPU_ARCH__LOCAL                      1
#define UBINOS__BSP__CPU_ARCH__ARM                        2
#define UBINOS__BSP__CPU_ARCH                             UBINOS__BSP__CPU_ARCH__@UBINOS__BSP__CPU_ARCH@

#define UBINOS__BSP__CPU_TYPE__LOCAL                      1
#define UBINOS__BSP__CPU_TYPE__ARM926EJ_S                 2
#define UBINOS__BSP__CPU_TYPE__CORTEX_M0                  10
#define UBINOS__BSP__CPU_TYPE__CORTEX_M3                  13
#define UBINOS__BSP__CPU_TYPE__CORTEX_M4                  14
#define UBINOS__BSP__CPU_TYPE__CORTEX_M7                  17
#define UBINOS__BSP__CPU_TYPE                             UBINOS__BSP__CPU_TYPE__@UBINOS__BSP__CPU_TYPE@

#cmakedefine01 UBINOS__BSP__CORTEX_MX

#define UBINOS__BSP__CPU_ENDIAN__LITTLE                   1
#define UBINOS__BSP__CPU_ENDIAN__BIG                      2
#define UBINOS__BSP__CPU_ENDIAN                           UBINOS__BSP__CPU_ENDIAN__@UBINOS__BSP__CPU_ENDIAN@

#define UBINOS__BSP__CPU_MODEL__LOCAL                     0x00010100
#define UBINOS__BSP__CPU_MODEL__SAM9XE512                 0x00010223
#define UBINOS__BSP__CPU_MODEL__NRF52832XXAA              0x00010311
#define UBINOS__BSP__CPU_MODEL__NRF52840XXAA              0x00010321
#define UBINOS__BSP__CPU_MODEL__STM32F100XB               0x00010401
#define UBINOS__BSP__CPU_MODEL__STM32F217IG               0x00010411
#define UBINOS__BSP__CPU_MODEL__STM32F207ZG               0x00010421
#define UBINOS__BSP__CPU_MODEL__STM32F429NI               0x00010431
#define UBINOS__BSP__CPU_MODEL__STM32F429ZI               0x00010441
#define UBINOS__BSP__CPU_MODEL__STM32F405RG               0x00010451
#define UBINOS__BSP__CPU_MODEL__STM32L475VG               0x00010521
#define UBINOS__BSP__CPU_MODEL__STM32L476ZG               0x00010531
#define UBINOS__BSP__CPU_MODEL__STM32L476RG               0x00010532
#define UBINOS__BSP__CPU_MODEL__STM32F769NI               0x00010711
#define UBINOS__BSP__CPU_MODEL__STM32H747XI               0x00010811
#define UBINOS__BSP__CPU_MODEL                            UBINOS__BSP__CPU_MODEL__@UBINOS__BSP__CPU_MODEL@

#cmakedefine01 UBINOS__BSP__NRF52_NRF52XXX

#cmakedefine01 UBINOS__BSP__STM32_STM32XXXX

#cmakedefine01 UBINOS__BSP__STM32_STM32F1XX
#cmakedefine01 UBINOS__BSP__STM32_STM32F100

#cmakedefine01 UBINOS__BSP__STM32_STM32F2XX
#cmakedefine01 UBINOS__BSP__STM32_STM32F2X7

#cmakedefine01 UBINOS__BSP__STM32_STM32F4XX
#cmakedefine01 UBINOS__BSP__STM32_STM32F429
#cmakedefine01 UBINOS__BSP__STM32_STM32F405

#cmakedefine01 UBINOS__BSP__STM32_STM32L4XX
#cmakedefine01 UBINOS__BSP__STM32_STM32L475
#cmakedefine01 UBINOS__BSP__STM32_STM32L476

#cmakedefine01 UBINOS__BSP__STM32_STM32F7XX
#cmakedefine01 UBINOS__BSP__STM32_STM32F769

#cmakedefine01 UBINOS__BSP__STM32_STM32H7XX
#cmakedefine01 UBINOS__BSP__STM32_STM32H747

#define UBINOS__BSP__BOARD_MODEL__LOCAL                   0x00020100
#define UBINOS__BSP__BOARD_MODEL__SAM9XE512EK             0x00020223
#define UBINOS__BSP__BOARD_MODEL__NRF52DK                 0x00020311
#define UBINOS__BSP__BOARD_MODEL__NRF52840DK              0x00020321
#define UBINOS__BSP__BOARD_MODEL__NRF52840DONGLE          0x00020322
#define UBINOS__BSP__BOARD_MODEL__ARDUINONANO33BLE        0x00020323
#define UBINOS__BSP__BOARD_MODEL__STM32VLDISCO            0x00020401
#define UBINOS__BSP__BOARD_MODEL__STM3221GEVAL            0x00020411
#define UBINOS__BSP__BOARD_MODEL__NUCLEOF207ZG            0x00020421
#define UBINOS__BSP__BOARD_MODEL__STM32429IEVAL           0x00020431
#define UBINOS__BSP__BOARD_MODEL__STM32F429IDISCO         0x00020441
#define UBINOS__BSP__BOARD_MODEL__NETDUINOPLUS2           0x00020451
#define UBINOS__BSP__BOARD_MODEL__STM32L475EIOT01         0x00020521
#define UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL          0x00020531
#define UBINOS__BSP__BOARD_MODEL__NUCLEOL476RG            0x00020532
#define UBINOS__BSP__BOARD_MODEL__STM32F769IEVAL          0x00020711
#define UBINOS__BSP__BOARD_MODEL__STM32F769IDISCO         0x00020721
#define UBINOS__BSP__BOARD_MODEL__STM32H747IDISCO         0x00020821
#define UBINOS__BSP__BOARD_MODEL                          UBINOS__BSP__BOARD_MODEL__@UBINOS__BSP__BOARD_MODEL@

#define UBINOS__BSP__BOARD_REVISION_NO @UBINOS__BSP__BOARD_REVISION_NO@

#define UBINOS__BSP__BOARD_VARIATION_NAME "@UBINOS__BSP__BOARD_VARIATION_NAME@"

#define UBINOS__BSP__BOARD_VARIATION__@UBINOS__BSP__BOARD_VARIATION_NAME@ 1

#define UBINOS__BSP__LINK_MEMMAP_TYPE__FLASH              1
#define UBINOS__BSP__LINK_MEMMAP_TYPE__SRAM               2
#define UBINOS__BSP__LINK_MEMMAP_TYPE__FLASH_EXTSRAM      3
#define UBINOS__BSP__LINK_MEMMAP_TYPE__FLASH_EXTSDRAM     4
#define UBINOS__BSP__LINK_MEMMAP_TYPE__EXTFLASH_EXTSDRAM  5
#define UBINOS__BSP__LINK_MEMMAP_TYPE                     UBINOS__BSP__LINK_MEMMAP_TYPE__@UBINOS__BSP__LINK_MEMMAP_TYPE@

#define UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN             @UBINOS__BSP__LINK_MEMMAP_FLASH_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH             @UBINOS__BSP__LINK_MEMMAP_FLASH_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH2_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH2_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH3_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH3_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH3_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH3_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH4_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH4_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH4_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH4_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH5_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH5_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH5_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH5_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH6_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH6_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH6_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH6_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH7_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH7_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH7_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH7_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_FLASH8_ORIGIN            @UBINOS__BSP__LINK_MEMMAP_FLASH8_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_FLASH8_LENGTH            @UBINOS__BSP__LINK_MEMMAP_FLASH8_LENGTH@

#define UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN               @UBINOS__BSP__LINK_MEMMAP_RAM_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH               @UBINOS__BSP__LINK_MEMMAP_RAM_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM2_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM2_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM3_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM3_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM4_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM4_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM4_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM4_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM5_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM5_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM5_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM5_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM6_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM6_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM6_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM6_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM7_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM7_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM7_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM7_LENGTH@
#define UBINOS__BSP__LINK_MEMMAP_RAM8_ORIGIN              @UBINOS__BSP__LINK_MEMMAP_RAM8_ORIGIN@
#define UBINOS__BSP__LINK_MEMMAP_RAM8_LENGTH              @UBINOS__BSP__LINK_MEMMAP_RAM8_LENGTH@

#cmakedefine01 UBINOS__BSP__USE_MMU
#cmakedefine01 UBINOS__BSP__USE_ICACHE
#cmakedefine01 UBINOS__BSP__USE_DCACHE

#cmakedefine01 UBINOS__BSP__USE_DTTY

#define UBINOS__BSP__DTTY_TYPE__UART                      1
#define UBINOS__BSP__DTTY_TYPE__EXTERNAL                  2
#define UBINOS__BSP__DTTY_TYPE                            UBINOS__BSP__DTTY_TYPE__@UBINOS__BSP__DTTY_TYPE@

#define UBINOS__BSP__CLOCK_FREQ_MAIN                      @UBINOS__BSP__CLOCK_FREQ_MAIN@
#define UBINOS__BSP__CLOCK_FREQ_SLOW                      @UBINOS__BSP__CLOCK_FREQ_SLOW@
#define UBINOS__BSP__BUSYWAITCOUNT_PER_MS                 @UBINOS__BSP__BUSYWAITCOUNT_PER_MS@

#cmakedefine01 UBINOS__BSP__USE_EXTSRAM
#cmakedefine01 UBINOS__BSP__USE_EXTSDRAM
#cmakedefine01 UBINOS__BSP__USE_EXTNORFLASH

#define UBINOS__BSP__EXTSDRAM_BUSWIDTH                    @UBINOS__BSP__EXTSDRAM_BUSWIDTH@
#define UBINOS__BSP__EXTNORFLASH_BUSWIDTH                 @UBINOS__BSP__EXTNORFLASH_BUSWIDTH@
#define UBINOS__BSP__EXTNORFLASH_ADDR                     @UBINOS__BSP__EXTNORFLASH_ADDR@

#define UBINOS__BSP__STACK_SIZE                           @UBINOS__BSP__STACK_SIZE@
#define UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN          @UBINOS__BSP__STACK_OVERFLOW_CHECK_MARGIN@

#cmakedefine01 UBINOS__BSP__EXCLUDE_ARCH_INIT

#cmakedefine01 UBINOS__BSP__USE_QEMU

#cmakedefine01 UBINOS__BSP__USE_CRITCOUNT_IN_ISR_CHECK

#define UBINOS__BSP__ABORTSYSTEM_TYPE__STOP               1
#define UBINOS__BSP__ABORTSYSTEM_TYPE__RESET              2
#define UBINOS__BSP__ABORTSYSTEM_TYPE                     UBINOS__BSP__ABORTSYSTEM_TYPE__@UBINOS__BSP__ABORTSYSTEM_TYPE@


////


#if (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__ARM)

#cmakedefine01 UBINOS__BSP__USE_RELOCATED_ISR_VECTOR

    #if (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__ARM926EJ_S)

#define UBINOS__BSP__CPU_ARMTHUMBSTATE__ARM               1
#define UBINOS__BSP__CPU_ARMTHUMBSTATE__THUMB             2
#define UBINOS__BSP__CPU_ARMTHUMBSTATE                    UBINOS__BSP__CPU_ARMTHUMBSTATE__@UBINOS__BSP__CPU_ARMTHUMBSTATE@

#cmakedefine01 UBINOS__BSP__INCLUDE_INTERRUPT_DISABLE_ENABLE_RETRY

    #elif (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__CORTEX_M3)

    #elif (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__CORTEX_M4)

    #elif (UBINOS__BSP__CPU_TYPE == UBINOS__BSP__CPU_TYPE__CORTEX_M7)

    #else

        #error "Unsupported UBINOS__BSP__CPU_TYPE"

    #endif /* (UBINOS__BSP__CPU_TYPE == ...) */


    #if (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__SAM9XE512)

    #elif ((UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA))

        #if (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52832XXAA)

#cmakedefine01 UBINOS__BSP__NRF52_NRF52
#cmakedefine01 UBINOS__BSP__NRF52_NRF52832_XXAA
#cmakedefine01 UBINOS__BSP__NRF52_NRF52_PAN_74

        #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__NRF52840XXAA)

#cmakedefine01 UBINOS__BSP__NRF52_NRF52840_XXAA

        #else

            #error "Unsupported UBINOS__BSP__CPU_MODEL"

        #endif /* (UBINOS__BSP__CPU_MODEL == ...) */

#cmakedefine01 UBINOS__BSP__USE_SOFTFLOAT
#cmakedefine01 UBINOS__BSP__NRF52_SOFTDEVICE_PRESENT
#define UBINOS__BSP__NRF52_SOFTDEVICE_NAME                "@UBINOS__BSP__NRF52_SOFTDEVICE_NAME@"
#define UBINOS__BSP__NRF52_SOFTDEVICE_BLE_API_VERSION     @UBINOS__BSP__NRF52_SOFTDEVICE_BLE_API_VERSION@

#cmakedefine01 UBINOS__BSP__NRF52_MBR_PRESENT

#cmakedefine01 UBINOS__BSP__NRF52_IGNORE_HARDFAULT_EXCEPTION_FROM_SOFTDEVICE

    #elif ((UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F217IG) || (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F207ZG))

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F100XB)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F405RG)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F429NI)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F429ZI)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32L475VG)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32L476ZG)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32L476RG)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32F769NI)

    #elif (UBINOS__BSP__CPU_MODEL == UBINOS__BSP__CPU_MODEL__STM32H747XI)

    #else

        #error "Unsupported UBINOS__BSP__CPU_MODEL"

    #endif /* (UBINOS__BSP__CPU_MODEL == ...) */


    #if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__SAM9XE512EK)

    #elif (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32VLDISCO)

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DK) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NRF52840DONGLE) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__ARDUINONANO33BLE))

#cmakedefine01 UBINOS__BSP__NRF52_CONFIG_GPIO_AS_PINRESET
#cmakedefine01 UBINOS__BSP__NRF52_ENABLE_SWO
#cmakedefine01 UBINOS__BSP__NRF52_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM3221GEVAL) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOF207ZG))

#define UBINOS__BSP__STM32_RCC_HSE_CONFIG__OFF     0
#define UBINOS__BSP__STM32_RCC_HSE_CONFIG__ON      1
#define UBINOS__BSP__STM32_RCC_HSE_CONFIG__BYPASS  2
#define UBINOS__BSP__STM32_RCC_HSE_CONFIG          UBINOS__BSP__STM32_RCC_HSE_CONFIG__@UBINOS__BSP__STM32_RCC_HSE_CONFIG@

#define UBINOS__BSP__STM32_HSE_VALUE @UBINOS__BSP__STM32_HSE_VALUE@

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NETDUINOPLUS2))

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32429IEVAL) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32F429IDISCO))

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__NUCLEOL476RG) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L475EIOT01))

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#define UBINOS__BSP__STM32_RCC_TYPE__HSE            1
#define UBINOS__BSP__STM32_RCC_TYPE__MSI            2
#define UBINOS__BSP__STM32_RCC_TYPE__LSE_MSI        3
#define UBINOS__BSP__STM32_RCC_TYPE                 UBINOS__BSP__STM32_RCC_TYPE__@UBINOS__BSP__STM32_RCC_TYPE@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32F769IEVAL) || (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32F769IDISCO))

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_ETHERNET

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #elif ((UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32H747IDISCO))

#define UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER @UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER@

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_ETHERNET

#cmakedefine01 UBINOS__BSP__STM32_ENABLE_TRACE

    #else

        #error "Unsupported UBINOS__BSP__BOARD_MODEL"

    #endif /* (UBINOS__BSP__BOARD_MODEL == ...) */

#elif (UBINOS__BSP__CPU_ARCH == UBINOS__BSP__CPU_ARCH__LOCAL)



#else

    #error "Unsupported UBINOS__BSP__CPU_ARCH"

#endif /* (UBINOS__BSP__CPU_ARCH == ... */

#endif /* (INCLUDE__UBINOS__BSP == 1) */


////////


#cmakedefine01 INCLUDE__UBINOS__UBICLIB

#if (INCLUDE__UBINOS__UBICLIB == 1)

#cmakedefine01 UBINOS__UBICLIB__NOSTDLIB

#cmakedefine01 UBINOS__UBICLIB__USE_MALLOC_RETARGETING

#cmakedefine01 UBINOS__UBICLIB__USE_STDIO_RETARGETING

#cmakedefine01 UBINOS__UBICLIB__USE_DUMMY_MKDIR

#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_ARCH_INIT

#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_LOGM
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_CLI

#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_LIST
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_DLIST
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_CIRBUF
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_CBUF
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_BITMAP
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_MATH_EXT

#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_BOUNDARY_CHECK
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_INTERMEDIATE_DATA_CHECK
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_FLAG
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_DIR_ON_OFF
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_DMPM_MEMORY_READY_CHECK
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_LOGMD
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_PRINTHEAPINFO
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BESTFIT
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__FIRSTFIT
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__NEXTFIT
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__PGROUP
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__BBUDDY
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__GROUP
#cmakedefine01 UBINOS__UBICLIB__EXCLUDE_HEAP_ALGORITHM__WBUDDY

#define UBINOS__UBICLIB__HEAP_ALGORITHM__BESTFIT                         1
#define UBINOS__UBICLIB__HEAP_ALGORITHM__FIRSTFIT                        2
#define UBINOS__UBICLIB__HEAP_ALGORITHM__NEXTFIT                         3
#define UBINOS__UBICLIB__HEAP_ALGORITHM__BBUDDY                          4
#define UBINOS__UBICLIB__HEAP_ALGORITHM__WBUDDY                          5
#define UBINOS__UBICLIB__HEAP_ALGORITHM__PGROUP                          6
#define UBINOS__UBICLIB__HEAP_ALGORITHM__GROUP                           7

#define UBINOS__UBICLIB__HEAP_LOCK_TYPE__NONE                            1
#define UBINOS__UBICLIB__HEAP_LOCK_TYPE__MUTEX                           2
#define UBINOS__UBICLIB__HEAP_LOCK_TYPE__CRITICAL                        3

#define UBINOS__UBICLIB__HEAP_DIR0_ALGORITHM              UBINOS__UBICLIB__HEAP_ALGORITHM__@UBINOS__UBICLIB__HEAP_DIR0_ALGORITHM@
#define UBINOS__UBICLIB__HEAP_DIR0_LOCKTYPE               UBINOS__UBICLIB__HEAP_LOCK_TYPE__@UBINOS__UBICLIB__HEAP_DIR0_LOCKTYPE@
#define UBINOS__UBICLIB__HEAP_DIR0_M                      @UBINOS__UBICLIB__HEAP_DIR0_M@
#define UBINOS__UBICLIB__HEAP_DIR0_FBLCOUNT               @UBINOS__UBICLIB__HEAP_DIR0_FBLCOUNT@
#define UBINOS__UBICLIB__HEAP_DIR0_FBLBM_BUFSIZE          @UBINOS__UBICLIB__HEAP_DIR0_FBLBM_BUFSIZE@

#define UBINOS__UBICLIB__HEAP_DIR1_ALGORITHM              UBINOS__UBICLIB__HEAP_ALGORITHM__@UBINOS__UBICLIB__HEAP_DIR1_ALGORITHM@
#define UBINOS__UBICLIB__HEAP_DIR1_LOCKTYPE               UBINOS__UBICLIB__HEAP_LOCK_TYPE__@UBINOS__UBICLIB__HEAP_DIR1_LOCKTYPE@
#define UBINOS__UBICLIB__HEAP_DIR1_M                      @UBINOS__UBICLIB__HEAP_DIR1_M@
#define UBINOS__UBICLIB__HEAP_DIR1_FBLCOUNT               @UBINOS__UBICLIB__HEAP_DIR1_FBLCOUNT@
#define UBINOS__UBICLIB__HEAP_DIR1_FBLBM_BUFSIZE          @UBINOS__UBICLIB__HEAP_DIR1_FBLBM_BUFSIZE@

#define UBINOS__UBICLIB__HEAP_DEFAULT_DIR                       @UBINOS__UBICLIB__HEAP_DEFAULT_DIR@
#define UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX   @UBINOS__UBICLIB__HEAP_DMPM_DIR_ON_OFF_BLOCK_COUNT_MAX@

#define UBINOS__UBICLIB__HEAP_ALIGNMENT                   @UBINOS__UBICLIB__HEAP_ALIGNMENT@

#endif /* (INCLUDE__UBINOS__UBICLIB == 1) */


////////


#cmakedefine01 INCLUDE__UBINOS__UBICLIB_TEST

#if (INCLUDE__UBINOS__UBICLIB_TEST == 1)

#cmakedefine01 UBINOS__UBICLIB_TEST__EXCLUDE_HEAPTEST
#cmakedefine01 UBINOS__UBICLIB_TEST__EXCLUDE_CBUF_TEST

#endif /* (INCLUDE__UBINOS__UBICLIB_TEST == 1) */


////////


#cmakedefine01 INCLUDE__UBINOS__UBIK

#if (INCLUDE__UBINOS__UBIK == 1)

#define UBINOS__UBIK__TICK_TYPE__SYSTICK                  1
#define UBINOS__UBIK__TICK_TYPE__RTC                      2
#define UBINOS__UBIK__TICK_TYPE                           UBINOS__UBIK__TICK_TYPE__@UBINOS__UBIK__TICK_TYPE@
#define UBINOS__UBIK__TICK_PER_SEC                        @UBINOS__UBIK__TICK_PER_SEC@
#define UBINOS__UBIK__TICK_COUNT_MAX                      @UBINOS__UBIK__TICK_COUNT_MAX@

#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)

#define UBINOS__UBIK__TICK_RTC_NO                         @UBINOS__UBIK__TICK_RTC_NO@
#define UBINOS__UBIK__TICK_RTC_COUNT_MAX                  @UBINOS__UBIK__TICK_RTC_COUNT_MAX@
#define UBINOS__UBIK__TICK_RTC_TICK_PER_KERNEL_TICK       @UBINOS__UBIK__TICK_RTC_TICK_PER_KERNEL_TICK@

#cmakedefine01 UBINOS__UBIK__TICK_RTC_CHECK

#define UBINOS__UBIK__TICK_RTC_CHECK_TYPE__CORRECT        1
#define UBINOS__UBIK__TICK_RTC_CHECK_TYPE__ABORT          2
#define UBINOS__UBIK__TICK_RTC_CHECK_TYPE                 UBINOS__UBIK__TICK_RTC_CHECK_TYPE__@UBINOS__UBIK__TICK_RTC_CHECK_TYPE@

#cmakedefine01 UBINOS__UBIK__TICK_RTC_SLEEP_IDLE
#cmakedefine01 UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE

#define UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MIN      @UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MIN@
#define UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MAX      @UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MAX@
#define UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MARGIN   @UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MARGIN@

#if (UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MAX >= UBINOS__UBIK__TICK_RTC_COUNT_MAX)

	#error "UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MAX should be less than UBINOS__UBIK__TICK_RTC_COUNT_MAX"

#endif /* (UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MAX >= UBINOS__UBIK__TICK_RTC_COUNT_MAX) */

#if (UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MIN <= UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MARGIN)

	#error "UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MARGIN should be less than UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MIN"

#endif /* (UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MIN <= UBINOS__UBIK__TICK_RTC_TICKLESS_IDLE_IGNORE_TICK_COUNT_MARGIN) */

#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */

#define UBINOS__UBIK__TASK_NAME_SIZE_MAX                  @UBINOS__UBIK__TASK_NAME_SIZE_MAX@
#define UBINOS__UBIK__TASK_PRIORITY_MAX                   @UBINOS__UBIK__TASK_PRIORITY_MAX@
#define UBINOS__UBIK__TASK_MAXWAITSIGOBJ_MAX              @UBINOS__UBIK__TASK_MAXWAITSIGOBJ_MAX@
#define UBINOS__UBIK__TASK_STACK_DEPTH_DEFAULT            @UBINOS__UBIK__TASK_STACK_DEPTH_DEFAULT@
#define UBINOS__UBIK__TASK_STACK_DEPTH_MIN                @UBINOS__UBIK__TASK_STACK_DEPTH_MIN@
#define UBINOS__UBIK__IDLETASK_STACK_DEPTH                @UBINOS__UBIK__IDLETASK_STACK_DEPTH@

#define UBINOS__UBIK__MSGQ_MSGSIZE_MAX                    @UBINOS__UBIK__MSGQ_MSGSIZE_MAX@

#cmakedefine01 UBINOS__UBIK__EXCLUDE_TICK_HOOKFUNC

#cmakedefine01 UBINOS__UBIK__EXCLUDE_KERNEL_MONITORING
#cmakedefine01 UBINOS__UBIK__EXCLUDE_TASK_MONITORING
#cmakedefine01 UBINOS__UBIK__EXCLUDE_TASK_PRIORITY_INHERITANCE
#cmakedefine01 UBINOS__UBIK__EXCLUDE_IDLETASK_GARBAGECOLLECT
#cmakedefine01 UBINOS__UBIK__EXCLUDE_IDLETASK_DTTY_WRITE
#cmakedefine01 UBINOS__UBIK__EXCLUDE_IDLETASK_HOOKFUNC
#cmakedefine01 UBINOS__UBIK__EXCLUDE_CONDV
#cmakedefine01 UBINOS__UBIK__EXCLUDE_MSGQ
#cmakedefine01 UBINOS__UBIK__EXCLUDE_SEM
#cmakedefine01 UBINOS__UBIK__EXCLUDE_SIGNAL

#cmakedefine01 UBINOS__UBIK__EXCLUDE_STIMER

#cmakedefine01 UBINOS__UBIK__EXCLUDE_HRTICK
#cmakedefine01 UBINOS__UBIK__EXCLUDE_HRTICK_TICKISR_DELAY_CHECK

#define UBINOS__UBIK__IDLETASK_SPINWAIT_INTERVALTICK      @UBINOS__UBIK__IDLETASK_SPINWAIT_INTERVALTICK@

#cmakedefine01 UBINOS__UBIK__USE_PENDSV_TASK_YIELD

#endif /* (INCLUDE__UBINOS__UBIK == 1) */


////////


#cmakedefine01 INCLUDE__UBINOS__UBIK_TEST

#if (INCLUDE__UBINOS__UBIK_TEST == 1)

#define UBINOS__UBIK_TEST__MSGBUFSIZE                     @UBINOS__UBIK_TEST__MSGBUFSIZE@
#define UBINOS__UBIK_TEST__BUSYWAITCOUNTTESTTIMEMS        @UBINOS__UBIK_TEST__BUSYWAITCOUNTTESTTIMEMS@
#define UBINOS__UBIK_TEST__TASKWAITTIMEMS                 @UBINOS__UBIK_TEST__TASKWAITTIMEMS@
#define UBINOS__UBIK_TEST__TASKLOOPCOUNT                  @UBINOS__UBIK_TEST__TASKLOOPCOUNT@
#define UBINOS__UBIK_TEST__MEMLEAK_TESTCOUNT              @UBINOS__UBIK_TEST__MEMLEAK_TESTCOUNT@
#define UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT            @UBINOS__UBIK_TEST__MEMLEAK_SIGOBJCOUNT@
#define UBINOS__UBIK_TEST__MEMLEAK_TASKCOUNT              @UBINOS__UBIK_TEST__MEMLEAK_TASKCOUNT@
#define UBINOS__UBIK_TEST__MSGQSIZE                       @UBINOS__UBIK_TEST__MSGQSIZE@
#define UBINOS__UBIK_TEST__MSGQMAXCOUNT                   @UBINOS__UBIK_TEST__MSGQMAXCOUNT@

#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_MISCTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET2
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_TASKTESTSET3
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_SIGNALTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_MUTEXTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_SEMTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_MSGQTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_CONDVTESTSET
#cmakedefine01 UBINOS__UBIK_TEST__EXCLUDE_STIMERTESTSET

#endif /* (INCLUDE__UBINOS__UBIK_TEST == 1) */


////////


#cmakedefine01 INCLUDE__UBINOS__UBIDRV

#if (INCLUDE__UBINOS__UBIDRV == 1)

#cmakedefine01 UBINOS__UBIDRV__INCLUDE_NVMEM

#cmakedefine01 UBINOS__UBIDRV__INCLUDE_UART

#endif /* (INCLUDE__UBINOS__UBIDRV == 1) */


////////


#cmakedefine01 INCLUDE__APP

#if (INCLUDE__APP == 1)

#define INCLUDE__APP__@APP__NAME@ 1

#define APP__NAME                                 "@APP__NAME@"

#endif /* (INCLUDE__APP == 1) */


