#include<iostream>
using namespace std;

//A program to count the sum of all odd or even numbers till the user wants

 int main()
  {
   system("cls");
   int limit,evsum=0,odsum=0;
   cout<<"Enter the limit\n";
   cin>>limit;

   //loop to add the numbers
   for(int i=0;i<=limit;i++)
      {
       //sum of even numbers
       if(i%2==0)
         evsum+=i;
       else
	     odsum+=i;
	}

   cout<<"The sum of all the odd numbers ="<<odsum;
   cout<<"\nThe sum of all the even numbers="<<evsum;

   return 0;
  }
