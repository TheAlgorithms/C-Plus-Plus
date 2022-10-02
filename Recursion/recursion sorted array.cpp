//write a recursive function to check if array is sorted

#include<iostream>
using namespace std;
bool is_sorted(int a[],int n){
	//base case
	if(n==0 or n==1){
		return true;
		
	}
	//recursive case
	if(a[0]<a[1] and is_sorted(a+1,n-1)){
		return true;
	}
	return false;
	
}
int main(){
	int a[]={1,2,3,4,5};
	int n=sizeof(a)/sizeof(int);
	cout<<is_sorted(a,n);
	return 0;
}

