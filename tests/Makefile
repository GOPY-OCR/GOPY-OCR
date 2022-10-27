# This Makefile should be called after everything is build by the main Makefile
include ../compile_settings.mk

TARGETS = NeuralNetwork Preprocess Utils Solver
BUILD_DIR := ../_build
TEST_DIR := $(BUILD_DIR)/tests
$(shell mkdir -p $(TEST_DIR)/NeuralNetworkTests $(TEST_DIR)/PreprocessTests $(TEST_DIR)/UtilsTests $(TEST_DIR)/SolverTests)

LDLIBS += -lcriterion
INCLUDE_DIRS = $(shell find ../src/ -type d)

SRC_OFILES = 
define ofiles
	$(shell find $(BUILD_DIR)/src/$(1)/ -type f -name "*.o") \
		$(shell find $(1)Tests/ -type f -name "test.c" | echo "$(TEST_DIR)/$(1)Tests/"`xargs basename -s .c`).o \

		$(wildcard $(BUILD_DIR)/src/Utils/*.o)


endef

all: MainBuild $(TARGETS)

.SECONDEXPANSION:
NeuralNetwork: $(call ofiles,NeuralNetwork)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	./$@

.SECONDEXPANSION:

Preprocess: $(call ofiles,Preprocess)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	./$@

.SECONDEXPANSION:
Utils: $(call ofiles,Utils)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	./$@

.SECONDEXPANSION:
Solver: $(call ofiles,Solver)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	./$@

# Same rule for all .o files
$(TEST_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)


MainBuild:
	$(MAKE) -C ..

clean:
	rm -rf $(TEST_DIR) $(TARGETS)

.PHONY: clean
