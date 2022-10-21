// C++ program to Count set
// # Method 1

// bits in an integer
#include <bits/stdc++.h>
using namespace std;
 
/* Function to get no of set bits in binary
representation of positive integer n */

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
 
/* Program to test function countSetBits */
int main()
{
    int i;
    cin>>i;
    cout << countSetBits(i);
    return 0;
}


/*

# Method 2

// cpp implementation of recursive approach to find the
// number of set bits in binary representation of positive
// integer n
#include <bits/stdc++.h>
using namespace std;
 
// recursive function to count set bits
int countSetBits(int n)
{
    // base case
    if (n == 0)
        return 0;
    else
        // if last bit set add 1 else add 0
        return (n & 1) + countSetBits(n >> 1);
}
 
// driver code
int main()
{
    int n;
    cin >> n;
    // function calling
    cout << countSetBits(n);
    return 0;
}

*/

/*

# Method 3

// C++ program to Count set
// bits in an integer
#include <iostream>
using namespace std;
class count{
    /* Function to get no of set bits in binary
representation of passed binary no. */

public:
    unsigned int countSetBits(int n)
    {
        unsigned int count = 0;
        while (n) {
            n &= (n - 1);
            count++;
        }
        return count;
    }
};

*/

/*

# Method 4

// CPP implementation for recursive
// approach to find the number of set
// bits using Brian Kernighan’s Algorithm

#include <bits/stdc++.h>
using namespace std;
 
// recursive function to count set bits
int countSetBits(int n)
{
    // base case
    if (n == 0)
        return 0;
    else
        return 1 + countSetBits(n & (n - 1));
}
 
*/

/*

# Method 5

// C++ implementation of the approach
#include <bits/stdc++.h>
using namespace std;
 
int BitsSetTable256[256];
 
// Function to initialise the lookup table
void initialize()
{
 
    // To initially generate the
    // table algorithmically
    BitsSetTable256[0] = 0;
    for (int i = 0; i < 256; i++)
    {
        BitsSetTable256[i] = (i & 1) +
        BitsSetTable256[i / 2];
    }
}
 
// Function to return the count
// of set bits in n
int countSetBits(int n)
{
    return (BitsSetTable256[n & 0xff] +
            BitsSetTable256[(n >> 8) & 0xff] +
            BitsSetTable256[(n >> 16) & 0xff] +
            BitsSetTable256[n >> 24]);
}
 

*/
