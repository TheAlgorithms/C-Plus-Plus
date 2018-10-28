#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;


//To print the reverse of a string, without using a library function

 int main()
 {
  system("cls");
  int length,i,length2;
  char str[80],rev[80];
  cout<<"enter the array\n";
  gets(str);

  length=strlen(str);
  length2=length;

  //reversing the string
  for(i=0;i<length;i++,length2--)
    rev[length2]=str[i];

  //cout the reversed string
  cout<<"\n\nafter reverse string=\n";
  for(i=0;i<length+1;i++)
    cout<<rev[i];
  return 0;
 }
