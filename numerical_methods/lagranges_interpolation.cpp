/*
@brief C++ program for implementation of Lagrange's Interpolation 
https://en.wikipedia.org/wiki/Lagrange_polynomial
Interpolation is the technique to estimate the value of a mathematical function,
for any intermediate value of the independent variable.
lagranges interpolation:
f(x)=((X-X1)(X-X3)....(X-Xn)/(X1-X2)(X1-X3)(X1-Xn))*Y1 +........((X-X1)(X-X2)...(X-Xn-1)/(Xn-X1)(Xn-X2)....(Xn-Xn-1))*YN
*/
#include<bits/stdc++.h> 
using namespace std; 

// To represent a data point corresponding to x and y = f(x) 
struct Data 
{ 
	int x, y; 
}; 

// function to interpolate the given data points using Lagrange's formula 
// xi corresponds to the new data point whose value is to be obtained 
// n represents the number of known data points 
double interpolate(Data f[], int xi, int n) 
{ 
	double result = 0; // Initialize result 

	for (int i=0; i<n; i++) 
	{ 
		// Compute individual terms of above formula 
		double term = f[i].y; 
		for (int j=0;j<n;j++) 
		{ 
			if (j!=i) 
				term = term*(xi - f[j].x)/double(f[i].x - f[j].x); 
		} 

		// Add current term to result 
		result += term; 
	} 

	return result; 
} 

// driver function to check the program 
int main() 
{ 
     int n,t;
     cout<<"Enter the number of known data points"<<endl;
     cin>>n;
     cout<<"Enter the value of new data point whose value needs to be obtained"<<endl;
     cin>>t;
   // creating an array of n known data points 
    Data f[n] ; 
    for(int i=0;i<n;i++)
    {
    	cout<<"Enter the value of x"<<endl;
    	cin>>f[i].x;
    	cout<<"Enter the corresponding value of y"<<endl;
    	cin>>f[i].y;
	}
	
	// Using the interpolate function to obtain a data point 
	// corresponding to x=t 
	cout << "Value of f("<<t<<") is : " << interpolate(f, t, n); 

	return 0; 
} 

