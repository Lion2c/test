# Makefile for C project
CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = 
TARGET = test
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Find all .c files in src directory
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(BIN_DIR)/$(TARGET)

test: all
	@echo "Running tests..."
	# Add test commands here

.PHONY: all clean run test