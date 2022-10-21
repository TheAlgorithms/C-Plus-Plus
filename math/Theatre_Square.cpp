#include<iostream>
using namespace std;
int main()
{
	unsigned long long n,m,a;
	cin>>n>>m>>a;
	unsigned long long r=n/a;
	unsigned long long c=m/a;
	if(n%a!=0)
	r++;
	if(m%a!=0)
	c++;
	unsigned long long nf=r*c;
	cout<<nf;
}
