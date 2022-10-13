# Name of the final executable
TARGET := gopy_ocr

include prettyprint.mk

### COMPILER PART ###

# Which compiler use
CC := gcc

USED_LIBS = sdl2 SDL2_image
# Flags (with = and not := so flags can be added after)
CFLAGS = -Wall -Wextra `pkg-config --cflags $(USED_LIBS)` $(OPTFLAGS)
OPTFLAGS := -O3
CPPFLAGS := -MMD $(INCLUDE_DIRS)
LDFLAGS :=
LDLIBS := `pkg-config --libs $(USED_LIBS)`
INCLUDE_DIRS =

# Debug mode can be enabled by executing `make DEBUG=1 rule_name`
DEBUG := 0

ifneq ($(DEBUG), 0)
	OPTFLAGS = -O1
	CFLAGS += -g -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
	CPPFLAGS += -DDEBUG # define DEBUG like `#define DEBUG`
endif


### SOURCES PART ###

# Dir where all build files will be stored
BUILD_DIR := ./_build

# Find all subdirectories
SRC_DIRS := $(shell find ./src -type d -not -path "*_build*")

# Create all needed dirs
$(shell mkdir -p $(SRC_DIRS:%=$(BUILD_DIR)/%))

CFILES := $(shell find ./src -type f \( -iname "*.c" ! -iname "*main.c" \)) ./src/main.c
OFILES := $(CFILES:%.c=$(BUILD_DIR)/%.o)
DFILES := $(OFILES:%.o=%.d)

### RULES PART ###

all: $(TARGET)

# Take a look to `prettyprint.mk` to understand $(V) and other things
$(TARGET): $(OFILES)
	$(V)$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@if [[ $$? == 0 ]]; then $(call printtask,$(GREEN),Linked successfuly:,$@); \
		else $(call printtask,$(RED),Linking failed:,$@); fi;

$(BUILD_DIR)/%.o: %.c
	$(V)$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)
	@if [[ $$? == 0 ]]; then $(call printtask,$(GREEN),Compiled successfuly:,$<); \
		else $(call printtask,$(RED),Compilation failed:,$<); fi;

test: $(BUILD_DIR)/$(TARGET_EXEC)
	$(MAKE) -C tests

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

format:
	find -name "*.[ch]" | xargs clang-format -i

.PHONY: clean all format test
-include $(D_FILES)
