TARGET_EXEC := ./test

BUILD_DIR := ./build
SRC_DIR := ./

SRCS := ../src/NeuralNetwork/matrice.c

OBJS := $(notdir $(SRCS))
OBJS := $(OBJS:%=$(BUILD_DIR)/%.o)

CFLAGS = -lcriterion -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`

$(TARGET_EXEC): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(SRC_DIR)/test.c -o $(TARGET_EXEC)

$(BUILD_DIR)/%.c.o: $(SRCS) $(SRC_DIR)/*.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: check
check: $(TARGET_EXEC)
	$(TARGET_EXEC)
	@echo "Ok"

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)
