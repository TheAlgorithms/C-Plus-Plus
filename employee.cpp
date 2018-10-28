#include<iostream>
#include<stdio.h>
using namespace std;

//Employee details

struct addr
   {
   int houseno;
   char state[20];
   char country[20];
   };

struct emp
  {
  int empno;
  char name[30];
  addr ad;
  char desig[10];
  }employ[100];

  void display(int,int);
  int main()
    {
    system("cls");
    int empnum,limit,i;
    cout<<"Enter the number of employee\n";
    cin>>limit;
    for(i=0;i<limit;i++)
     {
      cout<<"enter the employ no\n";
      cin>>employ[i].empno;
      cout<<"enter the name\n";
      gets(employ[i].name);
      cout<<"enter tha house no\n";
      cin>>employ[i].ad.houseno;
      cout<<"enter the state\n";
      gets(employ[i].ad.state);
      cout<<"enter tha country\n";
      gets(employ[i].ad.country);
      cout<<"enter the designation\n";
      gets(employ[i].desig);
     }

    cout<<"Enter the employ number to be displayed\n";
    cin>>empnum;
    display(empnum,limit);
    return 0;
    }

 void display(int empno,int limit1)
  {
   int i;
   for(i=0;i<limit1;i++)
    if(empno==employ[i].empno)
      {
       cout<<employ[i].empno;
       puts(employ[i].name);
       cout<<"Address\n";
       cout<<employ[i].ad.houseno;
       puts(employ[i].ad.state);
       puts(employ[i].ad.country);
       puts(employ[i].desig);
      }
   }
