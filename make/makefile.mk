###############################################################################

help: common-help

###############################################################################

%: common-% ;

###############################################################################

-include custom.mk

###############################################################################

# The common.mk must be included at the end.
include common.mk

###############################################################################


