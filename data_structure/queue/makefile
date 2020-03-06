CC= g++
CFLAGS = -c -Wall

all: test_queue
queue.o: queue.cpp
	$(CC) $(CFLAGS) queue.cpp
test_queue: queue.o
	$(CC) test_queue.cpp queue.o -o queue

clean:
	rm *o queue
