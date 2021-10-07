/**
 * @fast_fourier_transform.cpp
 * @brief A fast Fourier transform (FFT) is an algorithm that computes the 
 * discrete Fourier transform (DFT) of a sequence, or its inverse (IDFT).
 * @details
 * https://medium.com/@aiswaryamathur/understanding-fast-fourier-transform-from-scratch-to
  -solve-polynomial-multiplication-8018d511162f
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include<iostream>
#include<cmath>
#include<complex>
#include <cassert>
# define pi    3.14159265358979323846 
using namespace std;

/**
 * @brief FastFourierTransform is a recursive function which returns list of complex numbers
 * @param p List of Coefficents in form of complex numbers
 * @param n Count of elements in list p
 * @returns p if n==1
 * @returns y if n!=1
 */

complex<double>* FastFourierTransform(complex<double>*p,int n)
{

	if(n==1) return p; ///Base Case To return 

	complex<double> om=complex<double>(cos(2*pi/n),sin(2*pi/n));  ///Calculating value of omega

	complex<double> *pe= new complex<double>[n/2]; /// Coefficents of even power

	complex<double> *po= new complex<double>[n/2]; ///Coefficents of odd power

	int k1=0,k2=0;
	for(int j=0;j<n;j++)
	{
		if(j%2==0){
			pe[k1++]=p[j]; ///Assigning values of even coefficents

		}
		else po[k2++]=p[j]; ///Assigning value of odd coefficents


	}

	complex<double>*ye=FastFourierTransform(pe,n/2);///Recursive Call
	
	complex<double>*yo=FastFourierTransform(po,n/2);///Recursive Call

	complex<double>*y=new complex<double>[n];///Final value representation list


	for(int i=0;i<n/2;i++)
	{
		y[i]=ye[i]+pow(om,i)*yo[i]; ///Updating the first n/2 elemnts
		y[i+n/2]=ye[i]-pow(om,i)*yo[i];///Updating the last n/2 elemnts
	}

	return y;///Return the list 
	
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* descriptions of the following test */
    
    complex<double> t1[2]={1,2};///Test case 1
	
	complex<double> t2[4]={1,2,3,4};///Test case 2
		


	int n1=sizeof(t1)/sizeof(complex<double>);
	int n2=sizeof(t2)/sizeof(complex<double>);

    
    complex<double> r1[2]={{3,0},{-1,0} };///True Answer for test case 1
	
	complex<double> r2[4]={{10,0},{-2,-2},{-2,0},{-2,2} };///True Answer for test case 2
		

    complex<double> *o1=FastFourierTransform(t1,n1);
    complex<double> *o2=FastFourierTransform(t2,n2);
    
    
    for(int i=0;i<n1;i++)
    {
        assert(r1[i].real()-o1->real()<0.000000000001 and r1[i].imag()-o1->imag()<0.000000000001 );
        o1++;
    }
    
    for(int i=0;i<n2;i++)
    {
        assert(r2[i].real()-o2->real()<0.000000000001 and r2[i].imag()-o2->imag()<0.000000000001  );
        o2++;
    }
    
    
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
 

int main(int argc, char const *argv[])
{
	
	
   test();
    
	return 0;
}