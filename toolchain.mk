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
DIR_PYENV := $(PROJECT_ROOT)/venv_gcovr
GCOVR := $(DIR_PYENV)/bin/gcovr

CFLAGS = -c -Wall -Wextra -Wpedantic -Werror \
		 $(INCLUDES)
LDFLAGS :=
GCOVRFLAGS = --html-details \
			 -o $(DIR_COV)/coverage_report.html \
			 --json-summary \
			 $(DIR_COV)/coverage_report.json

$(GCOVR):
	python3 -m venv $(PROJECT_ROOT)/venv_gcovr
	$(PROJECT_ROOT)/venv_gcovr/bin/python3 -m pip install --upgrade pip
	$(PROJECT_ROOT)/venv_gcovr/bin/pip install gcovr
