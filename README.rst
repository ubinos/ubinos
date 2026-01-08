###################################################################################################
Ubinos
###################################################################################################

***************************************************************************************************
Batch build command
***************************************************************************************************

.. code-block:: bash

    cd build
    sed -i '1s|.*|set(UBI_CONFIG_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/ubinos/app")|'  ../config.cmake

.. code-block:: bash

    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_netduinoplus2_qemu)/'                      ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nrf52dk)/'                                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nrf52840dk)/'                              ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nrf52840dk_bdh)/'                          ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nucleof207zg)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nucleof207zg_rtctick_external_build)/'     ../config.cmake && make configd  && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nucleol476rg)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_nucleol476rg_dtty_usart3)/'                ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_sam9xe512ek)/'                             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32f429idisco)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32f769idisco)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32f769ieval)/'                          ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32h747idisco)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32l475eiot01)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32l476geval)/'                          ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm3221geval)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm3221geval_flash_extsram)/'              ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME cli_tester_stm32429ieval)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME heap_tester_sam9xe512ek)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_netduinoplus2_qemu)/'                     ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_nrf52dk)/'                                ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_nrf52840dk)/'                             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_nucleof207zg)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_nucleol476rg_dtty_usart3)/'               ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_nucleol476rg)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_sam9xe512ek)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32f429idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32f769idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32f769ieval)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32h747idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32l475eiot01)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32l476geval)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm3221geval_flash_extsram)/'             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm3221geval)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hello_world_stm32429ieval)/'                          ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_local_gcc_baremetal)/'                       ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_local_llvm_baremetal)/'                      ../config.cmake && make configd  && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_netduinoplus2_baremetal_qemu)/'              ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nrf52dk_baremetal_sram)/'                    ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nrf52dk_baremetal)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nrf52840dk_baremetal_sram)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nrf52840dk_baremetal)/'                      ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nucleof207zg_baremetal_sram)/'               ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nucleof207zg_baremetal)/'                    ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nucleoh723zg_baremetal)/'                    ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nucleol476rg_baremetal_dtty_usart3)/'        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_nucleol476rg_baremetal)/'                    ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_sam9xe512ek_baremetal_sram)/'                ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_sam9xe512ek_baremetal)/'                     ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32f429idisco_baremetal)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32f769idisco_baremetal_sram)/'            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32f769idisco_baremetal)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32f769ieval_baremetal_sram)/'             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32f769ieval_baremetal)/'                  ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32h747idisco_baremetal)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32l475eiot01_baremetal)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32l476geval_baremetal)/'                  ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32vldisco_baremetal_qemu)/'               ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm3221geval_baremetal_flash_extsram)/'      ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm3221geval_baremetal_sram)/'               ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm3221geval_baremetal)/'                    ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME hi_world_stm32429ieval_baremetal)/'                   ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubiclib_tester_nrf52840dk)/'                          ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nrf52dk)/'                                ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nrf52840dk_bdh_align16)/'                 ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nrf52840dk_bdh)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nrf52840dk)/'                             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nucleof207zg_rtctick_external_build)/'    ../config.cmake && make configd  && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nucleof207zg)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nucleol476rg_dtty_usart3)/'               ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_nucleol476rg)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_sam9xe512ek)/'                            ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32f429idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32f769idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32f769ieval)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32h747idisco)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32l475eiot01)/'                        ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32l476geval)/'                         ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm3221geval_flash_extsram)/'             ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm3221geval)/'                           ../config.cmake && make rebuildd && \
    sed -i '2s/.*/set(UBI_CONFIG_NAME ubik_tester_stm32429ieval)/'                          ../config.cmake && make rebuildd
