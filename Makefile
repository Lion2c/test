# Makefile for C project - Snake Game
CC = gcc
CFLAGS = -Wall -Wextra -I./include -D_DARWIN_C_SOURCE
LDFLAGS = -lncurses
TARGET = snake_game
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Snake game source files
SNAKE_SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/snake.c $(SRC_DIR)/game_logic.c $(SRC_DIR)/ui.c
SNAKE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SNAKE_SRCS))

# Original test project source files
TEST_SRCS = $(filter-out $(SNAKE_SRCS), $(wildcard $(SRC_DIR)/*.c))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

all: snake

# Snake game target
snake: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(SNAKE_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(SNAKE_OBJS) -o $@ $(LDFLAGS)

# Original test project target
test_proj: $(TEST_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(TEST_OBJS) -o $(BIN_DIR)/test_proj

# Compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: snake
	./$(BIN_DIR)/$(TARGET)

# Test the original example project
run_example: test_proj
	./$(BIN_DIR)/test_proj

# Run unit tests
test: 
	@echo "Running snake game tests..."
	# Add test commands here

.PHONY: all clean run run_example test snake test_proj