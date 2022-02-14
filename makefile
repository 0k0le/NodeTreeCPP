#
# Build file

node.bin: node.o
	g++ node.o -o node.bin

node.o: node.cpp
	g++ node.cpp -Wall -Wextra -pedantic -c -o node.o

clean:
	rm -f node.o node.bin
