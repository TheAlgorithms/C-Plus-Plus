#include<iostream>
#include<stdio.h>
#include<ctype.h>
using namespace std;


//Converting a given string to proper case

  int main()
   {
    system("cls");
    int i,length=1,x=0;
    char a[100];
    cout<<"enter the string\n";
    gets(a);
    cout<<"\nthe correct form is\n";

    //finding the length of the string
    //you can also use the inbuilt function strlen()
    for(i=0;a[i]!='\0';i++)
     length++;

    //first letter should be upper case
    a[0]=toupper(a[0]);

    for(i=0;i<length;i++)
     if(a[i]==' ')
      {
       x=i+1;     //position of the letter in the string after a space
       a[x]=toupper(a[x]);       //initilizing letter after a space to upper case
      }

    puts(a);
    return 0;
  }
