#include<bits/stdc++.h>
using namespace std;
struct nodes{
	int v1,v2,wt;
};
vector <struct nodes > g;
vector <int> arr;
int v,E;
int bmfd()
{
	for(int i=0;i<v;i++)
	{
		int count =0;
		vector <int> vis(v+1,0);
		for(int j=0;j<E;j++)
		{
			int s1=g[j].v1;
			int s2=g[j].v2;
			int w =g[j].wt;
			if(arr[s2] > arr[s1]+w )
			{
				arr[s2]=arr[s1]+w;
				if(vis[s2]==0)
				{
					count ++ ;
					vis[s2]=1;
				}
			}
		}
		if(i==v-1 && count !=0)
		{
			return 1;
		}
		else if(count == v)
		{
			return 1;
		}
		else if(count == 0)
		{
			return 0;
		}
	}
	return 0;
}
int main() 
{
	cin >> v >> E;
	arr.resize(v+1);
	for(int i=0; i<E;i++)
	{
		struct nodes a;
		cin >> a.v1 >> a.v2 >> a.wt;
		g.push_back(a);		
	}
	for(int i=1;i<=v;i++)
	{
		arr[i]=10000;
	}
	arr[1]=0;
	int p =bmfd();
	if(p==1)
	{
		cout << "NEGATIVE CYCLE EXISTS!" ;
	}
	else
	{
		for(int i=1;i<=v;i++)
		{
			cout << i << ":" << arr[i] <<" "; 
		}
	}
	cout << endl;
}
