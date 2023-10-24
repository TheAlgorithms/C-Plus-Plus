#pragma once
#include <iostream>
#include <fstream>

using namespace std;

//Defining Node structure for the priority queue
struct node
{
    char data;		//saving character	
    int Freq;		//frequency of that character
    node* next;	//Pointer to next element in the linked queue
    node* prev;	//Pointer to previous element in the linked queue
};

//Defining priority queue specificly designed for this assignment
class Pque
{
private:
    int size;		//Size of the queue
    node* Header;	//External Pointer to the first element

public:
    Pque()  //Default Constructor
    {
	   Header = NULL;
	   size = 0;
    }
    bool isEmpty()
    {
	   if (Header == NULL) //If Header does not exist, there will be no element in the queue
		  return true;
	   else
		  return false;
    }
    //Returns a New Node pointer
    node* GetNode(char d, node* p = NULL, node* n = NULL)
    {	  //Assigning values
	   node* temp = new node;
	   temp->data = d;
	   temp->Freq = 1;
	   temp->prev = p;
	   temp->next = n;
	   return temp;
    }
    void push(char d)   //Function to add character to the queue
    {
	   if (Header == NULL)	  //First ELement Case
	   {
		  Header = GetNode(d, NULL, NULL);
		  size = 1;
	   }
	   else
	   {
		  node* p, * q, * temp;
		  for (p = Header, q = Header->next; q != NULL; p = q, q = q->next)
		  {	 //In case element already exists
			 if (p->data == d)
			 {
				p->Freq++;  //Frequency will Increase
				return;
			 }
		  }
		  //New Element Entry Case
		  for (p = Header, q = Header->next; q != NULL; p = q, q = q->next)
			 ;
		  temp = GetNode(d, p, NULL);
		  p->next = temp;
		  size++;
	   }
    }

    int GetSize()
    {
	   return size;
    }

    void Traverse()	//Printing Function 
    {	  //Mostly used to check the working of the queue
	   node* p, * q, * temp;
	   for (p = Header, q = Header->next; q != NULL; p = q, q = q->next)
	   {
		  cout << "character = " << p->data << " , frequency = " << p->Freq << endl;
	   }
    }

    //This Function Sorts the linked Queue in the desired 
    //order comparing the frequencies of the characters
    void sort()
    {
	   node* p = Header;
	   node* q = NULL;

	   if (p == NULL)  //In case of Empty Queue
		  return;
	   else {		    //Bubble Sort
		  while (p != NULL) {
			 q = p->next;
			 while (q != NULL) {
				if (p->Freq > q->Freq)	   //Comparing Statement
				    swap(p, q);	//Swap Function
				q = q->next;	 //Inner Loop Increment
			 }
			 p = p->next;	  //Outer Loop Increment
		  }
	   }
    }
    //Swap function that the sorting function uses
    void swap(node* a, node* b) {
	   //The values are swapped, the pointers left as they were
	   char d;	//Temporary variable
	   int da;	//Temporary variable
	   d = a->data;
	   da = a->Freq;
	   a->data = b->data;
	   a->Freq = b->Freq;
	   b->data = d;
	   b->Freq = da;
    }
    //Function to POP and Delete the first Node from the Linked Queue
    void pop(char& d, int& f)
    {
	   if (this->isEmpty())
		  return;
	   this->size--;   //Decrement in the total size of the queue
	   node* p, * q, * temp;
	   int min = Header->Freq;
	   temp = Header;

	   d = Header->data;   //Saving the values
	   f = Header->Freq;   //Saving the values
	   p = Header;
	   Header = Header->next;

	   delete p;
    }
    //Function that reads the files and stores the characters in this queue
    void ReadFile(string filename)
    {
	   string str;
	   ifstream file(filename, ios::in);   //File Already Initialized

	   while (!file.eof())
	   {
		  file >> str;		  //Reading the text
		  for (int i = 0; i < str.length(); i++)
		  {
			 this->push(str[i]);	//Saving the Characters
		  }
		  this->push(' ');		 //Entering Spaces as the this function does not save spaces
	   }
    }
};
