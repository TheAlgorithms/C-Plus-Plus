// Program for sieve of Atkin
// sieve of atkin is the modern successor algorithm of sieve of eratosthenes
#include <bits/stdc++.h> 
using namespace std; 
// function for sieve of atkin
int Sieve_A(int end) 
{ 
	
	if (end > 2) 
		cout << 2 << " "; 
	if (end > 3) 
		cout << 3 << " "; 	
	bool arr[end]; 
	for (int i = 0; i < end; i++) 
		arr[i] = 0; 

	for (int l = 1; l * l < end; l++) { 
		for (int m = 1; m * m < end; m++) { 
					int n = (4 * l * l) + (m * m); 
			if (n <= end && (n % 12 == 1 || n % 12 == 5)) 
				arr[n] ^= 1; 

			n = (3 * l * l) + (m * m); 
			if (n <= end && n % 12 == 7) 
				arr[n] ^= 1; 

			n = (3 * l * l) - (m * m); 
			if (l > m && n <= end && n % 12 == 11) 
				arr[n] ^= 1; 
		} 
	} 

	for (int r = 5; r * r < end; r++) { 
		if (arr[r]) { 
			for (int i = r * r; i < end; i += r * r) 
				arr[i] = 0; 
		} 
	} 


	for (int a = 5; a < end; a++) 
		if (arr[a]) 
			cout << a << " "; 

            return 1;
} 

    
int main() 
{ 
	int last;
    //number upto which the primes are to be searched
    cin>>last;
	Sieve_A(last); 
	return 0; 
} 
