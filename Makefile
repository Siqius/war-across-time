# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Directories
SRC_DIR = src
OBJ_DIR = target
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target output
TARGET = $(OBJ_DIR)/WarAcrossTime

# Libraries
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Create target directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Main target
all: $(TARGET)

# Linking the target binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compiling .cpp files to .o files in the target directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
