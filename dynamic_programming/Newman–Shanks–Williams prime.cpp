Recurrence relation for Newman–Shanks–Williams prime is:

S_0 = 1
S_1 = 1
S_n = 2*S_{n-1} + S{n-2} 
The first few terms of the sequence are 1, 1, 3, 7, 17, 41, 99, ….



#include <bits/stdc++.h> 
using namespace std; 

int ns_wp(int ns) 
{ 
	
	if(ns == 0 || ns == 1) 
	{ 
		return 1; 
	} 
	
	int a ,b;
	a=1 , b= 1;
	
	for(int i = 2; i <= ns; ++i) 
	{ 
		int c = 2 * b + a; 
		a = b; 
		b = c; 
	} 
	return b; 
} 
int main() 
{ 
	int ns;
	cin>>ns;
	cout << ns_wp(ns); 
	return 0; 
} 
