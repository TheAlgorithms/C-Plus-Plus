/**
 * @file
 * @brief gives the reverse of the no. given as input
 * @details
 * For example,
 * The input is: 123
 * The output will be: 321
 * description containing links, references,
 * math equations, etc.
 * @rutvi02 [Rutvi] (https://github.com/rutvi02)
 * @see related_file.cpp, another_file.cpp// none
 */
#include <iostream>  
using namespace std;  
int main()  
{  
int n=0, reverse=0, rem=0;  
  //Taking input from the user
cout<<"Enter a number: ";    
cin>>n;    
  while(n!=0)    
  {    
    // using basic math equationd
     rem=n%10;      
     reverse=reverse*10+rem;    
     n/=10;    
  }    
  //returning the output
 cout<<"Reversed Number: "<<reverse<<endl;     
return 0;  
}  
