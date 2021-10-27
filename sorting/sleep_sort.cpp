#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Basic C++ function to use sleep sort. Basically, this function sort a array in a BIG O of O(max(input)+n),
 * using the sleep function. This type of sort is has only an educational purpose, because it is extremely
 * inefficient.
**/
int main() {
	// Instantiates a 5-position array.
	int a[] = {10,9,8,7,6};
	int c = sizeof(a) / sizeof(a[0]);

	// Creates a new process using fork and then makes the program sleep.
	while (--c >= 1 && !fork());
	sleep(c = a[c]);

	// When the sleep process ends, it prints to the user the current number.  
	printf("%d\n", c);
	wait(0);
	return 0;
}
