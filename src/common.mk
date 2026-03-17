#
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2025 Manuel Hernández Méndez
# 
# Authors:
#   Manuel Hernández Méndez <maherme.dev@gmail.com>
# 

#
# This Makefile applies only for building test
#

DIR_BIN := $(CURDIR)/bin
TEST_BIN := $(DIR_BIN)/test
SRC := $(wildcard $(CURDIR)/src/*.c) \
	   $(wildcard $(CURDIR)/tst/*.c)
OBJ := $(addprefix $(DIR_BIN)/,$(notdir $(patsubst %.c,%.o,$(filter %.c,$(SRC)))))

VPATH := $(sort $(dir $(SRC)))

INCLUDES := $(VPATH:%=-I%)

CFLAGS += --coverage -DUNIT_TESTING -DNDEBUG -O0 -fsanitize=address -g -fno-omit-frame-pointer
LDFLAGS += -lgcov --coverage -lcmocka -fsanitize=address
GCOVRFLAGS += --exclude $(CURDIR)/tst

.PHONY: run-test test coverage clean-test

run-test: $(TEST_BIN)
	$(QUIET) $(TEST_BIN)

test: $(TEST_BIN)

$(TEST_BIN): $(OBJ)
	$(QUIET) $(CC) $^ -o $@ $(LDFLAGS)

$(DIR_BIN)/%.o: %.c | $(DIR_BIN)
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

$(DIR_BIN):
	$(QUIET) $(MKDIR) $(DIR_BIN)

coverage:
	$(QUIET) $(GCOVR) $(GCOVRFLAGS)

clean-test:
	$(QUIET) $(RM) $(DIR_BIN)
