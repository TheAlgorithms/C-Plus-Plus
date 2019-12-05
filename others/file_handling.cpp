/*
Opening file1.txt,file2.txt by constructor function, writing data into them along with extracting data from them and printing on the screen.
Different objects to be used to open different files while using constructor function.
*/

#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	int x,y;
	cout<<"Enter integer data to be inserted in first file:";
	cin>>x;
	ofstream outf1("file1.txt:",ios::out); //Opening file1.txt using constructor method in ios::out mode
	outf1<<x; // Writing data to file1.txt
	cout<<"\nData inserted to file";
	outf1.close();


	ifstream inf1("file1.txt",ios::in); //Opening file1.txt using constructor method in ios::in mode
	inf1>>x; // Reading data from file1.txt
	cout<<"\nPrinting data of first file on the screen\n";
	cout<<x;
	inf1.close();
	
	cout<<"\n\nEnter integer data to be inserted in second file:";
	cin>>y;
	ofstream outf2("file2.txt:",ios::out); //Opening file2.txt using constructor method in ios::out mode
	outf2<<y; // Writing data to file2.txt
	cout<<"\nData inserted to file";
	outf2.close();


	ifstream inf2("file2.txt",ios::in); //Opening file2.txt using constructor method in ios::in mode
	inf2>>y; // Reading data from file2.txt
	cout<<"\nPrinting data of second fie on the screen\n";
	cout<<y;
	inf2.close();
	
	return 0;
}
