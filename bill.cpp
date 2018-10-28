#include<iostream>
using namespace std;

//Simple shopping bill calculator program

  int main()
   {
   system("cls");
   cout<<"*****RECIEPT*****\n";
   cout<<"\n\nEnter the number of items\n";
   int n=0,i;
   cin>>n;
   float total=0,cost;

   //loop for finding the total
   for(i=1;i<=n;i++)
    {
     cout<<"Enter the cost of item "<<i<<"\n";
     cost=0;
     cin>>cost;
     total+=cost;
    }

   cout<<"\n************************************\n* Number of items="<<n;
   cout<<"\n* The total amount to be paid is "<<total<<" bucks";
   cout<<"\n************************************";
   cout<<"\n\n\n\n*****THANK YOU PLEASE VISIT AGAIN*****";

  return 0;
  }
