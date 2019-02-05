ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),)
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
endif

SILENCE = @

#Helper Functions
get_src_from_dir  = $(wildcard $1/*.cpp) $(wildcard $1/*.c)
get_dirs_from_dirspec  = $(wildcard $1)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
__src_to = $(subst .c,$1, $(subst .cpp,$1,$2))
src_to = $(call __src_to,$1,$2)
src_to_o = $(call src_to,.o,$1)
src_to_d = $(call src_to,.d,$1)
src_to_gcda = $(call src_to,.gcda,$1)
src_to_gcno = $(call src_to,.gcno,$1)
make_dotdot_a_subdir = $(subst ..,_dot_dot, $1)
time = $(shell date +%s)
delta_t = $(eval minus, $1, $2)
debug_print_list = $(foreach word,$1,echo "  $(word)";) echo;

SRC_DIR = src
OBJ_DIR = objs
TESTS_DIR = tests
UNITY_DIR = unity
INCLUDE_DIR = include
UNITY_SRC =\
	$(UNITY_DIR)/src\
	$(UNITY_DIR)/extras/fixture/src

SRC_DIRS =\
	$(SRC_DIR)/LedDriver

TEST_SRC_DIRS =\
	$(TESTS_DIR)\
	$(TESTS_DIR)/LedDriver

INCLUDE_PATHS =\
	$(INCLUDE_DIR)/LedDriver\
	$(UNITY_DIR)/extras/fixture/src\
	$(UNITY_DIR)/src

TARGET_NAME = RUN
TEST_TARGET = $(TARGET_NAME).$(TARGET_EXTENSION)

COMPILE = gcc -c
LINK = gcc
INCLUDES = $(foreach dir,$(INCLUDE_PATHS),-I$(dir))
CFLAGS = $(INCLUDES) -w

TEST_SRC = $(call get_src_from_dir_list, $(TEST_SRC_DIRS) $(UNITY_SRC))
TEST_OBJ = $(addprefix $(OBJ_DIR)/,$(call src_to_o,$(TEST_SRC)))
SRC = $(call get_src_from_dir_list,$(SRC_DIRS))
OBJ = $(addprefix $(OBJ_DIR)/,$(call src_to_o,$(SRC)))

test: $(TEST_TARGET)
	$(SILENCE)./$(TARGET_NAME)

$(TEST_TARGET): $(TEST_OBJ) $(OBJ)
	$(SILENCE)$(LINK) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(COMPILE) $(CFLAGS) $< -o $@

clean:
	$(SILENCE)$(CLEANUP) $(OBJ)
	$(SILENCE)$(CLEANUP) $(TEST_OBJ)
	$(SILENCE)$(CLEANUP) *.$(TARGET_EXTENSION)

.PRECIOUS: %.$(TARGET_EXTENSION)
.PRECIOUS: $(OBJ_DIR)%.o
