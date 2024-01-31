# Compiler
CXX = g++

# Include directories for header files
INCLUDES = -I/opt/local/include

# Library directories for libraries
LDFLAGS = -L/opt/local/lib

# Libraries to link
LDLIBS = -lglfw -lglew -framework OpenGL

# Source files
SRCS = main.cc list.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Executable name
EXE = visualizer

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(INCLUDES) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.cc.o:
	$(CXX) $(INCLUDES) -c $<

clean:
	rm -f $(OBJS) $(EXE)
