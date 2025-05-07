CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE = .exe
    RAYLIB_INCLUDE = -IC:/raylib/include
    RAYLIB_LIBS = -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RM = del /Q /F
    RMDIR = rmdir /S /Q
else
    DETECTED_OS := Unix
    EXE =
    RAYLIB_INCLUDE = -I/usr/include
    RAYLIB_LIBS = -L/usr/lib -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
    MKDIR = mkdir -p $(OBJDIR)
    RM = rm -f
    RMDIR = rm -rf
endif

TARGET = target/WarAcrossTime$(EXE)
SRCS = src/main.cpp
OBJDIR = target
OBJS = $(OBJDIR)/main.o

CXXFLAGS += $(RAYLIB_INCLUDE)
LDFLAGS += $(RAYLIB_LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/main.o: src/main.cpp
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJS)
	-$(RM) $(TARGET)
	-$(RMDIR) $(OBJDIR)

.PHONY: all clean