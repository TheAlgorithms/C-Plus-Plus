/*
 * Simple data structure CLL (Cicular Linear Linked List)
 * */
#include <cstring>
#include <cctype>
#include <iostream>
#include <cstdlib>

#ifndef CLL_H
#define CLL_H
/*The data structure is a linear linked list of integers */
struct node
{
	int  data;
    node * next;
};

class cll
{
    public:
        cll();                       /* Construct without parameter */
        ~cll();
        void display();              /* Show the list */

        /******************************************************
	    * Useful method for list
        *******************************************************/
        void insert_front(int new_data);  /* Insert a new value at head  */
		void insert_tail(int new_data);   /* Insert a new value at tail */
		int get_size();              /* Get total element in list */
        bool find_item(int item_to_find); /* Find an item in list */

	    /******************************************************
	     * Overloading method for list
         *******************************************************/
	     int operator*();           /* Returns the info contained in head */
	     /* Overload the pre-increment operator.
	        The iterator is advanced to the next node. */
	     void operator++();

    protected:
        node * head;
		int total;      /* Total element in a list */
};
#endif
