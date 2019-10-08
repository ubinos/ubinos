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

###############################################################################

