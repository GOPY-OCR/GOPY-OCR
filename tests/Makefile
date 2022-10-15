# This Makefile should be called after everything is build by the main Makefile
include ../compile_settings.mk

BUILD_DIR := ../_build
TEST_DIR := $(BUILD_DIR)/tests
$(shell mkdir -p $(TEST_DIR))

LDLIBS += -lcriterion
INCLUDE_DIRS = $(addprefix -I,\
			   $(BUILD_DIR)/src/Utils\
			   )

SRC_OFILES = $(shell find $(BUILD_DIR)/src/$@/ -type f -name "*.o") \
			 $((shell find $@/ -type f -name "*.c"):%.c=$(TEST_DIR)%.o)

all: 


# Same rule for all .o files
$(TEST_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)


clean:
	rm -rf $(TEST_DIR)

.PHONY: clean
