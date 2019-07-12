###############################################################################
#
# This file must be included at the end.
#

###############################################################################

_BASE_DIR               := $(realpath $(dir $(firstword $(MAKEFILE_LIST)))/..)

###############################################################################

ifeq ($(strip $(CONFIG_NAME)),)
_CONFIG_NAME            := default
else
_CONFIG_NAME            := $(CONFIG_NAME)
endif

ifeq ($(strip $(CONFIG_DIR)),)
_CONFIG_DIR             := $(_BASE_DIR)/app
else
_CONFIG_DIR             := $(realpath $(CONFIG_DIR))
endif

ifeq ($(strip $(LIBRARY_DIR)),)
ifeq ($(lastword $(subst /, ,$(_BASE_DIR))),ubinos)
_LIBRARY_DIR            := $(realpath $(_BASE_DIR)/..)
else
_LIBRARY_DIR            := $(_BASE_DIR)/library
endif
else
_LIBRARY_DIR            := $(realpath $(LIBRARY_DIR))
endif

###############################################################################

ifeq ($(strip $(UBINOS_DIR)),)
ifeq ($(lastword $(subst /, ,$(_BASE_DIR))),ubinos)
_UBINOS_DIR            := $(_BASE_DIR)
else
_UBINOS_DIR            := $(_LIBRARY_DIR)/ubinos
endif
else
_UBINOS_DIR            := $(realpath $(UBINOS_DIR))
endif

ifeq ($(strip $(TOOLBOX)),)
_TOOLBOX               := $(_UBINOS_DIR)/make/toolbox.py
else
_TOOLBOX               := $(realpath $(TOOLBOX))
endif

###############################################################################

_SOURCE_DIR            := $(_BASE_DIR)/source

ifeq ($(strip $(OUTPUT_DIR)),)
_OUTPUT_DIR            := $(_BASE_DIR)/output/$(_CONFIG_NAME)
else
_OUTPUT_DIR            := $(OUTPUT_DIR)
endif

###############################################################################

ifeq ($(strip $(JOBS)),)
_JOBS                  := $(shell "$(_TOOLBOX)" cpu_count)
else
_JOBS                  := $(JOBS)
endif
ifeq ($(strip $(PRECMD)),)
_PRECMD                := :
else
_PRECMD                := $(PRECMD)
endif

###############################################################################

_CMAKE_OPTION           = -D PROJECT_CONFIG_NAME=$(_CONFIG_NAME)
_CMAKE_OPTION          += -D PROJECT_CONFIG_DIR="$(_CONFIG_DIR)"
_CMAKE_OPTION          += -D PROJECT_LIBRARY_DIR="$(_LIBRARY_DIR)"

###############################################################################

define begin_message
	@echo ""
	@echo "==============================================================================="
	@echo "[$@ - $(_CONFIG_NAME)]"
	@echo "-------------------------------------------------------------------------------"
	@echo ""
endef

define end_message
	@echo ""
	@echo "==============================================================================="
	@echo ""
endef

###############################################################################

common-help:
	$(call begin_message)
	@echo "CONFIG_NAME                  = $(_CONFIG_NAME)"
	@echo "CONFIG_DIR                   = $(_CONFIG_DIR)"
	@echo "LIBRARY_DIR                  = $(_LIBRARY_DIR)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "UBINOS_DIR                   = $(_UBINOS_DIR)"
	@echo "TOOLBOX                      = $(_TOOLBOX)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "BASE_DIR                     = $(_BASE_DIR)"
	@echo "SOURCE_DIR                   = $(_SOURCE_DIR)"
	@echo "OUTPUT_DIR (BINARY_DIR)      = $(_OUTPUT_DIR)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "CMAKE_OPTION                 = $(_CMAKE_OPTION)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "JOBS                         = $(_JOBS)"
	@echo "PRECMD                       = $(_PRECMD)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "MAKEFILE_LIST                = $(MAKEFILE_LIST)"
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo ""
	@echo "make all                     (config and build)"
	@echo ""
	@echo "make config                  (configure)"
	@echo "make build                   (build)"
	@echo ""
	@echo "make clean                   (clean)"
	@echo "make cleand                  (clean and remove output directory)"
	@echo ""
	@echo "make rebuild                 (clean and all)"
	@echo "make rebuildd                (cleand and all)"
	@echo ""
	@echo "make load                    (load execution binary file into target board)"
	@echo "make run                     (run execution binary file)"
	@echo "make reset                   (reset target board)"
	@echo "make debug                   (run execution binary file and attach GDB CLI)"
	@echo "make attach                  (attach GDB CLI)"
	@echo ""
	@echo "make menuconfig              (open config TUI)"
	@echo "make xconfig                 (open config GUI)"
	@echo ""
	@echo "make doc                     (build document)"
	@echo ""
	@echo "make zbatch-<make target>    (do <make target> with all <config name> listed in batch.mk)"
	$(call end_message)

###############################################################################

common-config:
	$(call begin_message)
	$(_PRECMD) && mkdir -p "$(_OUTPUT_DIR)"
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && cmake $(_CMAKE_OPTION) "$(_SOURCE_DIR)"
	$(call end_message)

common-menuconfig:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && ccmake .
	$(call end_message)

common-xconfig:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && cmake-gui .
	$(call end_message)

common-build:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make -j $(_JOBS)
	$(call end_message)

common-clean:
	$(call begin_message)
ifneq ("$(wildcard $(_OUTPUT_DIR)/Makefile)", "")
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make clean
endif
	$(call end_message)

common-cleand:
	$(call begin_message)
	$(_PRECMD) && rm -rf "$(_OUTPUT_DIR)"
	$(call end_message)

common-doc:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && doxygen
	$(call end_message)

###############################################################################

common-all: config build

common-rebuild: clean all

common-rebuildd: cleand all

###############################################################################

common-load:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make reset
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make load
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make reset
	$(call end_message)

common-reset:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make reset
	$(call end_message)

common-run:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make run
	$(call end_message)

common-debug:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make debug
	$(call end_message)

common-attach:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && make attach
	$(call end_message)

###############################################################################

common-zbatch-%:
	make -f batch.mk $*

###############################################################################

