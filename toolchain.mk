#
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2025 Manuel Hernández Méndez
# 
# Authors:
#   Manuel Hernández Méndez <maherme.dev@gmail.com>
# 
 
QUIET := @
QUIET_MAKE := --no-print-directory
RM:= rm -rf
MKDIR := mkdir -p
GCOVR := gcovr

CFLAGS = -c -Wall -Wextra -Wpedantic -Werror $(INCLUDES)
LDFLAGS :=
GCOVRFLAGS = --html-details \
			 -o $(DIR_COV)/coverage_report.html \
			 --json-summary \
			 $(DIR_COV)/coverage_report.json
