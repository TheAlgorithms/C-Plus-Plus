/**
 * @file fibonacci_matrix_exponentiation.cpp
 * @brief Computes N^th Fibonacci number given as
 * input argument
 *
 * Takes O(logn) time to compute nth Fibonacci number
 * 
 *
 * \author [villayatali123](https://github.com/villayatali123)
 * \author [unknown author]()
 * @see fibonacci.cpp, fibonacci_fast.cpp, string_fibonacci.cpp, fibonacci_large.cpp
 */
/* @details
 *Begin 
 * Take two 2 dimensional vector
 * Create a function and Perform matrix multiplication
 * Ceate another function to find out power of matrix
 * Create a function then to find out the Fibonacci number
 * Multiply(arr1[2][2], arr2[2][2], int size)
 * Take 4 variables a, b, c, d
 * a = arr1[0][0] * arr2[0][0] + arr1[0][1] * arr2[1][0]
 * b= arr1[0][0] * arr2[0][1] + arr1[0][1] * arr2[1][1]
 * c = arr1[1][0] * arr2[0][0] + arr1[1][1] * arr2[1][0]
 * d = arr1[1][0] * arr2[0][1] + arr1[1][1] * arr2[1][1]
 * arr1[0][0] = a
 * arr1[0][1] = b
 * arr1[1][0] = c
 * arr1[1][1] = d
 * Power(arr1[2][2], take integer n as input)
 * if (n == 0 or n == 1)
 *    return;
 * arr1 [2][2] = {{1,1}, {1,0}}
 * power(arr1, n / 2)
 * multiply(arr1, arr1)
 * if (n mod 2 not equal to 0)
 * multiply(arr1, arr2)
 * fibonacci_matrix(n)
 * arr1[2][2] = {{1,1}, {1,0}}
 * if n ==0
 *    return 0
 *    power(arr1 n - 1)
 * return arr1[0][0]
End
*/

#include<bits/stdc++.h>
typedef long long ll;
const long long mod = 1000000007;
std::vector<ll> a(2);
std::vector<std::vector<ll>> t(2,std::vector<ll>(2));
std::vector<std::vector<ll>> I(2,std::vector<ll>(2));
/**
 * This function multiplies two matrix.
 * @param a 2d-vector 
 * @param b 2d-vector
 * @param m size of vector
 */ 
void mul(std::vector<std::vector<ll>> &a,std::vector<std::vector<ll>> &b,int m)
{
	
	std::vector<std::vector<ll>> res(2,std::vector<ll>(2,0));
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++){
			for(int k=0;k<m;k++)
			{
				res[i][j]=(res[i][j]%mod+((a[i][k]%mod*b[k][j]%mod))%mod)%mod;
			}
		}
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			a[i][j]=res[i][j];
		}
	}
}
/**
 * This function finds nth fibonacci number.
 * @param n nth fibonacci number
 */
ll fibo(ll n)
{
	n--;
	a[0]=1, a[1]=1;
	I[0][0]=1; I[0][1]=0;
	I[1][0]=0; I[1][1]=1;
	 
	t[0][0]=0;
	t[1][0]=t[1][1]=t[0][1]=1;
	
	n;
	while(n)
	{
		if(n%2)
		{
			mul(I,t,2); n--;
		}
		else{
			mul(t,t,2); n=n/2;
		}
	}
	return ((a[0]%mod*I[0][0]%mod)%mod+(a[1]%mod*I[1][0]%mod)%mod)%mod;
}
/**
 * Function to test above algorithm
 */
void test()
{
	assert(fibo(6) == 8);
    std::cout << "test case:1 passed\n";
    assert(fibo(5) == 5);
    std::cout << "test case:2 passed\n";
    assert(fibo(10) == 55);
    std::cout << "test case:3 passed\n";
    std::cout << "--All tests passed--\n";
}
/**
 * Main function
 */
int main()
{
	test();
	std::cout<<"Enter the value of N: ";
	ll n; std::cin>>n; 
	std::cout<<n<<"th Fibonacci number :"<<fibo(n); 
}
