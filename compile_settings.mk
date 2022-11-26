### COMPILER PART ###

# Which compiler use
CC := gcc

USED_LIBS = sdl2 SDL2_image SDL_gfx gtk+-3.0
# Flags (with = and not := so flags can be added after)
CFLAGS = -Wall -Wextra `pkg-config --cflags $(USED_LIBS)` $(OPTFLAGS) -D__NO_INLINE__
OPTFLAGS := -O3
CPPFLAGS = -MMD $(addprefix -I, $(INCLUDE_DIRS))
LDFLAGS :=
LDLIBS := `pkg-config --libs $(USED_LIBS)` -lm -export-dynamic -lpthread

# Debug mode can be enabled by executing `make DEBUG=1 rule_name`
DEBUG := 0

ifneq ($(DEBUG), 0)
	OPTFLAGS = -O0
	CFLAGS += -g -pg -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
	CPPFLAGS += -DDEBUG # define DEBUG like `#define DEBUG` in all C files
endif


### SOURCES PART ###

# Dir where all build files will be stored
BUILD_DIR := ./_build

# use bash
SHELL := $(shell which bash)
