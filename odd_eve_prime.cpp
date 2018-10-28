#include<iostream>
#include<stdio.h>
using namespace std;

//Display if the the given number is odd-even or prime until the user wants.


 int main()
  {
   system("cls");
   int num,flago=0,flagp=0,flage=0,flag=0;
   char choice[4];
   cout<<"Enter the number\n";
   cin>>num;

   do
    {
     //checking prime
     for(int i=0;i<num/2;i++)
       if(num%i!=0)
         flagp=1;
     //checking even
     if(num%2==0)
      flage=1;
    //checking odd
    else
      flago=1;

    //displaying
    if(flagp==1)
     cout<<"The number is a prime\n";
    else if(flage==1)
     cout<<"The number is even\n";
    else if(flago==1)
     cout<<"The number is odd\n";

    cout<<"\n\nDo you want to continue?\n";
    cout<<"YES or NO\n";
    gets(choice);
    if(choice=="yes"||choice=="YES")
     flag=1;
    }
   //continue if user wants
   while(flag==1);

   return 0;
  }

