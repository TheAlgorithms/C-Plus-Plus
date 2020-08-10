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
struct node
{
    int val;
    node *next;
};//node containing value and pointer to next node

bool isDigit(const std::string& s)
{
	for(int i=0;i<s.size()-1;i++)
    {
    	if(!isdigit(s[i]))
    	{
            return false;
		}
	}
	return true;
}//returns true if argument contains only integers, false otherwise

int toInt(const std::string& s)
{
	std::stringstream geek(s);
	int number=0;
	geek>>number;
	return number;
}//converts argumnet from type string to type int 

node *start=nullptr;

void insert(int x) {
    node* t = start;
    node* n = new node;
    n->val = x;
    n->next = nullptr;
    if (t != nullptr) {
        while (t->next != nullptr) {
            t = t->next;
        }
        t->next = n;
    } else {
        start = n;
    }
}//inserts new node to the list with the argument as the value

void remove(int x) {
    if (start == nullptr) {
        std::cout << "\nLinked List is empty\n";
        return;
    } else if (start->val == x) {
        start = start->next;
        return;
    }

    node *temp = start, *parent = start;

    while (temp != nullptr && temp->val != x) {
        parent = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cout << std::endl << x << " not found in list\n";
        return;
    }

    parent->next = temp->next;
}//removes node containing argument as value

void search(int x) {
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
}//search for node containing the argument

void show() {
    node *t = start;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}//display all the values in the list

void reverse() {
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
}//reverse the order of the nodes in the list
} // namespace data_structures

/**
 * Main function
 */
int main()
{
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
