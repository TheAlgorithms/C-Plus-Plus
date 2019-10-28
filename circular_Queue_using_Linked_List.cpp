#include <iostream> 
using namespace std;

// Defining Node type and contents
struct node
{
    int data;
    struct node *next; //link to next node
};
// Defining a Class queue with front and rear elements
class Queue
{
    node *front;
    node *rear;

public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
    
	void createNode(int val) // Creating a new node for inserting in array
    {
        node *nn;
        nn = new node;
        nn -> data = val;
        nn -> next = NULL;
        front = nn;
        rear = nn;
    }
    void inqueue(int val) // Insert value at rear
    {
        if ( !front )
        {
            createNode( val );
        }
        else
        {
            node *nn; 
            nn = new node;
            nn->data = val;
            rear->next = nn;
            nn->next = front;
            rear = nn;
        }
    }
    
	// Deletion of a node from the front 
	void delqueue()
    {
        node * del;
        del = front;
		cout << "Deleted value is  " << del -> data
		front = front -> next; // Pushing front to the val next to front
        delete ( del );
    }
    // Traversing through the Circular Queue
	void traverse()
    {
        node * ptr;
        ptr = front;
        do
        {									
            cout << ptr -> data << " ";
            ptr = ptr -> next;
        } while ( ptr != rear -> next );	// Display values till rear from front
        cout << front -> data;
        cout << endl ;
    }
};
int main(void)
{
    Queue q;
    q.inqueue(10);
    q.inqueue(20);
    q.inqueue(30);
    q.inqueue(40);
    q.inqueue(50);
    q.inqueue(60);
    q.inqueue(70);
    q.traverse();
    q.delqueue();
    q.traverse();
    return 0;
}