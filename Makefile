# Compiler
CXX = g++
CC = gcc
CXXFLAGS = -std=c++11 -g
CFLAGS = -g

# Structure
DEPENDENCIES_DIR = dependencies
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj_dir

# Libraries and such
INCLUDES = -I$(DEPENDENCIES_DIR)/imgui -I$(DEPENDENCIES_DIR)/sqlite -I/opt/local/include
LDFLAGS = -L/opt/local/lib
LDLIBS = -lglfw -lglew -framework OpenGL

# Source files
SQLITE_SRCS = $(wildcard $(DEPENDENCIES_DIR)/sqlite/*.c)
IMGUI_SRCS = $(wildcard $(DEPENDENCIES_DIR)/imgui/*.cpp) $(wildcard $(DEPENDENCIES_DIR)/imgui/backends/*.cpp)
CXX_SRCS = $(wildcard src/*.cc) $(IMGUI_SRCS) 
C_SRCS = $(SQLITE_SRCS)

# Object files (placed in OBJ_DIR)
CXX_OBJS = $(patsubst src/%.cc,$(OBJ_DIR)/%.o,$(CXX_SRCS))
C_OBJS = $(patsubst $(DEPENDENCIES_DIR)/sqlite/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

# Executable name
EXE = visualizer

# Default target
all: $(EXE)

$(EXE): $(CXX_OBJS) $(C_OBJS) $(IMGUI_SRCS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: src/%.cc
	mkdir -p $(OBJ_DIR)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(DEPENDENCIES_DIR)/sqlite/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile and run the program
run: $(EXE)
	./$(BIN_DIR)/$(EXE)

# Clean up
clean:
	rm -rf $(BIN_DIR)
