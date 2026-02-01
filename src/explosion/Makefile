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

LDFLAGS += -Wl,--wrap=utilsCalloc \
		   -Wl,--wrap=graphCreateImage \
		   -Wl,--wrap=graphGetSprite \
		   -Wl,--wrap=clock_gettime
