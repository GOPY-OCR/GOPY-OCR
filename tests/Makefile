# This Makefile should be called after everything is build by the main Makefile
include ../compile_settings.mk

BUILD_DIR := ../_build
TEST_DIR := $(BUILD_DIR)/tests
$(shell mkdir -p $(TEST_DIR))

LDLIBS += -lcriterion
INCLUDE_DIRS = $(addprefix -I,\
			   ../src/Utils\
			   ../src/NeuralNetwork\
			   )

SRC_OFILES = $(shell find $(BUILD_DIR)/src/$@/ -type f -name "*.o" ! -iname "*main*") \
			 $((shell find $@Tests/ -type f -name "*.c"):%.c=$(TEST_DIR)%.o)

all: $(BUILD_DIR) NeuralNetwork

NeuralNetwork: $(SRC_OFILES)
	echo $(SRC_OFILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ NeuralNetworkTests/test.c -o $@ $(LDFLAGS) $(LDLIBS)
	./$@


# Same rule for all .o files
$(TEST_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR):
	make -C ../

clean:
	rm -rf $(TEST_DIR) NeuralNetwork NeuralNetwork.d

.PHONY: clean
