#include <stdio.h>

int main(){

   int x = 41;

   int y = 90;

   printf("Values before swapping! \n");

   printf("x = %d \t", x);

   printf("y = %d \n", y);

   x = x ^ y;

   y = y ^ x;

   x = x ^ y;

   printf("Values after swapping! \n");

   printf("x = %d \t", x);

   printf("y = %d \n", y);

   return 0;

} 
