BUILD_DIR := ./build
SRC_DIR := ./

SRCS := $(shell find $(SRC_DIR) -name '*.c')

CFLAGS = -lcriterion

$(BUILD_DIR)/test: $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/test.c -o $(BUILD_DIR)/test

check: $(BUILD_DIR)/test
	$(BUILD_DIR)/test
	@echo "Ok"
clean:
	rm -rf $(BUILD_DIR)
