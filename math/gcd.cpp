#include <iostream>
using namespace std;

// GCD using Euclidean Algorithm
// Time Complexity: O(log(min(a, b)))
// Space Complexity: O(1)

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a = 36, b = 60;
    cout << "GCD is: " << gcd(a, b);
    return 0;
}
