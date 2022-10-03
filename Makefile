TARGET_EXEC := main

BUILD_DIR := ./build
SRC_DIRS := ./src


SRCS := src/main.c
# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.c.o turns into ./build/hello.c.d
DEPS := $(OBJS:.o=.d)

CFLAGS := -Wall -Wextra -O3 -g 
# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step 
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C tests clean
	$(MAKE) -C src/GUI clean
	$(MAKE) -C src/NeuralNetwork clean
	$(MAKE) -C src/NeuralNetwork/data clean
	$(MAKE) -C src/Preprocess clean
	$(MAKE) -C src/Solver clean

format:
	find -name "*.[ch]" | xargs clang-format -i

all: $(BUILD_DIR)/$(TARGET_EXEC) GUI NeuralNetwork Preprocess Solver

GUI:
	$(MAKE) -C src/GUI

NeuralNetwork: Preprocess
	$(MAKE) -C src/NeuralNetwork

Preprocess:
	$(MAKE) -C src/Preprocess

Solver:
	$(MAKE) -C src/Solver


check: $(BUILD_DIR)/$(TARGET_EXEC)
	$(MAKE) -C tests check 
