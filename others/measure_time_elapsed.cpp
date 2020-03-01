// To calculate the time taken by a code to execute
#include<sys/time.h>

int64_t getTimeInMicroseconds() {
    struct timeval start;
    gettimeofday(&start, NULL);
    return start.tv_sec * 1000000 + start.tv_usec;
}

// write function sample(args)

int main() {
    // write code
    int64_t starttime = getTimeInMicroseconds();
    // sample(args) function run
    // Any other functions (if present) run
    std:cout << getTimeInMicroseconds() - starttime;
}
