#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node<T> *next;
};

template <class T>
class LinkedList
{
public:
    Node<T> *head;
    LinkedList()
    {
        head = NULL;
    }
    void insertionHead()
    {
        Node<T> *temp = new Node<T>;
        cout << "\nenter the value to be inserted " << endl;
        T n;
        cin >> n;
        temp->data = n;
        if (head == NULL)
        {
            head = temp;
            head->next = head;
        }
        else
        {
            Node<T> *loop = head;
            while (loop->next != head)
                loop = loop->next;
            temp->next = head;
            head = temp;
            loop->next = head;
        }
    }
    void insertionTail()
    {
        Node<T> *temp = new Node<T>;
        cout << "\nenter the value to be inserted " << endl;
        T n;
        cin >> n;
        temp->data = n;
        if (head == NULL)
        {
            head = temp;
            head->next = head;
        }
        else
        {
            Node<T> *p = head;
            while (p->next != head)
                p = p->next;
            temp->next = head;
            p->next = temp;
        }
    }
    void deletionHead()
    {
        if (head != NULL)
        {
            if (head->next == head)
            {
                Node<T> *delnode = head;
                cout << "element deleted " << head->data;
                head = NULL;
                delete delnode;
            }
            else
            {
                Node<T> *delnode = head;
                cout << "element deleted " << head->data;
                Node<T> *loop = head;
                while (loop->next != head)
                    loop = loop->next;
                head = head->next;
                loop->next = head;
                delnode->next = NULL;
                delete delnode;
            }
        }
        else
        {
            cout << "List empty";
        }
    }
    void deletionTail()
    {
        if (head != NULL)
        {
            if (head->next == head)
            {
                Node<T> *delnode = head;
                cout << "element deleted " << head->data;
                head = NULL;
                delete delnode;
            }
            else
            {
                Node<T> *temp = head;
                while (temp->next->next != head)
                    temp = temp->next;
                cout << "element deleted " << temp->next->data;
                Node<T> *delnode = temp->next;
                delete delnode;
                temp->next = head;
            }
        }
        else
        {
            cout << "List empty";
        }
    }
    void search()
    {
        if (head == NULL)
            cout << "\nList empty";
        else
        {
            cout << "\nenter the value to be searched " << endl;
            T x;
            cin >> x;
            Node<T> *temp = head;
            bool found = false;
            do
            {
                if (temp->data == x)
                    found = true;
                temp = temp->next;
            } while (temp != head);

            if (found)
                cout << "\nElement found in linked list";
            else
                cout << "\nElement not found in linked list";
        }
    }
    void reverse()
    {
        if (head == NULL)
        {
            cout << "\nList is empty.";
            return;
        }
        else if (head->next == head)
        {
            cout << "\nList only has one element";
            return;
        }

        Node<T> *prev = NULL;
        Node<T> *temp = head;
        Node<T> *next;
        do
        {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        } while (temp != head);
        head->next = prev;
        head = prev;
        cout << "\nThe list has been reversed";
    }
    void display()
    {
        Node<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            if (temp->next == head)
                break;
            temp = temp->next;
        }
        cout << "!!!";
    }
    void alt_display()
    {
        Node<T> *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << "->";
            if (temp->next == head || temp->next->next == head)
                break;
            temp = temp->next->next;
        }
        cout << "!!!";
    }
};

int main()
{
    LinkedList<int> l;
    int ch;
    char cont;
    do
    {
        cout << "\nEnter your choice among following " << endl;
        cout << "1.Insert an element at beginning" << endl;
        cout << "2.Insert an element at end" << endl;
        cout << "3.Delete an element from beginning" << endl;
        cout << "4.Delete an element from end" << endl;
        cout << "5.Search the list" << endl;
        cout << "6.Reverse the list" << endl;
        cout << "7.Display alternate elements of Linked List" << endl;
        cout << "8.Display Linked List\n"
             << endl;
        cin >> ch;
        switch (ch)
        {
            int val;
        case 1:
            l.insertionHead();
            break;
        case 2:
            l.insertionTail();
            break;
        case 3:
            l.deletionHead();
            break;
        case 4:
            l.deletionTail();
            break;
        case 5:
            l.search();
            break;
        case 6:
            l.reverse();
            break;
        case 7:
            l.alt_display();
            break;
        case 8:
            l.display();
            break;
        default:
            cout << "\nInvalid choice " << endl;
        }
        cout << "\n\nContinue?(y/n)" << endl;
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');
    return 0;
}