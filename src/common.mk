DIR_BIN := $(CURDIR)/bin
DIR_COV := $(DIR_BIN)/cov
SRC := $(wildcard $(CURDIR)/src/*.c) \
	   $(wildcard $(CURDIR)/tst/*.c)
OBJ := $(addprefix $(DIR_BIN)/,$(notdir $(patsubst %.c,%.o,$(filter %.c,$(SRC)))))

VPATH := $(sort $(dir $(SRC)))

INCLUDES := $(VPATH:%=-I%)

CFLAGS += --coverage
LDFLAGS += -lgcov --coverage -lcmocka
GCOVRFLAGS += --exclude $(CURDIR)/tst

$(shell $(MKDIR) $(DIR_BIN))
$(shell $(MKDIR) $(DIR_COV))

.PHONY: run-test
run-test: test
	$(QUIET) $(DIR_BIN)/test

.PHONY: test
test: $(OBJ)
	$(QUIET) $(CC) $^ -o $(DIR_BIN)/$@ $(LDFLAGS)

$(DIR_BIN)/%.o: %.c
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

.PHONY: coverage
coverage:
	$(QUIET) $(GCOVR) $(GCOVRFLAGS)

.PHONY: clean
clean:
	$(QUIET) $(RM) $(DIR_BIN)
