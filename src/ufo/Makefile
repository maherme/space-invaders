#
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2025 Manuel Hernández Méndez
# 
# Authors:
#   Manuel Hernández Méndez <maherme.dev@gmail.com>
# 
 
include ../../toolchain.mk
include ../common.mk

INCLUDES += -I../graphic/src \
			-I../utils/src \
			-I../graphicglut/src \
			-I../physic/src

LDFLAGS += -Wl,--wrap=utilsCalloc \
		   -Wl,--wrap=utilsCheckTimeout \
		   -Wl,--wrap=graphGetSprite \
		   -Wl,--wrap=graphUpdateTimeSprite \
		   -Wl,--wrap=graphRegisterPrint \
		   -Wl,--wrap=graphUnregisterPrint \
		   -Wl,--wrap=rand
