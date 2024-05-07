include ../../toolchain.mk
include ../common.mk

LDFLAGS += -Wl,--wrap=glBindTexture \
		   -Wl,--wrap=glGenTextures \
		   -Wl,--wrap=glTexImage2D \
		   -Wl,--wrap=glTexParameteri \
		   -Wl,--wrap=utilsCalloc
