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

int main()
{

    // trial run of function and class
    LinkedList list;
    list.InsertAtEnd(1);
    list.InsertAtEnd(2);
    list.InsertAtEnd(3);
    list.InsertAtEnd(4);
    list.Display();
    list.reverse();
    list.Display();

    LinkedList list1, list2;
    list1.InsertAtEnd(1);
    list1.InsertAtEnd(2);
    list2.InsertAtEnd(3);
    list2.InsertAtEnd(4);
    list1.Display();
    list2.Display();
    list1 = list1 + list2;
    list1.Display();

    list1.InsertAtEnd(5);
    LinkedList list4;
    list4 = list1.kgroup(3);
    list4.Display();
    list.Remove(1);
    list.Display();
    list.RemoveNth(3);
    list.Display();
    return 0;
}
