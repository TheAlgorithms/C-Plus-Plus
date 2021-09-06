/**
 * @file
 * @brief [swaping two numbers using XOR bitwise]
 * @details
 * Given two numbers as input. The goal is to swap those numbers.
 * What is swapping? 
 * Swapping means exchanging the content.
 * Suppose we have two buckets 'A' and 'B' one has 5 apples and other has 2 apples.
 * Then after performing swap bucket 'A' will have 2apples and bucket 
 * 'B' will have 5.
 * @author [Uttam kumar](https://github.com/helper-uttam)
 */
 
#include <iostream>   // for IO operations

using namespace std;

namespace bit_manipulation {
/**
 * @namespace hamming_distance
 * @brief Functions for [Hamming
 * distance](https://en.wikipedia.org/wiki/Hamming_distance) implementation
 */
namespace swap {

/*function to swap two values*/
void swap_XOR(int *first, int *second){   //passing pointers
      // swaping code
    *first = *first ^ *second;   //doing XOR of first and second and assigning to first
    *second = *first ^ *second;  //doing XOR of first and second and assigning to second
    *first = *first ^ *second;   //doing XOR of first and second and assigning to first
}
/*
As we are using call by referance, so we don't need to return anything after swapping 
because we are changing the values at the address of orginial variables which will led 
to change of the values in the original variables inself.
*/
}  // namespace hamming_distance
}  // namespace bit_manipulation


static void test() {
    assert(bit_manipulation::swap::swap_XOR(11, 2) == (2,11));
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    int a = 20; //initializing first variable named "a" with 20
    int b = 30; //initializing second variable named "b" with 30
    int *ptr1 = &a;  //pointer pointing to first variable
    int *ptr2 = &b; //pointer pointing to second variable
    test();  // execute the tests
 //Printing Values of A and B before swapping.
  std::cout<<"The Value of A before swaping is = "<<a<<"\n";
  std::cout<<"The Value of B before swaing is = "<<b<<"\n";
  
    swap_XOR(ptr1,ptr2);    /* here we are passing two pointers which is also known as pass by reference in which we 
  pass address of variable instead of the value*/
 
 //Printing Values of A and B after swapping.
   std::cout<<"The Value of A after swaping is = "<<a<<"\n";
   std::cout<<"The Value of B after swaping is = "<<b<<"\n";
    
    return 0; 
}
