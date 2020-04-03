#include<iostream>


int sum_of_d(int num){
	int sum = 1;
	int prime = 2;
	
	while(prime*prime <= num && num>1){
		if(num%prime == 0){
			int j = prime*prime;
			num = num / prime;
			while(num%prime == 0){
				j=j*prime;
				num = num/prime;
			}
			sum *= (j-1);
			sum /= (prime-1);
		}
		if(prime == 2)
			prime = 3;
		else
			prime+=2;
	}
	if(num>1)
		sum*=(num+1);
	return sum;
}

int sum_of_divisors(int num){
	return sum_of_d(num) - num;
}

/*
int sum_of_divisors(int num){
	int sum = 0;
	for(int i=1; i<=num/2; ++i){
		if(num%i == 0){
			sum += i;
		}
	}
	return sum;
}
*/


int main(){
	int sum = 0;
	for(int i=1; i<10000; ++i){
		int num1 = sum_of_divisors(i);
		if(i<num1){
			if(sum_of_divisors(num1) == i){
				sum += num1 + i;
			}
		}
	}
	std::cout<<"The sum of all Amicable numbers under 10000 is: "<<sum<<std::endl;
	return 0;
}
