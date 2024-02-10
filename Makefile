# Compiler
CXX = g++

CXXFLAGS = -std=c++11


# Include directories for header files
INCLUDES = -I/opt/local/include -I/opt/local/include/freetype2

# Library directories for libraries
LDFLAGS = -L/opt/local/lib

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

.cc.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXE)
