//0-1 Knapsack problem - Dynamic programming
#include <bits/stdc++.h>
using namespace std;
int Knapsack(int capacity,int n,int weight[],int value[]){
	int res[n+1][capacity+1];
	for (int i = 0; i < n+1; ++i)
	{
		for (int j = 0; j < capacity+1; ++j)
		{
			if(i==0||j==0)
				res[i][j] = 0;
			else if(weight[i-1]<=j)
				res[i][j] = max(value[i-1]+res[i-1][j-weight[i-1]], res[i-1][j]);
			else
				res[i][j] = res[i-1][j];
		}
	}
	return res[n][capacity];
}
int main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter number of items: ";
	cin>>n;
	int weight[n], value[n];
	cout<<"Enter weights: ";
	for (int i = 0; i < n; ++i)
	{
		cin>>weight[i];
	}
	cout<<"Enter values: ";
	for (int i = 0; i < n; ++i)
	{
		cin>>value[i];
	}
	int capacity;
	cout<<"Enter capacity: ";
	cin>>capacity;
	cout<<Knapsack(capacity,n,weight,value);
	return 0;
}