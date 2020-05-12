// C++ program to find factorial of given number
#include<iostream>

// function to find factorial of given number
// recursive approach
unsigned int factorial_rec(unsigned int n) {
    if (n == 0)
        return 1;
    return n * factorial_rec(n - 1);
}

// iterative approach
unsigned int factorial_iter(unsigned int n) {
    if (n == 0)
        return 1;
    
    unsigned int result = 1 , i;
    for(i=2 ; i<=n ; ++i)
        result *= i;
    
    return result;
}

// Driver code
int main() {
    int num = 5;
    std::cout << "Factorial of " << num << " is " << factorial_rec(num)
              << std::endl;
    return 0;
}
