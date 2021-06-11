/** * @file
 * @brief program to Count set bits in an integer 
 * @details
 * Time Complexity :- O(log n)
 * Space complexity :- O(1)

**/
#include <iostream>
using namespace std;
 
/* Function to get no of set bits in binary
representation of positive integer n */
unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0; // "count" variable is used to count number of 1's in binary representation of the number
    while (n!=0) {
        count += n&1;
        n=n>>1; // n=n/2 
    }
    return count;
}
 
/* Main Program to test function countSetBits */
int main()
{
    cout << countSetBits(19)<<endl; //binary representation is 10011 so set bits=3
    cout << countSetBits(23)<<endl; //binary representation is 10111 so set bits=4
    cout << countSetBits(25)<<endl; //binary representation is 11001 so set bits=3
    return 0;
}
 
