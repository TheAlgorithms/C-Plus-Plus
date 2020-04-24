CC= g++
CFLAGS = -c -Wall

all: cll
cll.o: cll.cpp main_cll.cpp
	$(CC) $(CFLAGS) cll.cpp main_cll.cpp
cll: cll.o
	$(CC) main_cll.o cll.o -o cll

clean:
	rm *o cll
