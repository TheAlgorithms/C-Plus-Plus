#include<iostream>
using namespace std;
//compute a^n
int power(int a,int n){
	if(n==0){
		return 1;
	}
	return a*power(a,n-1);
}
//more efficient way in terms of time and space 
int fast_power(int a,int n){
	if(n==0){
		return 1;
	}
	int smaller_ans=fast_power(a,n/2);
	smaller_ans*=smaller_ans;
	if(n&1){
		return smaller_ans*a;
	}
	return smaller_ans;
	
}
int main(){
	int a,n;
	cin>>a>>n;
	cout<<power(a,n)<<endl;
	cout<<fast_power(a,n);
	return 0;
}
