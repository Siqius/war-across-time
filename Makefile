# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Directories
SRC_DIR = src
ASSETS_DIR = assets
OBJ_DIR = target
BUILD_DIR = target/build
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

# Source files (recursive)
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Convert full paths to object files in target
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target output
TARGET = $(BUILD_DIR)/WarAcrossTime

# Libraries
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Create target directory
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(TARGET)

# Link object files into final binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Rule to compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
