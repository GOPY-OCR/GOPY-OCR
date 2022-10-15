# Name of the final executable
TARGET := gopy_ocr

include compile_settings.mk
include prettyprint.mk


# Find all subdirectories
SRC_DIRS := $(shell find ./src -type d -not -path "*_build*")

# Create all needed dirs
$(shell mkdir -p $(SRC_DIRS:%=$(BUILD_DIR)/%))

CFILES := $(shell find ./src -type f \( -iname "*.c" ! -iname "*main.c" \)) ./src/main.c
OFILES := $(CFILES:%.c=$(BUILD_DIR)/%.o)
DFILES := $(OFILES:%.o=%.d)

### RULES PART ###

all: $(TARGET)

# Take a look to `prettyprint.mk` to understand $(V) and printtask calls
$(TARGET): $(OFILES)
	$(V)$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	@if [[ $$? == 0 ]]; then \
		$(call printtask,$(GREEN),Linked successfuly:,$@); \
	else \
		$(call printtask,$(RED),Linking failed:,$@); \
	fi;

# Same rule for all .o files
$(BUILD_DIR)/%.o: %.c
	$(V)$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)
	@if [[ $$? == 0 ]]; then \
		$(call printtask,$(GREEN),Compiled successfuly:,$<); \
	else \
		$(call printtask,$(RED),Compilation failed:,$<); \
	fi;

test: $(TARGET)
	$(MAKE) -C tests

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	$(MAKE) clean -C src/GUI
	$(MAKE) clean -C src/NeuralNetwork
	$(MAKE) clean -C src/Preprocess
	$(MAKE) clean -C src/Postprocess
	$(MAKE) clean -C src/Solver
	$(MAKE) clean -C tests

.PHONY: clean test
-include $(D_FILES)
