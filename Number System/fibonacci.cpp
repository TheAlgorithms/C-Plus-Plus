#include <iostream>
using namespace std;


/*
	Efficient method for finding nth term in a fibonacci number sequence.
	Uses Dvide and conquer approach
	Enter Values from 1
	Eg-
	1st term = 0;
	2nd term = 1;
	3rd term = 1;
	.
	.
	.
	.
*/
int a[2][2] = {{1,1},{1,0}};//fibonacci matrix
int ans[2][2] = {{1,1},{1,0}};//final ans matrix
/*
	Working Principal:

	[F(k+1)	  F(k)]   [1  1]^k
	|             | = |    |
	[F(k)	F(k-1)]   [1  0]

	where F(k) is the kth term of the Fibonacci Sequence. 


*/

void product(int b[][2],int k[][2])
{
	/*
		Function for computing product of the two matrices b and k
		and storing them into the variable ans.

		Implementation :
		Simple matrix multiplication of two (2X2) matrices.
	*/
	int c[2][2];//temporary stores the answer
	c[0][0] = b[0][0]*k[0][0]+b[0][1]*k[1][0];
	c[0][1] = b[0][0]*k[0][1]+b[0][1]*k[1][1];
	c[1][0] = b[1][0]*k[0][0]+b[1][1]*k[1][0];
	c[1][1] = b[1][0]*k[0][1]+b[1][1]*k[1][1];
	ans[0][0] = c[0][0];
	ans[0][1] = c[0][1];
	ans[1][0] = c[1][0];
	ans[1][1] = c[1][1];
	
} 

void power_rec(int n)
{	

	/*
		Function for calculating A^n(exponent) in a recursive fashion

		Implementation:
		A^n = { A^(n/2)*A^(n/2) 			if n is even
			  { A^((n-1)/2)*A^((n-1)/2)*A   if n is odd
	*/
	if((n == 1)||(n==0))
		return;
	else
	{
		if((n%2) == 0)
		{	
			power_rec(n/2);
			product(ans,ans);
			
		}	
		else
		{
			power_rec((n-1)/2);	
			product(ans,ans);
			product(ans,a);
			
		}
	}
}

int main()
{
	//Main Function
	cout <<"Enter the value of n\n";
	int n;
	cin >>n;
	if(n == 1)
	{
		cout<<"Ans: 0"<<endl;
	}
	else
	{	
		power_rec(n-1);
		cout <<"Ans :"<<ans[0][1]<<endl;
	}
	return 0;
}

