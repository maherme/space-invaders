include ../../toolchain.mk
include ../common.mk

LDFLAGS += -Wl,--wrap=calloc \
		   -Wl,--wrap=perror \
		   -Wl,--wrap=exit
