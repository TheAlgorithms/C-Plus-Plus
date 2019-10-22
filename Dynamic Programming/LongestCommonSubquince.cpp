/* A Naive recursive implementation of LCS problem */
#include <bits/stdc++.h> 
using namespace std; 

int max(int a, int b); 

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char *X, char *Y, int m, int n ) 
{ 
	if (m == 0 || n == 0) 
		return 0; 
	if (X[m-1] == Y[n-1]) 
		return 1 + lcs(X, Y, m-1, n-1); 
	else
		return max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n)); 
} 

/* Utility function to get max of 2 integers */
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Driver code */
int main() 
{ 
	char X[] = "AGGTAB"; 
	char Y[] = "GXTXAYB"; 
	
	int m = strlen(X); 
	int n = strlen(Y); 
	
	cout<<"Length of LCS is "<< lcs( X, Y, m, n ) ; 
	
	return 0; 
} 
