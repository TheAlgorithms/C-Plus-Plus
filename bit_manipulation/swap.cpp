/**
 * @file
 * @brief [swaping two numbers using XOR bitwise]
 * @details
 * Given two numbers as input. The goal is to swap those numbers.
 * What is swaping? 
 * Swaping means exchanging the content.
 * Suppose we have two buckets 'A' and 'B' one has 5 apples and other has 2 apples.
 * Then after performing swap bucket 'A' will have 2apples and bucket 
 * 'B' will have 5.
 * @author [Uttam kumar](https://github.com/helper-uttam)
 */
 
#include <iostream>   // for IO operations
using namespace std;

void swap_XOR(int *first, int *second){   //passing pointers
      // swaping code
    *first = *first ^ *second;
    *second = *first ^ *second;
    *first = *first ^ *second;
}

int main()
{
    int a = 20;
    int b = 30;
    int *ptr1 = &a;  //pointer pointing to first variable
    int *ptr2 = &b; //pointer pointing to second variable
  
  cout<<"The Value of A before swaping is = "<<a<<"\nThe Value of B before swaing is = "<<b;
  
    swap_XOR(ptr1,ptr2); //passing both pointers
  /* here we are passing pointers which is also called pass by reference in which we 
  pass address of variable instead of the value*/
    cout<<"\n\nThe Value of A after swaping is = "<<a<<"\nThe Value of B after swaing is = "<<b;
    return 0;
}
