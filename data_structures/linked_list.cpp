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
};

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
}

int toInt(const std::string& s)
{
	std::stringstream geek(s);
	int number=0;
	geek>>number;
	return number;
}

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
}

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
}

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
}

void show() {
    node *t = start;
    while (t != nullptr) {
        std::cout << t->val << "\t";
        t = t->next;
    }
}

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
}
} // namespace data_structures

/**
*Main Function
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
            	insert(x);
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
