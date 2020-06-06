/*
    * reducing all possibilities of a number which cannot be prime.
    * eg: No even number, except 2 can be a prime number, hence we will increment our loop with i+2 jumping on all odd numbers only.
    * if number is <= 1 or if it is even except 2, return false telling number is no prime.
*/
#include<iostream>
using namespace std;

int isPrime(int);

int isPrime(int no) {

	int isPrime = 1;

	if(no <= 1) {
		return(0);
	} else if (no == 2) {
		return(1);
	} else if ((no&1) == 0) {
		return(0);
	}

	if(no >= 3) {
		for(int i = 3 ; i < (no/2+1) ; i = i+2) {
			if((no%i) == 0) {
				isPrime = 0;
				break;
			}
		}
	}
	return(isPrime);
}

int main() {
    int n;
    cout<<"Enter the number to check if it is prime or not"<<endl;
    cin>>n;
    int result = isPrime(n);
    if(result) {
        cout<<n<<" is a prime number"<<endl;
    } else {
        cout<<n<<" is not a prime number"<<endl;
    }
    return(0);
}