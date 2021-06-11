/** program to Count set bits in an integer 
* @file
* Time Complexity :- O(log n)
* Space complexity :- O(1)

**/
#include <bits/stdc++.h>
using namespace std;
 
/* Function to get no of set bits in binary
representation of positive integer n */
unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0; // "count" variable is used to count number of 1's in binary representation of the number
    while (n!=0) {
        count += n & 1;
        n >>= 1; // n=n/2 
    }
    return count;
}
 
/* Main Program to test function countSetBits */
int main()
{
    int t; // Variable t is used for number of test cases
	unsigned int n; // Number whose count of set bits is to be calculated 
    cin>>t; 
    while(t--){
	cin>>n;
    cout << countSetBits(n)<<endl;
}
    return 0;
}
 
