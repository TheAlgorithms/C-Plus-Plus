//Program To Print Mystery Series
#include<iostream.h>
#include<conio.h>
void main()
{
int mys=1,num;
clrscr();
cout<<"Enter Last Number Of Series: ";
cin>>num;
cout<<endl<<"\t________________Mystery Series Upto "<<num<<"_______________"<<endl<<endl;
while(1)
{
 ++mys;
 if((mys%3)==0)
 continue;
 if(mys==num)
 break;
 if((mys%2)==0)
 {
 mys=mys+3;
 }
 else
 {
 mys=mys-3;
 }
 cout<<mys<<" ";
}
cout<<endl;
getch();
}