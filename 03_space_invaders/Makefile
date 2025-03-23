CXX = g++

OPT = -O0

CXXFLAGS = -std=c++23 -Wall -Wextra -Werror $(OPT)
LDFLAGS = -lglfw -lGLEW -lGL

TARGET = main.out
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
