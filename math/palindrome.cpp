// This file demonstrates to check weather a number is palindrome or not

#include<iostream>
using namespace std;
int main()
{
	int n,a[50],i=0,p=0;
  //Input the number
	cin>>n;
	while(n>0)
	{
		a[i]=n%10;
		n=n/10;
		i++;
	}
	for(int j=0;j<i/2;j++)
	{
		if(a[j]!=a[i-j-1])
		{
			p=1;
			break;
		}
	}
	if(p==0)
	cout<<"no is palindrome";
	else
	cout<<"no is not palindrome";
	return 0;
}

/*Example test case:
i/p : 121  o/p: no is palindrome
i/p : 123 o/p: no is not palindrome
*/
