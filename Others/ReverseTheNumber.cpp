//This program reverse the number that you entered
#include <iostream>

int reverse(int num){

    int newNumber{0};

        while(num>0)
        {
            newNumber=10*newNumber+num%10;
            num/=10;
        }

        return newNumber;
}

int main(){

    int number;
	std::cout << "Enter a number:";
	std::cin >> number;
    std::cout << "Reversed number is: " << reverse(number);

    return 0;
}
