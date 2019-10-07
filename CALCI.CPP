#include<iostream.h>
#include<conio.h>
void main()
{
clrscr();
char ch;
float a,b,result;
cout<<"Enter two numbers";
cout<<"\n\nEnter first no.:";
cin>>a;
cout<<"\nEnter second no.:";
cin>>b;
cout<<"\n"<<"Enter oprerator:";
cin>> ch ;
cout<<"\n";
if(ch=='-')
{ result=a-b;
cout<<"\nResult="<<result; }
 else if(ch=='+')
 { result=a+b;
 cout<<"\nResult="<<result; }
  else if(ch=='*')
  { result=a*b;
  cout<<"\nResult="<<result; }
   else if(ch=='/')
   { result=a/b;
   cout<<"\nResult="<<result; }
    else
    {cout<<"Wrong operator";}
getch();
}
