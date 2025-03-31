###############################################################################

LIBRARY_DIR ?= ../..

###############################################################################

include $(LIBRARY_DIR)/ubinos/make/common.mk
-include $(LIBRARY_DIR)/ubinos/make/custom.mk

###############################################################################

include $(_CONFIG_DIR)/$(_CONFIG_NAME).mk

###############################################################################

config:
	$(call begin_message)
	$(_PRECMD) && $(call func_make_dir,"$(_OUTPUT_DIR)")
	$(call end_message)

menuconfig:
	$(call begin_message)
	$(call end_message)

xconfig:
	$(call begin_message)
	$(call end_message)

build: doc
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

xrun: xopendoc
	$(call begin_message)
	$(call end_message)

doc:
	$(call begin_message)
ifneq ("$(BUILD_HTML)", "0")
	$(_PRECMD) && sphinx-build -M html     "$(_CONFIG_DIR)/$(APP__NAME)/doc" "$(_OUTPUT_DIR)"
endif
ifneq ("$(BUILD_LATEXPDF)", "0")
	$(_PRECMD) && sphinx-build -M latexpdf "$(_CONFIG_DIR)/$(APP__NAME)/doc" "$(_OUTPUT_DIR)"
endif
	$(call end_message)

xopendoc:
	$(call begin_message)
ifneq ("$(BUILD_HTML)", "0")
	$(shell python "$(_TOOLBOX)" get_open_command_for_cmake) "$(_OUTPUT_DIR)/html/index.html"
endif
ifneq ("$(BUILD_LATEXPDF)", "0")
	$(shell python "$(_TOOLBOX)" get_open_command_for_cmake) "$(_OUTPUT_DIR)/latex/$(LATEX_FILE_NAME).pdf"
endif
	$(call end_message)

cleandoc:
	$(call begin_message)
	$(_PRECMD) && sphinx-build -M clean    "$(_CONFIG_DIR)/$(APP__NAME)/doc" "$(_OUTPUT_DIR)"
	$(call end_message)

clean: cleandoc
	$(call begin_message)
	$(call end_message)

cleand:
	$(call begin_message)
	$(_PRECMD) && $(call func_remove_dir,"$(_OUTPUT_DIR)")
	$(call end_message)

install:
	$(call begin_message)
ifeq ($(strip $(DOCS_INSTALL_DIR)),)
	@echo "DOCS_INSTALL_DIR is not defined."
else
	$(_PRECMD) && python -c "import shutil, os; d='$(DOCS_INSTALL_DIR)'; shutil.rmtree(d) if os.path.exists(d) and os.path.isdir(d) else None"
	$(_PRECMD) && python -c "import shutil; import os; s='$(_OUTPUT_DIR)/html'; d='$(DOCS_INSTALL_DIR)'; shutil.copytree(s, d)"
endif
ifneq ($(strip $(DOCS_INSTALL_ADDITIONAL_CMD)),)
	$(_PRECMD) && $(DOCS_INSTALL_ADDITIONAL_CMD)
endif
	$(call end_message)

%: common-% ;

###############################################################################

