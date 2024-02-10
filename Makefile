# Compiler
CXX = g++

CXXFLAGS = -std=c++11

DEPENDENCIES_DIR = dependencies

# Include directories for header files
INCLUDES = -I$(DEPENDENCIES_DIR)/include

# Library directories for libraries
LDFLAGS = -L$(DEPENDENCIES_DIR)/lib


# Libraries to link
LDLIBS = -lglfw -lglew -framework OpenGL -lfreetype

# Source files
SRCS = main.cc list.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Executable name
EXE = visualizer

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compile and run the program
run: $(EXE)
	./$(EXE)

# Compile the source files
.cc.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

# Clean up
clean:
	rm -f $(OBJS) $(EXE)
