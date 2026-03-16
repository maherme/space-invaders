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

INCLUDES += -I../utils/src

LDFLAGS += -Wl,--wrap=usleep \
		   -Wl,--wrap=utilsCalloc \
		   -Wl,--wrap=utilsFree
