#include<iostream>
using namespace std;

//basic calculator

 int main()
  {
   int num1,num2;
   float ansr;
   char oprtr,option;
   do
     {
      system("cls");
      cout<<"********CALCULATOR********\n";
      cout<<"Enter the two numbers\n";
      cin>>num1>>num2;
      cout<<"\nEnter the operator\n";
      cout<<"* -Multiplication\n+ -Addition\n- -Substraction\n/ -Division\n";
      cin>>oprtr;

      //multiplication
      if(oprtr=='*')
	ansr=num1*num2;
      //addition
      else if(oprtr=='+')
	ansr=num1+num2;
      //substraction
      else if(oprtr=='-')
       ansr=num1-num2;
      //division
      else if(oprtr=='/')
       ansr=num1/num2;
      //if the entered operation not specified here
      else
        {
        cout<<"invald operator\n";
        break;
        }
      cout<<"\nThe answer ="<<ansr<<"\n\n";
      cout<<"Do you want to continue?\nY or N\n";
      cin>>option;
     }
   while(option=='Y'||option=='y');
   return 0;
  }

