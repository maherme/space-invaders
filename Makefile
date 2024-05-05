QUIET := @
RM := rm -rf
MKDIR := mkdir -p
GCOVR := gcovr

DIR_BIN := $(CURDIR)/bin
DIR_BIN_TST := $(DIR_BIN)/tst
DIR_COV := $(DIR_BIN_TST)/cov
DIR_BIN_RLS := $(DIR_BIN)/rel
DIR_SRC := $(CURDIR)/src
DIR_TST := $(CURDIR)/tst

INCLUDES := -I$(DIR_SRC)

VPATH := $(DIR_SRC) $(DIR_TST)

OBJ := graphGlut.o \
	   graphGlutCallbacks.o

OBJ_TST := $(OBJ) \
		   test.o \
		   testGraphGlut.o \
		   testGraphGlutCallbacks.o

OBJ := $(addprefix $(DIR_BIN_RLS)/,$(OBJ))
OBJ_TST := $(addprefix $(DIR_BIN_TST)/,$(OBJ_TST))

CFLAGS := -c -Wall -Wextra -Wpedantic -Werror $(INCLUDES)
LDFLAGS := -lglut -lGL
TEST_LDFLAGS := -lgcov \
				--coverage \
				-lcmocka \
				-Wl,--wrap=glutInit \
				-Wl,--wrap=glutInitDisplayMode \
				-Wl,--wrap=glutInitWindowSize \
				-Wl,--wrap=glutInitWindowPosition \
				-Wl,--wrap=glutCreateWindow \
				-Wl,--wrap=glutDisplayFunc \
				-Wl,--wrap=glClear \
				-Wl,--wrap=glutSwapBuffers
GCOVRFLAGS := --html-details \
			  --exclude $(DIR_TST) \
			  -o $(DIR_COV)/coverage_report.html \
			  --json-summary \
			  $(DIR_COV)/coverage_report.json

.PHONY: run-test
run-test: test
	$(QUIET) $(DIR_BIN_TST)/test

.PHONY: test
test: $(shell $(MKDIR) $(DIR_BIN_TST))
test: $(shell $(MKDIR) $(DIR_COV))
test: CFLAGS += --coverage
test: $(OBJ_TST)
	$(QUIET) $(CC) $^ -o $(DIR_BIN_TST)/$@ $(TEST_LDFLAGS)

.PHONY: game
game: $(shell $(MKDIR) $(DIR_BIN_RLS))
game: $(DIR_BIN_RLS)/main.o $(OBJ)
	$(QUIET) $(CC) $^ -o $(DIR_BIN_RLS)/$@ $(LDFLAGS)

.PHONY: all
all: game test

.PHONY: gen-coverage
gen-coverage:
	$(QUIET) $(GCOVR) $(GCOVRFLAGS) -o $(DIR_COV)/coverage_report.html

$(DIR_BIN_TST)/%.o: %.c
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

$(DIR_BIN_RLS)/%.o: %.c
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(QUIET) $(RM) $(DIR_BIN)
