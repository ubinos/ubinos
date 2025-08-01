###############################################################################

LIBRARY_DIR ?= ../..

###############################################################################

include $(LIBRARY_DIR)/ubinos/make/common.mk
-include $(LIBRARY_DIR)/ubinos/make/custom.mk

###############################################################################

include $(_CONFIG_DIR)/$(_CONFIG_NAME).mk

###############################################################################

define func_pip_install_e
	cd "$(LIBRARY_DIR)/$(1)" && pip install -e .
endef

define func_python_setup_py_install
	cd "$(LIBRARY_DIR)/$(1)" && python setup.py install
endef

define func_python_setup_py_develop
	cd "$(LIBRARY_DIR)/$(1)" && python setup.py develop
endef

###############################################################################

PYTHON_VENV_OPTIONS_USE_SYSTEM_SITE_PACKAGES ?= 0

ifeq ($(strip $(PYTHON_INTERPRETER)),)
ifeq ("$(shell python "$(_TOOLBOX)" is_python3)", "1")
_PYTHON_INTERPRETER = python
else
_PYTHON_INTERPRETER = python3
endif
else
_PYTHON_INTERPRETER = $(PYTHON_INTERPRETER)
endif

ifeq ($(strip $(PYTHON_VENV_INTERPRETER)),)
_PYTHON_VENV_INTERPRETER = $(_PYTHON_INTERPRETER)
else
_PYTHON_VENV_INTERPRETER = $(PYTHON_VENV_INTERPRETER)
endif

ifeq ($(strip $(PYTHON_VENV_OPTIONS)),)
_PYTHON_VENV_OPTIONS    =
else
_PYTHON_VENV_OPTIONS    = $(PYTHON_VENV_OPTIONS)
endif

ifneq ("$(PYTHON_VENV_OPTIONS_USE_SYSTEM_SITE_PACKAGES)", "0")
_PYTHON_VENV_OPTIONS   += --system-site-packages
endif

###############################################################################

config:
	$(call begin_message)
	$(_PRECMD) && $(call mkf_mkdir_p,"$(_OUTPUT_DIR)")
	@echo ""
	@echo "PYTHON_INTERPRETER:      $(_PYTHON_INTERPRETER)"
	@echo "PYTHON_VENV_INTERPRETER: $(_PYTHON_VENV_INTERPRETER)"
	@echo "PYTHON_VENV_OPTIONS:     $(_PYTHON_VENV_OPTIONS)"
	@echo ""
	$(call end_message)

menuconfig:
	$(call begin_message)
	$(call end_message)

xconfig:
	$(call begin_message)
	$(call end_message)

build: env
	$(call begin_message)
	$(call end_message)

load:
	$(call begin_message)
	$(call end_message)

reset:
	$(call begin_message)
	$(call end_message)

run:
	$(call begin_message)
	$(call end_message)

xrun:
	$(call begin_message)
	$(call end_message)

env:
	$(call begin_message)
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && $(_PYTHON_INTERPRETER)  -m virtualenv $(_PYTHON_VENV_OPTIONS) -p $(_PYTHON_VENV_INTERPRETER)  .
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && $(shell $(_PYTHON_INTERPRETER) "$(_TOOLBOX)" get_python_venv_activate_command_for_cmake .) && pip install -r "$(_CONFIG_DIR)/$(APP__NAME)/requriements.txt"
ifeq ($(strip $(PIP_INSTALL_E_LIST)),)
else
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && $(shell $(_PYTHON_INTERPRETER) "$(_TOOLBOX)" get_python_venv_activate_command_for_cmake .) && $(foreach item,$(PIP_INSTALL_E_LIST),$(call func_pip_install_e,$(item));)
endif
ifeq ($(strip $(PYTHON_SETUP_PY_INSTALL_LIST)),)
else
	$(_PRECMD) && cd "$(_OUTPUT_DIR)" && $(shell $(_PYTHON_INTERPRETER) "$(_TOOLBOX)" get_python_venv_activate_command_for_cmake .) && $(foreach item,$(PYTHON_SETUP_PY_INSTALL_LIST),$(call func_python_setup_py_develop,$(item));)
endif
	@echo ""
	@echo ""
	@echo "* python interpreter path: "
	@echo "$(_OUTPUT_DIR)/bin/python"
	@echo ""
	@echo "* env activate command: "
	@echo "$(shell python "$(_TOOLBOX)" get_python_venv_activate_command $(_OUTPUT_DIR))"
	@echo ""
	@echo "* env deactivate command: "
	@echo "deactivate"
	@echo ""
	$(call end_message)

cleanenv:
	$(call begin_message)
	$(call end_message)

clean: cleanenv
	$(call begin_message)
	$(call end_message)

cleand:
	$(call begin_message)
	$(_PRECMD) && $(call mkf_rm_rf,"$(_OUTPUT_DIR)")
	$(call end_message)

test:
	$(call begin_message)
	$(_PRECMD) && which python
	$(_PRECMD) && python --version
	$(_PRECMD) && which pip
	$(_PRECMD) && pip list
	$(call end_message)

%: common-% ;

###############################################################################


