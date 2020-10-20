/**
 * @file 
 * @brief This program computes the N^th Fibonacci number in modulo mod
 * input argument .
 *
 * Takes O(logn) time to compute nth Fibonacci number
 * 
 *
 * \author [villayatali123](https://github.com/villayatali123)
 * \author [unknown author]()
 * @see fibonacci.cpp, fibonacci_fast.cpp, string_fibonacci.cpp, fibonacci_large.cpp
 */

#include<iostream>
#include<vector>
#include <cassert>

/**
 * This function finds nth fibonacci number in a given modulus
 * @param n nth fibonacci number
 * @param mod  modulo number 
 */
uint64_t fibo(uint64_t n , uint64_t mod )
{
	std::vector<uint64_t> result(2,0);
	std::vector<std::vector<uint64_t>> transition(2,std::vector<uint64_t>(2,0));
	std::vector<std::vector<uint64_t>> Identity(2,std::vector<uint64_t>(2,0));
	n--;
	result[0]=1, result[1]=1;
	Identity[0][0]=1; Identity[0][1]=0;
	Identity[1][0]=0; Identity[1][1]=1;
	 
	transition[0][0]=0;
	transition[1][0]=transition[1][1]=transition[0][1]=1;
	
	while(n)
	{
		if(n%2)
		{
			std::vector<std::vector<uint64_t>> res(2, std::vector<uint64_t>(2,0));
	                for(int i=0;i<2;i++)
			{
				for(int j=0;j<2;j++)
				{
					for(int k=0;k<2;k++)
						{
							res[i][j]=(res[i][j]%mod+((Identity[i][k]%mod*transition[k][j]%mod))%mod)%mod;
						}
				}
			}
		       	for(int i=0;i<2;i++)
			{
				for(int j=0;j<2;j++)
				{
				Identity[i][j]=res[i][j];
				}
	    		}
			n--;
		}
		else{
			std::vector<std::vector<uint64_t>> res1(2, std::vector<uint64_t>(2,0));
			for(int i=0;i<2;i++)
			{
				for(int j=0;j<2;j++)
				{
					for(int k=0;k<2;k++)
					{
						res1[i][j]=(res1[i][j]%mod+((transition[i][k]%mod*transition[k][j]%mod))%mod)%mod;
					}
				}
			}
			for(int i=0;i<2;i++)
			{
				for(int j=0;j<2;j++)
				{
					transition[i][j]=res1[i][j];
				}
			} 
			n=n/2;
			}
	}
	return ((result[0]%mod*Identity[0][0]%mod)%mod+(result[1]%mod*Identity[1][0]%mod)%mod)%mod;
}

/**
 * Function to test above algorithm
 */
void test()
{
    assert(fibo(6, 1000000007 ) == 8);
    std::cout << "test case:1 passed\n";
    assert(fibo(5, 1000000007  ) == 5);
    std::cout << "test case:2 passed\n";
    assert(fibo(10 , 1000000007) == 55);
    std::cout << "test case:3 passed\n";
    assert(fibo(500 , 100) == 25);
    std::cout << "test case:3 passed\n";
    assert(fibo(500 , 10000) == 4125);
    std::cout << "test case:3 passed\n";
    std::cout << "--All tests passed--\n";
}

/**
 * Main function
 */
int main()
{
	test();
	uint64_t mod=1000000007;
	std::cout<<"Enter the value of N: ";
	uint64_t n=0; std::cin>>n; 
	std::cout<<n<<"th Fibonacci number in modulo " << mod << ": "<< fibo( n , mod) << std::endl;
}
