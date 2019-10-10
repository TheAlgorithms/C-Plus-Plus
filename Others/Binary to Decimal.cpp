//Program to convert a binary number to decimal
#include<iostream.h>
#include<maths.h>     /* for pow() */
using namespace std;

int main ()        /* driver code */
{
 int number, i, decimal, digit;
 i=decimal=0;
 cout<<"Enter the number to be converted : ";
 cin>>number;
 while(number>0)
 {
         digit=number%10;
	 decimal+=digit*(pow(2,i));
	 number/=10;
	 i++;
 }
 cout<<"The decimal form of the entered number is "<<decimal;
 return 0;
}
 

 
