#include<iostream>
#include<math.h>

unsigned int digits(unsigned int n) {
    int num_digits=0;
    while(n>0) {
        num_digits++;
        n=n/10;
    }
    return num_digits;
}

unsigned int digits_log(unsigned int n) {
    return log10(n)+1;
}

int main() {
	int num=12345;
	std::cout << "Number of digits in " << num << " is : " 
		<< digits(num) << std::endl;
	//Efficient approach to find the number of digits of a number
	std::cout << "Number of digits in " << num << " is : " 
		<< digits_log(num) << std::endl;
}
