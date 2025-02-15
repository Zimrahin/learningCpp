# target: dependencies
# 	action

# The action will link 'main.o' and 'message.o' together to create the 'output' executable.
# -o flag: specify output name
output: main.o message.o
	g++ main.o message.o -o output

# The action will compile 'message.cpp' into the object file 'message.o'.
# -c flag: compile the source files into object files (.o files) but not link them

main.o: main.cpp
	g++ -c main.cpp

message.o: message.cpp message.h
	g++ -c message.cpp

clean:
	rm *.o output
