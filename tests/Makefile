TARGET_EXEC := ./test

BUILD_DIR := ./build
SRC_DIR := ../src

SRCS := $(shell find $(SRC_DIR) ! -name "main.c" -name "*.c")

OBJS := $(SRCS:$(SRC_DIR)/%=$(BUILD_DIR)/%.o)

INCLUDES := ../src/Utils ../src/NeuralNetwork

CPPFLAGS = $(addprefix -I,$(INCLUDES))
CFLAGS = -lcriterion -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDLIBS = `pkg-config --libs sdl2 SDL2_image`
LDFLAGS = -lm

$(TARGET_EXEC): $(OBJS) ./*.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) ./test.c -o $(TARGET_EXEC) $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: check
check: $(TARGET_EXEC)
	$(TARGET_EXEC)
	@echo "Ok"

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)
