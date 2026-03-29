#
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2026 Manuel Hernández Méndez
# 
# Authors:
#   Manuel Hernández Méndez <maherme.dev@gmail.com>
#

include ../../toolchain.mk
include ../common.mk

INCLUDES += -I../graphic/src \
			-I../utils/src \
			-I../graphicglut/src

LDFLAGS += -Wl,--wrap=utilsCalloc \
		   -Wl,--wrap=utilsFree \
		   -Wl,--wrap=utilsCheckTimeout \
		   -Wl,--wrap=graphCreateImage \
		   -Wl,--wrap=graphDestroyImage \
		   -Wl,--wrap=graphGetSprite \
		   -Wl,--wrap=graphNextImageToPrint \
		   -Wl,--wrap=clock_gettime \
		   -Wl,--wrap=graphRegisterPrint \
		   -Wl,--wrap=graphUnregisterPrint
