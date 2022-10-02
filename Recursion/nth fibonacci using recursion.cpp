#include<iostream>
using namespace std;
int fibonacci(int n){
	//base case
	if(n==0 || n==1){
		return n;  //if n=0,return 0 or n=1,return 1
	}
	//recursive case
	int f1=fibonacci(n-2);
	int f2=fibonacci(n-1);
	return f1+f2;
}
int main(){
	int n;
	cin>>n;
	cout<<fibonacci(n);
	return 0;
}
