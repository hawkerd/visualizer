# Compiler
CXX = g++

CXXFLAGS = -std=c++11 -g

# Directory for dependencies
DEPENDENCIES_DIR = dependencies
# Directory for executables and object files
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj_dir

# Include directories for header files
INCLUDES = -I$(DEPENDENCIES_DIR)/include -I/dependencies/imgui

# Library directories for libraries
LDFLAGS = -L$(DEPENDENCIES_DIR)/lib

# Libraries to link
LDLIBS = -lglfw -lglew -framework OpenGL

# Source files
# IMGUI_SRCS = $(wildcard dependencies/imgui/*.cpp) $(wildcard dependencies/imgui/backends/*.cpp)
SRCS = $(wildcard src/*.cc) # $(IMGUI_SRCS)

# Object files (placed in OBJ_DIR)
OBJS = $(patsubst src/%.cc,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
EXE = visualizer

# Default target
all: $(EXE)

$(EXE): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: src/%.cc
	mkdir -p $(OBJ_DIR)
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

# Compile and run the program
run: $(EXE)
	./$(BIN_DIR)/$(EXE)

# Clean up
clean:
	rm -rf $(BIN_DIR)
