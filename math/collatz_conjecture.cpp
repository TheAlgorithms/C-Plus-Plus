/**
 * @file 
 * @brief The conjecture is that no matter what value of n, the sequence will always reach 1.
 * @details 
 * The Collatz conjecture is a conjecture in mathematics 
 * that concerns a sequence defined as follows: 
 * start with any positive integer n. 
 * Then each term is obtained from the previous term as follows: 
 * if the previous term is even, the next term is one half of the previous term. 
 * If the previous term is odd, the next term is 3 times the previous term plus 1.
 * link : https://en.wikipedia.org/wiki/Collatz_conjecture
 * @author [Deepak Agrawal](https://github.com/DebugAgrawal)
 */

#include<iostream>
using namespace std;
int main()
{
	int n=0,i,j,cnt,start,max=0;
	for(i=1;i<20;i++)
	{
		n=i;
		do
		{ 
			if((n%2)==0)
			{
				n=n/2;					
			}
			else
			{
				n=((3*n)+1);				
			}
			cnt++;
			if(cnt>max)
			{
				max=cnt;
				start=i;
			}			
		}while(n>1);
		cnt=0;
	}			
	cout<<start;
	return 0;
}