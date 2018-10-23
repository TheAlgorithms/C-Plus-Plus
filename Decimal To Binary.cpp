#include<iostream>
using namespace std;
int main(){
	int number;
	cout <<"Enter number to find its binary : ";
	cin>>number;
	int remainder,binary=0,var=1;

	do{
		remainder = number%2;
		number /= 2;
		binary += (remainder*var);
		var *= 10;
	}while(number>0);
	cout<<binary;
	return 0;
}
