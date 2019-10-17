#include <iostream>
 
int countDivisors(int n) {
    if (n < 2) return 1;
    int count = 2; // 1 and n
    for (int i = 2; i <= n/2; ++i) {
        if (n%i == 0) ++count;
    }
    return count;
}
 
int main() {
    int maxDiv = 0, count = 0;
    std::cout << "The first 20 anti-primes are:" << std::endl;
    for (int n = 1; count < 20; ++n) {
        int d = countDivisors(n);
        if (d > maxDiv) {
            std::cout << n << " ";
            maxDiv = d;
            count++;
        }
    }
    std::cout << std::endl;
    return 0;
}
