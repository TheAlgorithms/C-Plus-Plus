#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
int main()
{
	lli v,E;
	cin >>v >> E;
	lli arr[v+1][v+1];
	for(lli j=1;j<=v;j++)
		{
			for(lli p=1;p<=v;p++)
			{
				if(j!=p)
				arr[j][p]=1000000;
			else
				arr[j][p]=0;

			}
		}

	for(lli i=0;i<E;i++)
	{
		lli v1,v2,wt;
		cin >>v1>>v2>>wt;
		arr[v1][v2]=wt;
		arr[v2][v1]=wt;
	}
	for(lli i=1;i<=v;i++)
	{
		lli k=i;
		for(lli j=1;j<=v;j++)
		{
			for(lli p=1;p<=v;p++)
			{
				if(arr[j][p] > (arr[j][k]+arr[k][p]))
				{
					arr[j][p] = (arr[j][k]+arr[k][p]);
				}
			}
		}
	}
	for(lli j=1;j<=v;j++)
		{
			for(lli p=1;p<=v;p++)
			{
				cout <<arr[j][p]<<" ";
			}
			cout <<endl;
		}
		return 0;
}
