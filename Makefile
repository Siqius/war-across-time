# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Directories
SRC_DIR = src
OBJ_DIR = target
BUILD_DIR = target/build

# Platform detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    # Linux settings
    TARGET = $(BUILD_DIR)/WarAcrossTime
    LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
    INCLUDE_DIR = /usr/include
else ifeq ($(UNAME_S), MINGW64_NT)
    # Windows (MSYS2 MinGW64)
    TARGET = $(BUILD_DIR)/WarAcrossTime.exe
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    INCLUDE_DIR = /mingw64/include
else
    $(error Unsupported platform: $(UNAME_S))
endif

# Source and object files
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Create build directories
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Compile step
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
