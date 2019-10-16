/**
 * Factorial of a very large number, say 100. It would be of 158 digits long. We will store the result in a vector.
 * We can do this by doing normal multiplication algorithm, however we will store digits in an array.
 * let's just take an example of normal multiplication of 189 to 10, output would be 1890.
 * so step store digits of 189 in a vector in reverse order.
 * result[] = { 9, 8, 1 }
 * m = 10
 * prod = 1
 * carry = 0
 * i = 0 --> prod = result[0] * m + carry = 9 * 10 + 0  = 90
 * result[0] = 0 , carry = 9
 *
 * i = 1 --> prod = result[1] * m + carry = 8 * 10 + 9 = 89
 * result[1] = 9, carry = 8
 *
 * i = 2 --> prod = result[2] * m + carry = 1 * 10 + 8 = 18
 * result[2] = 8, carry = 1
 *
 * result[3] = carry = 1
 *
 * result = { 0, 9, 8, 1 }
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

// look at above example to understand this function
void multiply( std::vector<int> &  result, int m )
{
    int carry = 0;
    for (unsigned int i = 0; i < result.size(); ++i ) {
        int prod = result[i] * m + carry;
        result[i] = prod % 10;
        carry = prod / 10;
    }
    
    while( carry ) {
        result.push_back(carry % 10 );
        carry /= 10;
    }
}

std::vector<int> factorial( int n )
{
    std::vector<int> result{ 1 };
    for ( int i = 2; i <= n; ++i ) {
        multiply(result, i);
    }

    return result;
}

void print_num( std::vector<int> & vec )
{
     for(std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
     {
                         std::cout << *it;
     }
    std::cout << std::endl;
}


int main()
{
    std::cout << "Program for calculating large number factorial\n";
    std::cout << "Enter a number:";
    int n;
    std::cin >> n;
    std::vector<int> res = factorial(n);
    print_num(res);
    return 0;
}
