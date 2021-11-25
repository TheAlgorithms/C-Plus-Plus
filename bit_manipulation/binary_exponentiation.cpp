/*
    author : @sishir2001
*/
#include <cassert>
#include <iostream>
using namespace std;

long binary_exponention(int x, int n) {
    // @param x : base number
    // @param n : exponent
    // T(N) = O(log(n))
    // S(n) = O(1)
    long res = 1;
    while (n != 0) {
        if (n % 2 == 1) {
            // last bit is 1
            res *= x;
        }
        x *= x;
        n /= 2;
    }
    return res;
}
void test() {
    assert(binary_exponention(2, 2) == 4);
    assert(binary_exponention(3, 2) == 9);
    assert(binary_exponention(4, 2) == 16);
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}