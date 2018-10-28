#include<conio.h>
#include<iostream>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
using namespace std;

//progrram to count the number of alphabets, vowels, digits and words in a string

  int main()
   {
    system("cls");
    int i,alphacount=0,vowelcount=0,degitcount=0,wordcount=0;
    char a[50];  //storing the string
    cout<<"\tEnter a string to count\n\t";
    gets(a);

    for(i=0;a[i]!='\0';i++)
    {
     //count the number of vowels
     if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u')
      vowelcount++;
     else if(a[i]=='A'||a[i]=='E'||a[i]=='I'||a[i]=='O'||a[i]=='U')
      ++vowelcount;

     //count the number of alphabets
     if(isalpha(a[i]))
      alphacount++;

     //count the number of digits
     if(isdigit(a[i]))
      ++degitcount;

     //count the number of words
     if(a[i]==' ')
      ++wordcount;    //count if a space occures
    }

    cout<<"\n\nThe number of words ="<<wordcount+1;   //we did not count the first word
    cout<<"\nThe number of vowels ="<<vowelcount;
    cout<<"\nThe number of digits ="<<degitcount;
    cout<<"\nThe number of alphabets ="<<alphacount;
    return 0;
   }
