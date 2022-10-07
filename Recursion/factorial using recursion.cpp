#include<iostream>
using namespace std;
int factorial(int n){
	//base case
	if(n==0){
		return 1;
	}
	//recursive case
	int small_ans=factorial(n-1);
	int ans=n*small_ans;
	return ans;
	/* or simply 
	return n*factorial(n-1);
	*/

}
int main(){
	int n;
	cin>>n;
	cout<<factorial(n)<<endl;
	return 0;
}
