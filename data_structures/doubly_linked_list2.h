/*

Documentation for DoubleLinkedList class
Overview
The DoubleLinkedList class is a template class that implements a double linked list data structure.
It supports the following operations:

Adding and removing elements to and from the list
Accessing elements in the list by index
Getting the head and tail elements of the list
Checking if the list is empty

Usage:
To use the DoubleLinkedList class, you first need to create an instance of it.
You can then add and remove elements to and from the list using the
addToTail(),
addToHead(),
addToIndex(),
and pop() methods.

You can access elements in the list by index using the getNth() method.
You can get the head and tail elements of the list using the getHead() and getTail() methods, respectively.
You can check if the list is empty using the isEmpty() method.


API Reference:

Class methods:
DoubleLinkedList(): Creates a new empty double linked list.
deleteList(): Deletes all elements from the list.
displayList(): Displays the contents of the list to the console.
isEmpty(): Returns true if the list is empty, false otherwise.

Member variables:
head: A pointer to the head node of the list.
tail: A pointer to the tail node of the list.

Member functions:
addToTail(): Adds a new element to the tail of the list.
addToHead(): Adds a new element to the head of the list.
addToIndex(): Adds a new element to the list at the specified index.
pop(): Removes the element at the specified index from the list.
getNth(): Returns the element at the specified index in the list.
getHead(): Returns the head element of the list.
getTail(): Returns the tail element of the list.


*/




#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST
#include <iostream>

template <typename type>
class DoubleLinkedList
{
private:
    struct Node
    {
        type data;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;

public:
    DoubleLinkedList()
    {
        head = NULL;
        tail = head;
    }

    void addToTail(type val)
    {
        Node *newNode = new Node;

        newNode->data = val;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void addToHead(type val)
    {
        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addToIndex(type val, int index)
    {
        if (index < 0)
        {
            std::cerr << "Invalid index." << std::endl;
            return;
        }

        Node *newNode = new Node;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (index == 0)
        {
            // Special case: Insert at the head.
            newNode->next = head;
            if (head)
            {
                head->prev = newNode;
            }
            head = newNode;
            return;
        }

        Node *temp = head;
        int count = 0;

        while (temp)
        {
            if (count == index - 1)
            {
                if (temp->next) // Ensure temp->next is not nullptr.
                {
                    newNode->next = temp->next;
                    newNode->prev = temp;
                    temp->next->prev = newNode;
                    temp->next = newNode;
                    return;
                }
                else
                {
                    std::cerr << "Index out of bounds." << std::endl;
                    delete newNode; // Clean up the new node if index is out of bounds.
                    return;
                }
            }
            temp = temp->next;
            count++;
        }

        if (!temp && count != index)
        {
            std::cerr << "Index out of bounds." << std::endl;
            delete newNode; // Clean up the new node if index is out of bounds.
        }
    }

    int count()
    {
        int count = 0;
        Node *nodePtr = head;

        while (nodePtr)
        {
            count++;
            nodePtr = nodePtr->next;
        }

        return count;
    }

    type getNth(int index)
    {
        if (index < 0)
        {
            std::cerr << "Invalid index" << std::endl;
            return type();
        }

        Node *nodePtr = head;
        int count = 0;

        while (nodePtr)
        {
            if (count == index)
            {
                if (nodePtr)
                {
                    return nodePtr->data;
                }
                else
                {
                    std::cerr << "Index out of Bounds" << std::endl;
                    return type();
                }
            }
            count++;

            if (nodePtr)
            {
                nodePtr = nodePtr->next;
            }
        }
    }

    type getTail()
    {
        if (tail)
        {
            return tail->data;
        }
        else
        {
            std::cerr << "Tail does not exist" << std::endl;
            return type();
        }
    }

    type pop(int index)
    {
        if (index < 0)
        {
            std::cerr << "Invalid index" << std::endl;
        }
        if (head)
        {
            if (index == 0)
            {
                type val;
                head->data = val;
                Node *temp = head;
                head = head->next;
                if (head)
                {
                    head->prev = nullptr;
                }
                else
                {
                    tail = NULL;
                }
                delete temp;

                return val;
            }

            Node *nodePtr = head;
            int count = 0;

            while (nodePtr)
            {
                if (count == index)
                {
                    if (!nodePtr)
                    {
                        std::cerr << "Index out of bounds" << std::endl;
                    }

                    type val = nodePtr->data;

                    nodePtr->prev->next = nodePtr->next;
                    if (nodePtr->next)
                    {
                        nodePtr->next->prev = nodePtr->prev;
                    }
                    else
                    {
                        tail = nodePtr->prev;
                    }

                    delete nodePtr;

                    return val;
                }
                nodePtr = nodePtr->next;
                count++;
            }

            std::cerr << "Index out of Bounds" << std::endl;
        }
        else
        {
            std::cerr << "List is empty cannot delete" << std::endl;
        }
    }

    void deleteList()
    {
        if (!head)
        {
            std::cerr << "There are no elements in list to delete!" << std::endl;
        }

        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void displayList()
    {
        Node *temp = head;
        if (head == NULL)
        {
            std::cout << "List is empty" << std::endl;
            return;
        }
        while (temp != NULL)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }

    bool isEmpty()
    {
        if (head)
        {
            return false;
        }

        return true;
    }

    ~DoubleLinkedList()
    {
        deleteList();
    }
};

#endif
