#include<bits/stdc++.h>
using namespace std;

void print(long long arr[],long long n)
{
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
}

pair<long long,long long> partition3(long long arr[],long long l,long long r )
{
	pair <long long,long long> par;
	long long i=l,j,k=l,p=r;
	while(i<p)
	{
		if(arr[i]<arr[r])
			swap(arr[i++],arr[k++]);
		else if(arr[i]==arr[r])
			swap(arr[i],arr[--p]);
		else
			i++;
	}
	// print(arr,r+1);
	// cout<<endl;
	// cout<<k<<" "<<p<<endl;
	long long temp=arr[r],end;
	for(i=p-1,j=r;i>=k;i--,j--)
		arr[j]=arr[i];
	end=j;
	for(j;j>=k;j--)
		arr[j]=temp;
	// print(arr,r+1);
	// cout<<endl<<end;
	par=make_pair(k,end);
	return par;
}

void sort(long long arr[],long long l,long long r)
{
	if(l<r)
	{
		int k=l+rand()%(r-l+1);
		swap(arr[l],arr[k]);
		pair<long long,long long> par=partition3(arr,l,r);
		sort(arr,l,par.first-1);
		sort(arr,par.second+1,r);
	}
}
bool checkSorted(long long arr[],long long n)
{
	int i;
	for(i=0;i<n-1;i++)
		if(arr[i]>arr[i+1])
			return false;
	return true;
}

int main()
{
	long long n,arr[100010];
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	sort(arr,0,n-1);
	print(arr,n);
	// partition3(arr,0,n-1);
	return 0;
}

// int main()
// {
// 	long long n,ini[1000],temp,arr[1000],i;
// 	n=100;
// 	while(1)
// 	{
// 		srand(time(0));
// 		for(i=0;i<n;i++)
// 		{
// 			temp=rand()%4;
// 			arr[i]=temp;
// 			ini[i]=temp;
// 		}
// 		sort(arr,0,n-1);
// 		if(checkSorted(arr,n)==false)
// 		{
// 			print(ini,n);
// 			cout<<endl;
// 			print(arr,n);
// 			return 0;
// 		}
// 	}
// 	return 0;
// }