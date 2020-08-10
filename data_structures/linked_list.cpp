/**
 * @file linked_list.cpp
 * @brief Implementation of singly linked list algorithm.
 *
 * @details
 * The linked list is a form of container used for holding a sequence of 
 * values, which can be added, removed and displayed.
 * ### Algorithm
 * Values can be added by iterating to the end of a list(by following 
 * the pointers) starting from the first node. Whichever node points to null
 * is considered the last node and is pointed to the new value.
 *
 * Values can be removed by also iterating through the list. When the node containing 
 * the value is found, the node pointing to the current node is made to point to the 
 * node that the current node is pointing to, and then returning the current node to
 * heap store.
 */
#include <iostream>
#include <sstream>

/**
 * @namespace data_structures
 * @brief Data Structures algorithms
 */
namespace data_structures {
/**
 * Class Documentation
 */
struct node
{
    int val;
    node *next;
};
	
/**
 * This function checks if the string passed consists 
 * of only digits.
 *@param s To be checked if s contains only integers
 *@returns true if there are only only digits present in the string
 *@returns false if any other character is found
 */
bool isDigit(const std::string& s)
{
	//function statements here
	for(int i=0;i<s.size()-1;i++)
    {
    	if(!isdigit(s[i]))
    	{
            return false;
		}
	}
	return true;
}
	
/**
 * This function changes the value_type of its argument
 * from a string to an integer
 * @param s argument whose value_type we want to change
 * @return number value with value_type as integer
 */
int toInt(const std::string& s)
{
	//function statements here
	std::stringstream geek(s);
	int number=0;
	geek>>number;
	return number;
} 

node *start=nullptr;

/**
 * This function creates a new node using the new value
 * passed as its argument and inserts it to the end of the 
 * list.
 *@param x value we want to insert to the list
 */
void insert(int x) {
	//function statements here
    node* t = start;
    node* n = new node;//creates new node
    n->val = x;//sets value(val) as x
    n->next = nullptr;
    if (t != nullptr) {
        while (t->next != nullptr) {
            t = t->next;
        }//iterate to the end of the list
        t->next = n;//current last node on the list is made
	    //to point to the new node
    } else {
        start = n;
    }
}

/**
 * This function removes an existing node from the current
 * list containing the value passed as an argument to the 
 * function.
 * @param x value we want to remove from the list
 */
void remove(int x) {
	//function statements here
    if (start == nullptr) {
        std::cout << "\nLinked List is empty\n";
        return;//return if the list is empty 
    } else if (start->val == x) {//check if the first node contains
	    			//the value passed as an argument
        start = start->next;
        return;
    }

    node *temp = start, *parent = start;
	//create iterators to the first and the next node
	//and initialize both iterators with the first node
	
    //while the node pointed to by parent iterator 
    //points at another node and the temp iterator does not have the 
    //value x passed as the argument, move both iterators forward
    //by one node and repeat
    while (temp != nullptr && temp->val != x) {
        parent = temp;
        temp = temp->next;//initially, only the temp iterator is moved forward
    }
	
    //Tell user if value not found
    if (temp == nullptr) {
        std::cout << std::endl << x << " not found in list\n";
        return;
    }
    //else point the node pointed to by the parent iterator to the 
    //node after the temp iterator 
    parent->next = temp->next;

    delete temp;
}

/**
 * This function searches for the value passed as an argument
 * in the linked list.
 * @param x value to be searched for
 */
void search(int x) {
	//function statements here
    node *t = start;
    int found = 0;
    while (t != nullptr) {
        if (t->val == x) {
            std::cout << "\nFound";
            found = 1;
            break;
        }
        t = t->next;
    }
    if (found == 0) {
        std::cout << "\nNot Found";
    }
}
	
/**
 * This function displays all the values that are currently 
 * in the list in the order in which they were inputed by the 
 * user
 */
void show() {
	//function statements here
    node *t = start;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

/**
 * This function displays all the values that are currently 
 * in the list in a reverse order to which they were inputed by the 
 * user
 */
void reverse() {
	//function statements here
    node *first = start;
    if (first != nullptr) {
        node *second = first->next;
        while (second != nullptr) {
            node *tem = second->next;
            second->next = first;
            first = second;
            second = tem;
        }
        start->next = nullptr;
        start = first;
    } else {
        std::cout << "\nEmpty list";
    }
}
} // namespace data_structures

/**
 * Main function
 */
int main()
{
//code here
    int choice =0;
    int x = 0;
    std::string s;
    do {
        std::cout << "\n1. Insert";
        std::cout << "\n2. Delete";
        std::cout << "\n3. Search";
        std::cout << "\n4. Print";
        std::cout << "\n5. Reverse";
        std::cout << "\n0. Exit";
        std::cout << "\n\nEnter you choice : ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nEnter the element to be inserted : ";
            std::cin >> s;
            
            if(!data_structures::isDigit(s))
	    {
		    std::cout<<"Wrong Input!\n";
	    }
            else
            {
            	x=data_structures::toInt(s);
            	data_structures::insert(x);
			}
            break;
        case 2:
            std::cout << "\nEnter the element to be removed : ";
            std::cin >> s;
            if(!data_structures::isDigit(s))
	    {
		    std::cout<<"Wrong Input!\n";
	    }
            else
            {
            	x=data_structures::toInt(s);
            	data_structures::remove(x);
			}
            break;
        case 3:
            std::cout << "\nEnter the element to be searched : ";
            std::cin >> s;
            if(!data_structures::isDigit(s))
	    {
		    std::cout<<"Wrong Input!\n";
	    }
            else
            {
            	x=data_structures::toInt(s);
            	data_structures::search(x);
			}
            break;
        case 4:
            data_structures::show();
            std::cout << "\n";
            break;
        case 5:
            std::cout << "The reversed list: \n";
            data_structures::reverse();
            data_structures::show();
            std::cout << "\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
