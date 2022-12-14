# Name of the final executable
TARGET := main

### COMPILER PART ###

# Which compiler use
CC := gcc

USED_LIBS = sdl2 SDL2_image
# Flags (with = and not := so flags can be added after)
CFLAGS = -Wall -Wextra `pkg-config --cflags $(USED_LIBS)` $(OPTFLAGS)
OPTFLAGS := -O3
CPPFLAGS = -MMD $(INCLUDE_DIRS)
LDFLAGS :=
LDLIBS := `pkg-config --libs $(USED_LIBS)`
INCLUDE_DIRS = $(addprefix -I,\
)

# Debug mode can be enabled by executing `make DEBUG=1 rule_name`
DEBUG := 0

ifneq ($(DEBUG), 0)
	OPTFLAGS = -O1
	CFLAGS += -g -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
	CPPFLAGS += -DDEBUG # define DEBUG like `#define DEBUG` in all C files
endif


### SOURCES PART ###

# Dir where all build files will be stored
BUILD_DIR := ./_build

# Find all subdirectories
SRC_DIRS := $(shell find ./ -type d -not -path "*_build*")

# Create all needed dirs
$(shell mkdir -p $(SRC_DIRS:%=$(BUILD_DIR)/%))

CFILES := $(shell find ./ -type f -name "*.c")
OFILES := $(CFILES:%.c=$(BUILD_DIR)/%.o)
DFILES := $(OFILES:%.o=%.d)

### RULES PART ###

all: $(TARGET)

$(TARGET): $(OFILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Same rule for all .o files
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

format:
	find -name "*.[ch]" | xargs clang-format -i

.PHONY: clean all format
-include $(D_FILES)
