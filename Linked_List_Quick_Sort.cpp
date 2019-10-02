#include<bits/stdc++.h>
using namespace std;

// node class for singly linked list
class Node
{
public:
    int data;
    Node *next;
    Node(int data)
    {
        this->data = data;
        next = NULL;
    }
};

// class for maintaining linked list
class LinkedList
{
public:
    int size;
    Node *head, *tail;
    
    LinkedList()
    {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    // add a node at the last of a linked list
    void addNode(int data)
    {
        Node *temp = new Node(data);
        if(head == NULL) // if size of list is 0
        {
            head = temp;
            tail = temp;
        }
        else // size of list in not zero
        {
            tail->next = temp;
            tail = temp;
        }
        size++;
    }

    // print the whole linked list
    void print()
    {
        Node *temp = head;
        while(temp!=NULL)
        {
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }

private:
    // returns previous node of the node 'n'
    Node* prevNode(Node* start,Node* n)
    {
        // if node 'n' is the start of the linked list
        if(start==n) 
            return NULL;
        Node* temp = start;
        while(temp->next!=n)
        {
            temp = temp->next;
        }
        return temp;
    }

    // swap data of two nodes 'node1' and 'node2'
    void swapNodeData(Node* node1,Node* node2)
    {
        int temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    /* create the partition of the list
       all the number less than pivot is on left side of pivot
       all the number greater than pivot is on the right side of pivot
       exapmle : input  : 1,5,4,6,2,3
                 output : 1,2,3,6,5,4 */
    Node* divideList(Node* start,Node* end)
    {
        int pivot = end->data; // pivot is always end node of the linked list
        Node* i = NULL; // index of smaller element
        Node* j =start; 
        while(j!=end)
        {
            if(j->data <= pivot) // if current element is less than or equal to pivot
            {
                // increment index of smaller element
                if(i==NULL)
                    i = start;
                else
                    i = i->next;
                swapNodeData(i,j); // swap current and smaller element
            }
            j = j->next;   
        }
        // increment index of smaller element
        if(i==NULL)
            i = start;
        else
            i = i->next;
        swapNodeData(i,j); // place pivot at its correct position
        return i;
    }

    void quickSortRec(Node* start,Node* end)
    {
        if(start==end || start==NULL || end==NULL || start==end->next)
            return;
        Node* pivot = divideList(start,end); // create partition of unsorted list
        quickSortRec(start,prevNode(start,pivot)); // sort list left of pivot
        quickSortRec(pivot->next,end); // sort list right of pivot
        return;
    }

public:
    void quickSort()
    {
        quickSortRec(head,tail);
        return;
    }
};

int main()
{
    LinkedList ll;
    ll.addNode(5);
    ll.addNode(2);
    ll.addNode(1);
    ll.addNode(8);
    ll.addNode(3);
    ll.addNode(6);
    ll.addNode(-1);
    ll.print();
    ll.quickSort();
    ll.print();
    return 0;
}

/*
this code is contributed by Raghav
https://github.com/raghav-dalmia
*/

/*
sample input : 5 2 1 8 3 6 -1
ouput : -1 1 2 3 5 6 8
*/
