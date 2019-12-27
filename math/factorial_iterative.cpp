#include <iostream>
#include <stdexcept>

// this function return the factorial of given number iteratively.
unsigned int factorial(int number) {
    if (number < 0) {
        throw std::domain_error("factorial only defined for positive ints > 0");
    }
    int factorial_product = 1;
    for (int i = 2; i <= number; i++) {
        factorial_product *= i;
    }
    return factorial_product;
}


int main() {
    std::cout<< "5 Factorial is " << factorial(5) << std::endl;
    try {
        std::cout<< "-1 Factorial is " << factorial(-1) << std::endl;
    }catch( const std::domain_error& e ) {
        std::cout<< "Error handling was successful" << std::endl;
    }
    std::cout<< "0 Factorial is " << factorial(0) << std::endl;
}
