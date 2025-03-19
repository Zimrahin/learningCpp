# A parametrised version of the makefile in 00_makefile_example

# The C++ compiler to use.
CXX = g++

# Compiler flags:
# -Wall    : Enables all the common warning messages.
# -Wextra  : Enables extra warning messages not covered by -Wall.
# -std=c++17 : Sets the C++ standard to C++17.
# -O2     : Applies a moderate level of optimization to the code.
CXXFLAGS = -Wall -Wextra -std=c++23 -O2

# TARGET defines the name of the final executable that will be generated.
TARGET = main

# SOURCES lists all the C++ source files in the project.
SOURCES = main.cpp date.cpp

# OBJECTS is a variable that transforms the list of source files in SOURCES into object files (.o).
# The pattern substitution '%.cpp=%.o' tells make to replace the .cpp extension with .o.
OBJECTS = $(SOURCES:.cpp=.o)

# The 'all' target is the default target. Typing 'make' without arguments will build this target.
all: $(TARGET)

# Linker
# It states that the TARGET depends on all the object files listed in $(OBJECTS).
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
# $(OBJECTS) are the object files, and '-o $(TARGET)' specifies the output executable name.

# This is a pattern rule that tells make how to compile each .cpp file into a .o object file.
# $< represents the first prerequisite (the .cpp file), and $@ is the target (the .o file).
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# -c flag: compile the source files into object files (.o files) but not link them

# When you run 'make clean', it will remove all the object files and the final executable,
# allowing you to start a fresh build.
clean:
	rm -f $(OBJECTS) $(TARGET)
# '-f' flag forces removal without prompting for confirmation.
