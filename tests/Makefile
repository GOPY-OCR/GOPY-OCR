# This Makefile should be called after everything is build by the main Makefile
include ../compile_settings.mk

BUILD_DIR := ../_build
TEST_DIR := $(BUILD_DIR)/tests
$(shell mkdir -p $(TEST_DIR))

SRC_OFILES = $(shell find $(BUILD_DIR)/src/$@/ -type f -name "*.o") $(TEST_DIR)/$@/main.o

all: 

# Compile .o files that are not already
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(TEST_DIR)

.PHONY: clean

