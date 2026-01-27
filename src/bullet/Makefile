include ../../toolchain.mk
include ../common.mk

LDFLAGS += -Wl,--wrap=utilsCalloc \
		   -Wl,--wrap=graphCreateImage \
		   -Wl,--wrap=graphGetSprite \
		   -Wl,--wrap=graphPrintImage
