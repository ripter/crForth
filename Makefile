# Compiler
CC = clang

# Compiler flags
CFLAGS = -std=c99 -Wall -Wextra -pedantic

# Use pkg-config to get Raylib flags
RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS = $(shell pkg-config --libs raylib)

# Source files
SRC = ./src/main.c

# Output binary folder and name
BUILD_DIR = ./build
OUT = $(BUILD_DIR)/crForth

# Build target
all: $(OUT)

# Link the executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(RAYLIB_CFLAGS) -o $(OUT) $(SRC) $(RAYLIB_LIBS)

# Clean target to remove the binary
clean:
	rm -f $(OUT)
