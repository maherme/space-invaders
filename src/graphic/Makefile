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

LDFLAGS += -Wl,--wrap=glGenTextures \
		   -Wl,--wrap=glTexImage2D \
		   -Wl,--wrap=glTexParameteri \
		   -Wl,--wrap=glBegin \
		   -Wl,--wrap=glTexCoord2f \
		   -Wl,--wrap=glVertex2i \
		   -Wl,--wrap=glEnd \
		   -Wl,--wrap=glBindTexture \
		   -Wl,--wrap=glDeleteTextures \
		   -Wl,--wrap=gettimeofday \
		   -Wl,--wrap=utilsFree
