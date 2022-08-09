/**
 * Copyright 2020 @author LeeYiTien
 *
 * @file
 * A very short program to determine the number is prime or not
 *
 * @brief
 * the loop start with i=2 as i<
 * inside the loop, if it is a prime number it will return true,otherwise false.
 * the termination of the loop is when i<sqrt(number)+1
 */

#include <cassert>   /// for assert
#include<iostream> /// for IO operations
#include<cmath> /// for math operation
/**
 *  Function to check if the given number is prime or not.
 *  @return if number is prime, it returns @ true, else it returns @ false.
 */
template <typename T>
bool is_prime(T number){
    bool result = true;
    for(int i=2;i<sqrt(number)+1;i++){
        if(number%i==0){
            return false;
        }
    }
    return true;
}

/**
 * Main function
 */
int main(){
    // perform self-test
    assert(is_prime(50) == false);
    assert(is_prime(115249) == true);
    
    int num = 0;
    std::cout << "Enter the number " << std::endl;
    std::cin >> num;
    bool result = is_prime(num);
    if (result) {
        std::cout << num << " is a prime number" << std::endl;
    } else {
        std::cout << num << " is not a prime number" << std::endl;
    }
    return 0;
}