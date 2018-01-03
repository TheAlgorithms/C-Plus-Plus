#include <bits/stdc++.h>
using namespace std;

int main()
{
	int i,n,l=0;
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
	{
 	 	scanf("%d",&a[i]);
 	 	if(a[i]>l)
 	 	 l=a[i];
	}
	int b[l+1]={0};
	for(i=0;i<n;i++)
	 b[a[i]]++; //hashing number to array index
	for(i=0;i<(l+1);i++)
	{
		if(b[i]>0)
		{
			while(b[i]!=0) //for case when number exists more than once
			{
				printf("%d ",i); 
				b[i]--;
			}
		}
	}
	return 0;
}