///Floyd Cycle Finding Algorithm

#include<iostream>
using namespace std;

class Node
{
    int data;
    Node* next;
};
Node *head = NULL;

void insert(int value)
{
    // Create a new node and inserts it in beginning of the list
    Node* temp = new Node;
    temp->data = value;
    temp->next = head;
    head = temp;
}

bool CheckforCycle()
{
    Node* slow = head, *fast = head;     //Initialised two pointers
    while(slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast)            //if at any instance, the slow and fast pointer point to the same node, it means a loop is present
            return true;
    }
    return false;
}

int main()
{
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    insert(6);
    head->next->next->next->next = head->next; //Cycle made for testing
    if(CheckforCycle())
        cout<<"Cycle found"<<endl;
    else
        cout<<"No cycle found"<<endl;
    return 0;

}
