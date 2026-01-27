
include ../../toolchain.mk
include ../common.mk

LDFLAGS += -Wl,--wrap=glutIgnoreKeyRepeat \
		   -Wl,--wrap=glutKeyboardFunc \
		   -Wl,--wrap=glutKeyboardUpFunc \
		   -Wl,--wrap=glutSpecialFunc \
		   -Wl,--wrap=glutSpecialUpFunc
