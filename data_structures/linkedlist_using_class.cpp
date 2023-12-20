#include <iostream>

struct Node
{
    int data;
    Node *next = nullptr;
};

class LinkedList
{
public:
    Node *head = nullptr;
    Node *tail = nullptr;

    int InsertAtEnd(int value)
    {
        Node *newnode = new Node();
        newnode->data = value;
        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
        return value;
    }

    void Display()
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }

        std::cout << "\n";
    }

    int InsertAtBeginning(int value)
    {
        Node *newnode = new Node();
        newnode->data = value;

        if (head == nullptr)
        {
            head = newnode;
            tail = newnode;
        }

        else
        {
            newnode->next = head;
            head = newnode;
        }
        return value;
    }
    void reverse()
    {
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;
        while (current != nullptr)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }
    LinkedList operator+(LinkedList temp)
    {
        LinkedList rval;
        Node *current = this->head;
        while (current != nullptr)
        {
            rval.InsertAtEnd(current->data);
            current = current->next;
        }

        Node *current1 = temp.head;
        while (current1 != nullptr)
        {
            rval.InsertAtEnd(current1->data);
            current1 = current1->next;
        }
        return rval;
    }
    LinkedList kgroup(int k)
    {
        LinkedList rval;
        LinkedList temp;
        Node *current = head;

        int count = 0;
        while (current != nullptr)
        {
            temp.InsertAtEnd(current->data);
            current = current->next;

            count++;

            if (count == k)
            {
                temp.reverse();
                rval = rval + temp;
                temp.head = nullptr;
            }
        }
        rval = rval + temp;
        return rval;
    }

    int Remove(int value)
    {
        Node *current = head;
        Node *temp = current;
        while (current != nullptr)
        {

            if (current->data == value)
            {

                if (current == head)
                {
                    head = current->next;
                    delete current;
                    return value;
                }
                else
                {

                    temp->next = current->next;
                    delete current;
                    return value;
                }
            }
            temp = current;

            current = current->next;
        }
        return -1;
    }

    int RemoveNth(int index)
    {
        Node *current = head;
        Node *temp = current;

        int counter = 0;

        while (current != nullptr)
        {

            if (counter == index)
            {
                if(current==head)
                {
                    head = current->next;
                    int returnvalue= current->data;
                    delete current;
                    return returnvalue;
                }

                else{
                    temp->next=current->next;
                    int returnvalue = current->data;
                    delete current;
                    return returnvalue;
                }
            }
            counter++;
            temp = current;
            current = current->next;
        }
        return -1;

    }
};

void testcase()
{
    LinkedList myList;

    // Insert elements
    myList.InsertAtEnd(1);
    myList.InsertAtEnd(2);
    myList.InsertAtEnd(3);

    // Display original list
    std::cout << "Original List: ";
    myList.Display();

    // Reverse the list
    myList.reverse();
    std::cout << "Reversed List: ";
    myList.Display();

    // Concatenate two lists
    LinkedList list1, list2;
    list1.InsertAtEnd(4);
    list1.InsertAtEnd(5);
    list2.InsertAtEnd(6);
    list2.InsertAtEnd(7);

    LinkedList concatenatedList = list1 + list2;
    std::cout << "Concatenated List: ";
    concatenatedList.Display();

    // Perform k-group reversal
    std::cout << "K-Group Reversal (k=2): ";
    LinkedList kGroupedList = concatenatedList.kgroup(2);
    kGroupedList.Display();

    // Remove elements
    myList.Remove(2);
    std::cout << "After Removing 2: ";
    myList.Display();

    myList.RemoveNth(1);
    std::cout << "After Removing Node at Index 1: ";
    myList.Display();
}


int main()
{
    testcase();
    return 0;
}
