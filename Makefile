QUIET := @
RM := rm -rf
MKDIR := mkdir -p

DIR_BIN := $(CURDIR)/bin
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

OBJ := $(addprefix $(DIR_BIN)/,$(OBJ))
OBJ_TST := $(addprefix $(DIR_BIN)/,$(OBJ_TST))

CFLAGS := -c -Wall -Wextra -Wpedantic -Werror $(INCLUDES)
LDFLAGS := -lglut -lGL
TEST_LDFLAGS := -lcmocka \
				-Wl,--wrap=glutInit \
				-Wl,--wrap=glutInitDisplayMode \
				-Wl,--wrap=glutInitWindowSize \
				-Wl,--wrap=glutInitWindowPosition \
				-Wl,--wrap=glutCreateWindow \
				-Wl,--wrap=glutDisplayFunc \
				-Wl,--wrap=glClear \
				-Wl,--wrap=glutSwapBuffers

$(shell $(MKDIR) $(DIR_BIN))

test: $(OBJ_TST)
	$(QUIET) $(CC) $^ -o $(DIR_BIN)/$@ $(TEST_LDFLAGS)
	$(QUIET) $(DIR_BIN)/test

game: $(DIR_BIN)/main.o $(OBJ)
	$(QUIET) $(CC) $^ -o $(DIR_BIN)/$@ $(LDFLAGS)

$(DIR_BIN)/%.o: %.c
	$(QUIET) $(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(QUIET) $(RM) $(DIR_BIN)
