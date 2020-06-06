#include<iostream>
int isPrime (int);
int isPrime (int no) {
    int isPrime = 1;
    if (no <= 1) {
        return 0;
    } else if (no == 2) {
        return 1;
    } else if (no & 1 == 0) {
        return 0;
    }
    if (no >= 3) {
        for (int i = 3 ; i < (no / 2 + 1) ; i = i + 2) {
            if ( no % i  == 0) {
                isPrime = 0;
                break;
            }
        }
    }
    return isPrime;
}

int main () {
    int n;
    std::cout << "Enter the number to check if it is prime or not" << std::endl;
    std::cin >> n;
    int result = isPrime(n);
    if (result) {
        std::cout << n << " is a prime number" << std::endl;
    } else {
        std::cout << n << " is not a prime number" << std::endl;
    }
    return 0;
}
