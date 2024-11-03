# Compiler
CC = clang

# Compiler flags
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g

# Use pkg-config to get Raylib flags
RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS = $(shell pkg-config --libs raylib)

# Shared Source Files
# Include all .c files in src/** except for src/main.c
SHARED_SRC = $(shell find src -name '*.c' ! -name 'main.c')
# Source files
SRC = ./src/main.c $(SHARED_SRC)
# Test files
TEST_SRC = $(wildcard ./tests/*.c) $(SHARED_SRC)

# Output binary folder and name
BUILD_DIR = ./build
FORTH_DIR = $(BUILD_DIR)/forth
OUT = $(BUILD_DIR)/crForth
TEST_OUT = $(BUILD_DIR)/crForth_test

# Build target
all: $(BUILD_DIR) $(OUT)

# Compile and run tests
test: $(TEST_OUT)
	./$(TEST_OUT)

# Create the build folder if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Copy forth files only if they have changed
$(FORTH_DIR): $(BUILD_DIR)
	mkdir -p $(FORTH_DIR)
	rsync -u src/forth/*.fth $(FORTH_DIR)


# Compile main executable
$(OUT): $(FORTH_DIR) $(SRC)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -o $(OUT) $(SRC) $(RAYLIB_LIBS)

$(TEST_OUT): $(FORTH_DIR) $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -o $(TEST_OUT) $(TEST_SRC) $(RAYLIB_LIBS)


# Clean target to remove the binary
clean:
	rm -rf $(BUILD_DIR)
