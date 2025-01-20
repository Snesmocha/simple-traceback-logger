# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99

# Set the default main file
MAIN_FILE = main.c

TEST ?= default

# Select the main file based on the TEST variable
ifeq ($(TEST), default)
    MAIN_FILE = main_test1.c
else ifeq ($(TEST), filesave)
    MAIN_FILE = main_test2.c
else ifeq ($(TEST), redirect)
    MAIN_FILE = main_test3.c
endif

# Output directory and file
BUILD_DIR = build
OUTPUT = $(BUILD_DIR)/program

# Default target
all: $(OUTPUT)

# Create build directory if it doesn't exist and compile the program
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUTPUT): $(BUILD_DIR) $(MAIN_FILE)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(MAIN_FILE)

# Clean up the build directory
clean:
	rm -rf $(BUILD_DIR)

# Run the program from the build directory
run: $(OUTPUT)
	$(BUILD_DIR)/program

.PHONY: all clean run
