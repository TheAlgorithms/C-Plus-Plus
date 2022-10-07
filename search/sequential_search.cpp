#include<iostream.h>
#include<conio.h>
main()
{
int arr1[5];
int req;
int location=-5;
cout<<"Enter 5 numbers to store in array: "<<endl;
for(int i=0; i<5; i++)
{
cin>>arr1[i];
}
cout<<endl;
cout<<"Enter the number you want to find :";
cin>>req;
cout<<endl;
 
for(int w=0;w<5;w++)
{
if(arr1[w] == req)
location=w;
}
if(location !=-5)
{
cout<<"Required number is found out at the location:"<<location+1;
cout<<endl;
}
else
cout<<"Number is not found ";
getch();
}