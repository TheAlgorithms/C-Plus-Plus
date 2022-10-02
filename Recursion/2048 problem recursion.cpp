#include<iostream>
using namespace std;

char words[][10]={"zero","one","two","three","four","five","six","seven","eight","nine"};
void print_spelling(int n){
	//base case
	if(n==0){
		return;
	}
	//recursive case first print the spellings of (204)
	print_spelling(n/10);
	//after the function call
	int digit=n%10;
	cout<<words[digit]<<" ";
	return;
	
}
int main(){
	int n;
	cin>>n;
	print_spelling(n);
	return 0;
}
