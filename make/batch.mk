#
# Copyright (c) 2019 Sung Ho Park and CSOS
# 
# SPDX-License-Identifier: Apache-2.0
#

###############################################################################

%:
	@echo ""
	@echo ""
	
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_sam9xe512ek_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_sam9xe512ek_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_sam9xe512ek
	@echo ""
	@echo ""

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_sam9xe512ek_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_sam9xe512ek_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_sam9xe512ek
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_sam9xe512ek
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_sam9xe512ek
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : heap tester application"
	@echo "Target board    : sam9xe512ek"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=heap_tester_sam9xe512ek
	@echo ""
	@echo ""

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_baremetal_sram_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_baremetal_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_softdevice_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_softdevice_baremetal_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_softdevice
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52dk_softdevice_trace
	@echo ""
	@echo ""

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nrf52dk_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nrf52dk_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_nrf52dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application supporting ETM trace"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_nrf52dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : nrf52dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_nrf52dk
	@echo ""
	@echo ""
	

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_baremetal_sram_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_baremetal_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_softdevice_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice supporting ETM trace"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_softdevice_baremetal_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_softdevice
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice supporting ETM trace"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dk_softdevice_trace
	@echo ""
	@echo ""

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nrf52840dk_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nrf52840dk_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_nrf52840dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_nrf52840dk
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash, bidirectional heap"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_nrf52840dk_bdh
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : nrf52840dk"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_nrf52840dk
	@echo ""
	@echo ""
	
	
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dongle"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dongle_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dongle"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dongle_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nrf52840dongle"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dongle
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52840dongle"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dongle_softdevice_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice"
	@echo "Target board    : nrf52840dongle"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nrf52840dongle_softdevice
	@echo ""
	@echo ""
		
	
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal_flash_extsram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal_flash_extsram_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_extsram_aws"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal_flash_extsram_aws
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library supporting ETM trace"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_extsram_aws"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal_flash_extsram_aws_trace
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_flash_extsram
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm3221geval_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm3221geval_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm3221geval_baremetal_flash_extsram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_stm3221geval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_stm3221geval_flash_extsram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_stm3221geval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_stm3221geval_flash_extsram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_stm3221geval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : stm3221geval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash_extsram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_stm3221geval_flash_extsram
	@echo ""
	@echo ""
	
	
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nucleof207zg_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nucleof207zg_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nucleof207zg
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library with softdevice supporting ETM trace"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_nucleof207zg_trace
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nucleof207zg_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_nucleof207zg_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_nucleof207zg
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_nucleof207zg
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : nucleof207zg"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_nucleof207zg
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769ieval_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769ieval_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769ieval
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm32f769ieval_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm32f769ieval_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_stm32f769ieval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_stm32f769ieval
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : stm32f769ieval"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_stm32f769ieval
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32l475eiot01_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_aws"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32l475eiot01_baremetal_aws
	@echo ""
	@echo ""

	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm32l475eiot01_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_stm32l475eiot01
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_stm32l475eiot01
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : stm32l475eiot01"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_stm32l475eiot01
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769idisco_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769idisco_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_ethernet"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769idisco_baremetal_ethernet
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash_ethernet_aws"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769idisco_baremetal_ethernet_aws
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm32f769idisco
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : sram"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm32f769idisco_baremetal_sram
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld application"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_stm32f769idisco_baremetal
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : helloworld multi-tasking application"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=helloworld_mt_stm32f769idisco
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubik tester application"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=ubik_tester_stm32f769idisco
	@echo ""
	@echo ""
	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : command line interface tester application"
	@echo "Target board    : stm32f769idisco"
	@echo "OS Kernel       : ubik"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_NAME=cli_tester_stm32f769idisco
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	@echo "Config          : ubinos library"
	@echo "Target board    : stm32429ieval"
	@echo "OS Kernel       : none"
	@echo "Link memory map : flash"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=ubinos_stm3221geval_baremetal
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""

###############################################################################

