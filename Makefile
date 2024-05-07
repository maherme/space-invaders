include configuration.mk
include toolchain.mk

LDFLAGS += -lglut -lGL
GCOVRFLAGS += $(GCOV_EXCLUDE)

.PHONY: run-test
run-test: test
	@for dir in $(DIR_MAKES); do \
		$(MAKE) $(QUIET_MAKE) --directory=$$dir; \
	done

.PHONY: test
test:
	@for dir in $(DIR_MAKES); do \
		$(MAKE) $(QUIET_MAKE) --directory=$$dir test; \
	done

.PHONY: clean-test
clean-test:
	@for dir in $(DIR_MAKES); do \
		$(MAKE) $(QUIET_MAKE) --directory=$$dir clean; \
	done

.PHONY: game
game: $(shell $(MKDIR) $(DIR_BIN_RLS))
game: $(OBJ)
	$(QUIET) $(CC) $^ -o $(DIR_BIN_RLS)/$@ $(LDFLAGS)

.PHONY: all
all: game test

.PHONY: coverage
coverage: $(shell $(MKDIR) $(DIR_COV))
coverage:
	$(QUIET) $(GCOVR) $(GCOVRFLAGS)

$(DIR_BIN_RLS)/%.o: %.c
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(QUIET) $(RM) $(DIR_BIN)

.PHONY: clean-all
clean-all: clean clean-test
