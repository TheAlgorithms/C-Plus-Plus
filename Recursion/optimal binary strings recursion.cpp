/* #Count binary strings
count the no. of binary strings of length N  which have no consecutive ones?
example N=2,
00
01
11    this is not a valid case
10
so the total no. of strings is 3.*/
#include<iostream>
using namespace std;
int f(int n){
	if(n==0){
		return 1;
	}
	if(n==1){
		return 2;
	}
	return f(n-1)+f(n-2);
}
int main(){
	int n;
	cin>>n;
	cout<<f(n);
	return 0;
}
