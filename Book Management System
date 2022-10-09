#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cctype>
#include<string.h>

using namespace std;

class donate
{
	char pname[50],bname[50][50];
	int qty;

	public:
		void getinfo();
		void showinfo();

};

void donate::getinfo()
{
	cout<<"Enter your name:\n";
	cin.ignore();
	gets(pname);
	strupr(pname);
	cout<<"Enter the number of books you want to donate:\n";
	cin>>qty;
	cout<<"Enter the name of the book(s) you want to donate:\n";
	for(int i=0;i<=qty;i++)
	{
		//cin>>bname[i];
		cin.getline(bname[i],100);
	}
}

void donate::showinfo()
{
	cout<<"\nName: ";
	puts(pname);
	cout<<"Book you've donated: ";
	for(int i=0;i<=qty;i++)
	{
		cout<<bname[i]<<endl;
	}
	cout<<endl;
}

int main()
{
    //creating text files

    /*ofstream books,category;
    books.open("name.txt");
    category.open("cat.txt");*/

    //Welcome Screen
    int n;
    char name[50],word[20],c;
    do
    {
	cout << "\t\t\t\t\tWelcome to the Store" << endl<<"\t\t\t\t\t********************\n";
    cout<<"Select one of the following:\n\n";
    cout<<"1. Search for the book\n";
    cout<<"2. View all the books\n";
    cout<<"3. View all the categories\n";
    cout<<"4. Donate a book\n";
    cout<<"5. Quit\n";
    cout<<"\n******************************************\n\n";

    //Selecting the choice
    cin>>n;


    if(n==1)
        {
        	int p=0;
        	cout<<"Type the name of the book\n";
        	cin.ignore();
        	cin.getline(name,100);
        	//converting the name into upper or lower case will reduce the issue of case senstivity while searching
        	// strupr(name);	This can also be used to covert the string in upper case
			for(int i=0;i<strlen(name);i++)
        	{
        		if(name[i]>=97 && name[i]<=122)
        		{
        			name[i]-=32;
				}
			}
        	ifstream books;
        	books.open("name.txt");
        	while(!books.eof())
        	{
        		books.getline(word,100);
        		if((strcmp(word,name))==0)
        		p=1;
			}
			if(p==1)
			cout<<"This Book is available";
			else
			cout<<"Sorry,The Book is not available";
		}

    if(n==2)
    	{
    		ifstream books;
    		books.open("name.txt");
    		while(!books.eof())
    		{
    			books.getline(word,100);
    			puts(word);
			}
		}

    if(n==3)
    	{
    		ifstream category;
    		category.open("cat.txt");
    		while(!category.eof())
    		{
    			category.getline(word,100);
    			puts(word);
			}
		}

	if(n==4)
	{
		donate a;
		a.getinfo();
		a.showinfo();	
	}
	if(n==5)
	{
		exit(0);
	}
	cout<<"\nDo you wish to conitnue?\nY or N\n";
	cin>>c;
	c=toupper(c);
	}while(c=='Y');
return 0;
}
