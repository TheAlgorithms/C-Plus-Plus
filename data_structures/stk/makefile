CC= g++
CFLAGS = -c -Wall

all: main test_stack
stack.o: stack.cpp
	$(CC) $(CFLAGS) stack.cpp
test_stack: stack.o
	$(CC) test_stack.cpp stack.o -o stk
main: stack.o
	$(CC) main.cpp stack.o -o main

clean:
	rm *o stk main
