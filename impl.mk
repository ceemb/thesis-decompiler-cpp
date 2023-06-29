#
# Copyright Ericsson AB
#
# The copyright to the computer programs herein is the property of
# Ericsson AB. The programs may be used and/or copied only with the
# written permission from Ericsson AB or in accordance with the terms
# conditions stipulated in the agreement/contract under which the
# programs have been supplied.
#
$(ALFRED_HEADER)

# Implementation interface dependencies
$(call include_if_mk_once,$(MODULE_DIR)/if.mk)

# Implementation code
SRC_DIRS_$(MODULE_ID) += $(MODULE_DIR)/src
SRC_DIRS_$(MODULE_ID) += $(MODULE_DIR)/src/xnap/src

$(ALFRED_FOOTER)
