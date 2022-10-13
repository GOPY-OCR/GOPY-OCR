# Name of the final executable
TARGET := gopy_ocr

### COMPILER PART ###

# Which compiler use
CC := gcc

# Flags (with = and not := so flags can be added after)
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image` $(OPTFLAGS)
OPTFLAGS := -O3
CPPFLAGS := -MMD
LDFLAGS :=
LDLIBS := `pkg-config --libs sdl2 SDL2_image`

# Debug mode can be enabled by executing `make DEBUG=1 rule_name`
DEBUG := 0

ifneq ($(DEBUG), 0)
	OPTFLAGS = -O1
	CFLAGS += -g -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
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

$(TARGET): $(OFILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)


$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)


test: $(BUILD_DIR)/$(TARGET_EXEC)
	$(MAKE) -C tests

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

format:
	find -name "*.[ch]" | xargs clang-format -i

.PHONY: clean all format test
-include $(D_FILES)
