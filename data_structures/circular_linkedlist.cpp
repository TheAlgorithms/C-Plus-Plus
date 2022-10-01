#include <iostream>
using namespace std;

class Node
{
    public:
    int data;
    Node* next;

    // constructor
    Node(int data)
    {
        this -> data = data;
        this -> next = NULL;
    }

    ~Node()
    {
        int value = this -> data;
        while(this -> next != NULL)
        {
            delete next;
            next = NULL;
        }
        cout << "Memory is free to use now " << value << endl;
    }

};

void insertNode(Node* &tail,int element, int data)
{
    // assuming that the element is present in the list
    if(tail == NULL)
    {
        Node* newNode = new Node(data);
        tail = newNode;
        newNode -> next = newNode;
    }
    else
    {
        // non empty list
        // assuming that the element is present in the list

        Node* current = tail;
        while(current -> data != element)
        {
            current = current -> next;
        }
        Node* temp = new Node(data);
        // 2---->3
        // 2 ---->4 ---->3
        // 2 is current 4 is temp
        // 2 was linked to 3 before 4 so current -> next address = temp -> next (address)
        // and then make the list circular 
        // current -> next (address) = temp
        temp -> next = current -> next;
        current -> next = temp;
        
    }
    
}

// printing
    void print(Node* tail)
    {
        Node* temp = tail;
        if(tail == NULL)
        {
            cout << "List is empty " << endl;
        }
        do
        {
            cout << tail -> data << " ";
            tail = tail -> next;
        } while (tail  != temp);
        cout << endl;
           
    }

    void deletetion(Node* &tail,int value)
    {
        // case for list is empty
        if(tail == NULL)
        {
            cout << "List is empty! Try something else " << endl; 
        }
        // assuming list in not empty
        else
        {
            Node* previous = tail;
            //  current is the element infront of the previous element this is why we have written current = previous -> next (address)
            Node* current = previous -> next;
            while(current -> data != value)
            {
                previous = current;
                // previous holds the value of current before it's changed to next location
                current = current -> next;
                // at the end of this loop current will store the value of the element which you want to delete
            }
            // assuming that we have found the element
            previous -> next = current -> next;
            
            // 1 Node Linked List
            if(tail == current)
            {
                tail = previous;
            }
            
            if(tail == current)
            {
                tail = previous;
            }
            current -> next = NULL;
            delete current;
        }
    }

int main()
{
    Node* tail = NULL;
    // empty list case
    insertNode(tail,5,3);
    print(tail);

    insertNode(tail,3,5);
    print(tail);

    insertNode(tail,5,7);
    print(tail);

    insertNode(tail,7,9);
    print(tail);

    insertNode(tail,5,6);
    print(tail);

    insertNode(tail,9,10);
    print(tail);

    insertNode(tail,3,4);
    print(tail);

    deletetion(tail,3);
    print(tail);
    return 0;
    
}
