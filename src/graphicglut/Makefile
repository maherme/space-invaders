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

LDFLAGS += -Wl,--wrap=glutInit \
		   -Wl,--wrap=glutInitDisplayMode \
		   -Wl,--wrap=glutInitWindowSize \
		   -Wl,--wrap=glutInitWindowPosition \
		   -Wl,--wrap=glutCreateWindow \
		   -Wl,--wrap=glutDisplayFunc \
		   -Wl,--wrap=glutReshapeFunc \
		   -Wl,--wrap=glClear \
		   -Wl,--wrap=glutSwapBuffers \
		   -Wl,--wrap=glViewport \
		   -Wl,--wrap=glMatrixMode \
		   -Wl,--wrap=glLoadIdentity \
		   -Wl,--wrap=gluOrtho2D \
		   -Wl,--wrap=glEnable \
		   -Wl,--wrap=graphPrintImage
