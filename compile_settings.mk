### COMPILER PART ###

# Which compiler use
CC := gcc

USED_LIBS = sdl2 SDL2_image
# Flags (with = and not := so flags can be added after)
CFLAGS = -Wall -Wextra `pkg-config --cflags $(USED_LIBS)` $(OPTFLAGS)
OPTFLAGS := -O3
CPPFLAGS = -MMD $(INCLUDE_DIRS)
LDFLAGS :=
LDLIBS := `pkg-config --libs $(USED_LIBS)` -lm
INCLUDE_DIRS = $(addprefix -I, \
			   src/Utils)

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