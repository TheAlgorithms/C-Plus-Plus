/**
 * @file
 * \@brief Program to find sum of binomial coefficients of a given positive integer.
 * Given a positive integer n, the task is to find the sum of binomial coefficient i.e
 * nC0 + nC1 + nC2 + ……. + nCn-1 + nCn
 * By induction, we can prove that the sum is equal to 2^n
 * [https://en.wikipedia.org/wiki/Binomial_coefficient#Sums_of_the_binomial_coefficients]
 * @author muskan0719[https://github.com/muskan0719]
 */
#include<iostream>
#include<cassert>
using namespace std; 

/** 
 * @param n number
 * @return Sum of binomial coefficients of number 
 */
int binomialCoeffSum(int n) 
{ 
    //Calculating 2^n  
	return (1 << n); 
}
/**
 * Function for testing the binomialCoeffSum() function
 */ 
static void test()
{
	int test_case_1=binomialCoeffSum(4);
	assert(test_case_1==16);
	cout<<"Test_case_1 Passed!"<<endl;
	int test_case_2=binomialCoeffSum(5);
	assert(test_case_2==32);
	cout<<"Test_case_2 Passed!"<<endl;
 } 

/* Main function*/
int main() 
{ 
    test();
	int number;
	cout<<"Enter the value of n"<<endl;
	cin>>number;
	assert(number>=0);
    cout<<"Sum of binomial coefficient is "<<binomialCoeffSum(number)<<endl;
	return 0; 
} 

