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
int a[2][2] = {{1,1},{1,0}};
int I[2][2] = {{1,0},{0,1}};
int ans[2][2] = {{1,1},{1,0}};

void product(int b[][2],int k[][2])
{
	int c[2][2];
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
}