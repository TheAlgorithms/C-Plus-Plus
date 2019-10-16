#include<bits/stdc++.h>
using namespace std;

// using static vector
void lex_subsets(int a[],int n,int level)
{
	static vector<int> temp;
	
	for(int i=0;i<temp.size();i++)
		cout<<temp[i]<<" ";
	cout<<endl;

	
	if(level<n)
	{
		for(int i=level;i<n;i++)
		{
			temp.push_back(a[i]);
			lex_subsets(a,n,i+1);
			temp.pop_back();

		}
	}
}

// using auxilliary array
void lex_subsets2(int a[],int n,int aux[],int c,int level)
{
	
	for(int i=0;i<c;i++)
		cout<<aux[i]<<" ";
	cout<<endl;

	
	if(level<n)
	{
		for(int i=level;i<n;i++)
		{
			aux[c] = a[i];
			lex_subsets2(a,n,aux,c+1,i+1);

		}
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

		int level = 0;
		lex_subsets(a,n,level);
		cout<<endl;
		int aux[n];
		int c = 0;
		level = 0;
		lex_subsets2(a,n,aux,c,level);
	}
}