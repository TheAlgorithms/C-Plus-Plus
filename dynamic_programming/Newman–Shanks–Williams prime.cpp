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
