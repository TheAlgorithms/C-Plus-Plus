#include <bits/stdc++.h>
using namespace std;
int fib(int n){
	int res[n+1];
	res[0] = 0;	res[1] = 1;
	for(int i=2;i<=n;i++){
		res[i] = res[i-1] + res[i-2];
	}
	return res[n];
}
int main(int argc, char const *argv[])
{
	int n;
	cout<<"Enter n: ";
	cin>>n;
	cout<<"Fibonacci number is ";
	cout<<fib(n)<<endl;
	return 0;
}