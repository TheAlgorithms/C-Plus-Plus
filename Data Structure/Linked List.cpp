#include <iostream>
#include <string>

class Node
{
public:
    int val;
    Node* next;

    Node(int val)
    {
        this->val = val;
    }
};

class LinkedList
{
public:
    Node* root;
    int size;

    LinkedList(int val)
    {
        root = new Node{ val };
    }

    void insert(int val)
    {
        if(root == nullptr)
        {
            root = new Node{ val };
            return;
        }

        Node* temp = root;

        while(temp->next != nullptr)
            temp = temp->next;

        temp->next = new Node{ val };
    }

    void remove(int val)
    {
        Node* temp = root;
        Node* prev;

        if(temp != nullptr && temp->val == val)
        {
            root = temp->next;
            return;
        }

        while(temp != nullptr && temp->val != val)
        {
            prev = temp;
            temp = temp->next;
        }

        if(temp == nullptr)
            return;

        prev->next = temp->next;
    }

    Node* search(int val)
    {
        if(root->val == val)
            return root;

        Node* temp = root;
        while(temp->next != nullptr)
        {
            if(temp->val == val)
                return temp;
            temp = temp->next;
        }
    }

    void print()
    {
        Node* temp = root;
        while(temp != nullptr)
        {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
    }
};

void print_menu()
{
    std::cout << "\n1. Insert";
    std::cout << "\n2. Delete" ;
    std::cout << "\n3. Search";
    std::cout << "\n4. Print" ;
    std::cout << "\n0. Exit" ;
    std::cout << "\n\nEnter you choice : " ;
}

int main()
{

    int init;
    std::cout << "Initial value: ";
    std::cin >> init;
    LinkedList ll{ init };


	int choice, target;
	do
	{
        print_menu();
        std::cin >> choice;
		switch (choice)
		{
		case 1:
            std::cout << "\nEnter the element to be inserted : ";
			std::cin >> target;
            ll.insert(target);
			break;
		case 2:
            std::cout << "\nEnter the element to be removed : ";
			std::cin >> target;
            ll.remove(target);
			break;
		case 3:
            std::cout << "\nEnter the element to be searched : ";
			std::cin >> target;
			break;
		case 4:
            ll.print();
            std::cout << "\n";
			break;
		}
	} while (choice != 0);

	return 0;
}
