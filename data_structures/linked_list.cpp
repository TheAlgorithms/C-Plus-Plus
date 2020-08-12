/**
 * @file linked_list.cpp
 * @brief Implementation of singly linked list algorithm.
 *
 * @details
 * The linked list is a form of container used for holding a sequence of
 * values, which can be added, removed and displayed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list(by following
 * the pointers) starting from the first link. Whichever link points to null
 * is considered the last link and is pointed to the new value.
 *
 * Values can be removed by also iterating through the list. When the node
 * containing the value is found, the node pointing to the current node is made
 * to point to the node that the current node is pointing to, and then returning
 * the current node to heap store.
 */
#include <iostream>
#include <sstream>

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures{

/**
 * This function changes the value_type of its argument
 * from a string to an integer
 * @param s argument whose value_type we want to change
 * @return number value with value_type as integer
 */
int toInt(const std::string &s) {
  // function statements here
  std::stringstream geek(s);
  int number = 0;
  geek >> number;
  return number;
}

/**
 * This function checks if the string passed consists
 * of only digits.
 * @param s To be checked if s contains only integers
 * @returns true if there are only only digits present in the string
 * @returns false if any other character is found
 */
bool isDigit(const std::string &s) {
  // function statements here
  for (int i=0;i<s.size();i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

/**
 * A link class containing a value and pointer to another link
 */
class link
{
	public:
		link(int v=0, link* succ=0)
		:val(v),succ(0)
		{}
		int val;
		link* succ;
};

/**
 * A list class containing a sequence of links
 */
class list
{
	public:
		list()
		:first(new link),last(first)
		{}
		
		bool isEmpty();
		
		void push_back(int new_elem);
		void push_front(int new_elem);
		void erase(int old_elem);
		void display();
		void search(int find_elem);
		void reverse();
		
	private:
		link* first;//link before the actual first element
		link* last;
};

/**
 * function checks if list is empty
 * @returns true if list is empty
 * @returns false if list is not empty
 */
bool list::isEmpty()
{
	if(first==last)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * function adds new element to the end of the list
 * @param element to be added to the list
 */
void list::push_back(int new_elem)
{
	link* new_link = new link(new_elem);
	last->succ = new_link;
	last = last->succ;
}

/**
 * function adds new element to the beginning of the list
 * @param element to be added to the list
 */
void list::push_front(int new_elem)
{
	link* new_link = new link(new_elem);
	new_link->succ = first->succ;
	first->succ = new_link;
}

/**
 * function erases old element from the list
 * @param element to be erased from the list
 */
void list::erase(int old_elem)
{
	if(isEmpty())
	{
		std::cout<<"List is Empty!";
		return;
	}
	link* t = first;
	while(t!=last && t->succ->val!=old_elem)
	{
		t=t->succ;
	}
	if(t==last)
	{
		std::cout<<"Element not found\n";
		return;
	}
	t->succ=t->succ->succ;
	if(t->succ == 0)last=t;
}

/**
 * function displays all the elements in the list
 */
void list::display()
{
	if(isEmpty())
	{
		std::cout<<"List is Empty!";
		return;
	}
	link* t = first;
	while(t->succ!=0)
	{
		std::cout<<t->succ->val<<"\t";
		t=t->succ;
	}
}

/**
 * function searchs for @param find_elem in the list
 */
void list::search(int find_elem)
{
	if(isEmpty())
	{
		std::cout<<"List is Empty!";
		return;
	}
	link* t = first;
	while(t!=last && t->succ->val!=find_elem)
	{
		t=t->succ;
	}
	if(t==last)
	{
		std::cout<<"Element not found\n";
		return;
	}
	std::cout<<"Element was found\n";
}
}// namespace data_structures

/**
 * Main function
 */
int main()
{
	data_structures::list l;
	int choice = 0;
  	int x = 0;
  	std::string s;
  	do
  	{
    	std::cout << "\n1. Insert";
    	std::cout << "\n2. Delete";
    	std::cout << "\n3. Search";
    	std::cout << "\n4. Print";
    	std::cout << "\n0. Exit";
    	std::cout << "\n\nEnter you choice : ";
    	std::cin >> choice;
    	switch (choice) 
		{
    		case 1:
      			std::cout << "\nEnter the element to be inserted : ";
      			std::cin >> s;

      			if (data_structures::isDigit(s)) 
				{
        			x = data_structures::toInt(s);
       		 		l.push_back(x);
      			} 
				else 
				{
        			std::cout << "Wrong Input!\n";
      			}
      			break;
    		case 2:
     			std::cout << "\nEnter the element to be removed : ";
      			std::cin >> s;
      			if (data_structures::isDigit(s)) 
				{
       		 		x = data_structures::toInt(s);
        			l.erase(x);
      			} 
				else 
				{
        			std::cout << "Wrong Input!\n";
     		 	}
      			break;
    		case 3:
      			std::cout << "\nEnter the element to be searched : ";
      			std::cin >> s;
      			if (data_structures::isDigit(s)) 
				{
        			x = data_structures::toInt(s);
        			l.search(x);
      			} 
				else 
				{
        			std::cout << "Wrong Input!\n";
      			}
      			break;
      		case 4:
      			l.display();
      			std::cout<<"\n";
      			break;
      		default:
    			std::cout<<"Invalid Input\n"<<std::endl;
    			break;
		}
	} while(choice != 0);
	return 0;
}

