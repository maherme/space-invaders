DIR_BIN := $(CURDIR)/bin
DIR_BIN_RLS := $(DIR_BIN)/rel
DIR_COV := $(DIR_BIN)/cov
DIR_SRC := $(CURDIR)/src

DIR_TST := $(filter-out %/src/ %/bin/,$(dir $(wildcard $(DIR_SRC)/*/*/.)))
GCOV_EXCLUDE := $(foreach d,$(DIR_TST),$(addprefix -e ,$(d)))

VPATH := $(DIR_SRC) $(filter-out %/tst/ %/bin/,$(dir $(wildcard $(DIR_SRC)/*/*/.)))

INCLUDES := $(VPATH:%=-I%)

find_c_files = $(wildcard $(addsuffix /*.c,$(1)))
SRC:= $(foreach d,$(VPATH),$(call find_c_files,$(d)))
OBJ := $(notdir $(patsubst %.c, %.o, $(SRC)))
OBJ := $(addprefix $(DIR_BIN_RLS)/,$(OBJ))

DIR_MAKES := $(CURDIR)/src/utils $(CURDIR)/src/spaceship $(CURDIR)/src/graphic
