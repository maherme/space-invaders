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
			-I../utils/src

LDFLAGS += -Wl,--wrap=utilsCheckTimeout \
		   -Wl,--wrap=graphUpdateTimeSprite \
		   -Wl,--wrap=graphGetSpriteCoordinates \
		   -Wl,--wrap=graphUpdateImageToPrint
