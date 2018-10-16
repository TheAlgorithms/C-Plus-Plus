#include<iostream>
using namespace std;

int main()
{
	int number;
	cout << "Enter Number: ";
	cin>>number;
	int remainder,binary=0,var=1;

	while(number>0) {
		remainder = number%2;
		number /= 2;
		binary = binary + (remainder*var);
		var=var*10;
	}
	cout << "Binary representation: " << binary; 
	
	return 0;
}
