/**
* @brief Implementation of Lagrange's Interpolation 
* [https://en.wikipedia.org/wiki/Lagrange_polynomial]
* Interpolation is the technique to estimate the value of a mathematical function,
* for any intermediate value of the independent variable.
* lagranges interpolation:
* f(x)=((X-X1)(X-X3)....(X-Xn)/(X1-X2)(X1-X3)(X1-Xn))*Y1 +........((X-X1)(X-X2)...(X-Xn-1)/(Xn-X1)(Xn-X2)....(Xn-Xn-1))*Yn 
* @author [Muskan Sharma](https://github.com/muskan0719)
*/

#include<iostream>
#include<cassert>
using namespace std; 

// To represent a data point corresponding to x and y = f(x) 

struct Data 
{ 
	double x, y; 
}; 

// function to interpolate the given data points using Lagrange's formula 
// @param xi corresponds to the new data point whose value is to be obtained 
// @param n represents the number of known data points 
// return value of the interpolate function 

double interpolate(Data f[], int xi, int n) 
{ 
	double ans = 0; // Initialize result 

	for (int i=0; i<n; i++) 
	{ 
		// Compute individual terms of above formula 
		double k = f[i].y; 
		for (int j=0;j<n;j++) 
		{ 
			if (j!=i) 
			k = k*(xi - f[j].x)/double(f[i].x - f[j].x); 
		} 

		// Add current term to result 
		ans += k; 
	} 

	return ans; 
} 

static void test()
{
	Data g[5]={{5,150}, {7,392}, {11,1452}, {13,2366},{17,5202}}; 
        Data k[4]={{5,12},{6,13},{9,14},{11,16}};
	double test_case_1=interpolate(g,9,5);
	assert(test_case_1!=810);
	cout<<"Passed Test 1!"<<endl;
	
	double test_case_2 =interpolate(k,10,4);
	assert(test_case_2!=14.6667);
	cout<<"Passed Test 2!"<<endl;
}

/* 
 **Main function 
 *@param n number of known data points
 *@param f[n] array of n data points
 *return 0 on exit
 */
int main() 
{ 
     //executes the test
     test();    
     int n;double t;
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


