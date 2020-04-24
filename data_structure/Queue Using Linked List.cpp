#include <iostream>
using namespace std;

struct node
{
    int val;
    node *next;
};

node *front, *rear;

void Enque(int x)
{
    if (rear == NULL)
    {
        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear = n;
        front = n;
    }

    else
    {

        node *n = new node;
        n->val = x;
        n->next = NULL;
        rear->next = n;
        rear = n;
    }
}

void Deque()
{
    if (rear == NULL && front == NULL)
    {
        cout << "\nUnderflow";
    }
    else
    {
        node *t = front;
        cout << "\n"
             << t->val << " deleted";
        front = front->next;
        delete t;
        if (front == NULL)
            rear = NULL;
    }
}

void show()
{
    node *t = front;
    while (t != NULL)
    {
        cout << t->val << "\t";
        t = t->next;
    }
}

int main()
{
    int ch, x;
    do
    {
        cout << "\n1. Enque";
        cout << "\n2. Deque";
        cout << "\n3. Print";
        cout << "\nEnter Your Choice : ";
        cin >> ch;
        if (ch == 1)
        {
            cout << "\nInsert : ";
            cin >> x;
            Enque(x);
        }
        else if (ch == 2)
        {
            Deque();
        }
        else if (ch == 3)
        {
            show();
        }
    } while (ch != 0);

    return 0;
}
