#
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2024 Manuel Hernández Méndez
# 
# Authors:
#   Manuel Hernández Méndez <maherme.dev@gmail.com>
# 

PROJECT_ROOT := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
export PROJECT_ROOT

include configuration.mk
include toolchain.mk

LDFLAGS += -lglut -lGL -lGLU
GCOVRFLAGS += $(GCOV_EXCLUDE)

SUBGOALS := run-test test clean-test

.PHONY: $(SUBGOALS) $(DIR_MAKES) game all coverage clean clean-all prune install_gcovr

$(SUBGOALS): $(DIR_MAKES)

$(DIR_MAKES):
	$(QUIET) $(MAKE) $(QUIET_MAKE) -C $@ $(filter $(SUBGOALS),$(MAKECMDGOALS))

game: $(OBJ)
	$(QUIET) $(CC) $^ -o $(DIR_BIN_RLS)/$@ $(LDFLAGS)

all: game 
	$(QUIET) $(MAKE) $(QUIET_MAKE) test

coverage: $(GCOVR) |  $(DIR_COV)
	$(QUIET) $(GCOVR) $(GCOVRFLAGS)

$(DIR_COV):
	$(QUIET) $(MKDIR) $(DIR_COV)

install_gcovr: $(GCOVR)

$(DIR_BIN_RLS)/%.o: %.c | $(DIR_BIN_RLS)
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

$(DIR_BIN_RLS):
	$(QUIET) $(MKDIR) $(DIR_BIN_RLS)

clean:
	$(QUIET) $(RM) $(DIR_BIN)

clean-all: clean
	$(QUIET) $(MAKE) $(QUIET_MAKE) clean-test

prune: clean-all
	$(QUIET) $(RM) $(DIR_PYENV)
