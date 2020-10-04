//Author : Veer Bhadra Singh Solanki
// C++ Program Reverse String using Stack

#include<iostream>  // include header files
#include<string.h>
using namespace std;

#define size 20 // include preprocessor

int top = -1;    // global variables
char stack[size];

char push(char ch) // Function which push string in stack
{
 if(top==(size-1)) 	// condition check location of top when it equal to size-1 then stack overflows  
  cout<<"Stack is Overflow\n"; 
 else
  stack[++top]=ch; // put char on pre increment top
}

char pop() // Function which pop string in stack
{
 if(top==-1) // condition check location of top when it equal to -1 then stack underflows 
  cout<<"Stack is Underflow\n";
 else
  return stack[top--]; 
}


int main() // main() function from where execution starts
{
 char str[20];  	// define character array of 20 size to take string of length 20
 cout<<"Enter String:\t";
 gets(str); 	// Takes string from user
 int i;
 for(i=0;i<strlen(str);i++) 	// strlen() function present inside string.h header file to calculate length of string
  {
   push(str[i]);		// Testing of push() function
  }
 for(i=0;i<strlen(str);i++)
  {
      str[i]=pop();  // Testing of pop() function
  }
 cout<<"Reversed of String is : ";
 puts(str);	 // Show output to user

	return 0;
}
