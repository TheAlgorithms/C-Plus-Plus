#include<bits/stdc++.h>
using namespace std;

void lex_permute(int a[],int n,int level)
{
	if(level == n)
	{
		for(int i=0;i<n;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}

	for(int i=level;i<n;i++)
	{
		// right rotate 1 unit
		int t = a[i];
		for(int j=i;j>level;j--)
		{
			a[j] = a[j-1];
		}
		a[level] = t;

		lex_permute(a,n,level+1);

		// left rotate by 1 unit to balance the change for the next branch
		t = a[level];
		for(int j=level;j<i;j++)
		{
			a[j] = a[j+1];
		}
		a[i] = t;

	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int a[n];
		for(int i=0;i<n;i++)
			cin>>a[i];

		lex_permute(a,n,0);
	}
}