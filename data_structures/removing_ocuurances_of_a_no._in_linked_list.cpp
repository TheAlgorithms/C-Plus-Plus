#include <bits/stdc++.h>
using namespace std;
class node
{
public:
    int data;
    node *ptr;
    node()
    {
    }
    node(int a)
    {
        data = a;
        ptr = NULL;
    }
};
node *head = NULL;
void insertion(int a)
{
    node *temp = new node(a), *temp1 = head;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        while (temp1->ptr != NULL)
        {
            temp1 = temp1->ptr;
        }
        temp1->ptr = temp;
    }
}
int deletion(int k)
{
    node *temp = head, *temp1;
    int c = 0;
    while (temp!= NULL)
    {
        if (temp->data == k)
        {
            c++;
            if (c > 1)
            {
                temp1->ptr = temp->ptr;
                delete (temp);
                temp = temp1->ptr;
            }
            else
            {
                temp1=temp;
                temp=temp->ptr;
            }
        }
        else
        {
            temp1=temp;
            temp=temp->ptr;
        }
    }
    return c;
}
void display()
{
    node *temp = head;
    if (head == NULL)
    {
        cout << "List is empty" << endl;
    }
    else
    {
        while (temp->ptr != NULL)
        {
            cout << temp->data << endl;
            temp = temp->ptr;
        }
        cout << temp->data << endl;
    }
}
int main()
{
    int n, c = 0, k = 0;
    cout << "Enter the nos. and enter -1 when you are done" << endl;
    cin >> n;
    while (n != -1)
    {
        insertion(n);
        cin >> n;
    }
    node *temp = head;
    cout << "Enter occurance to be removed" << endl;
    cin >> n;
    if (head == NULL)
        cout << "List is empty" << endl;
    else
    {
        c=deletion(n);
        display();
        cout<<"Ocuurence is "<<c<<endl;
    }
    return 0;
}