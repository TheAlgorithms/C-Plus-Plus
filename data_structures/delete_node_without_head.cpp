/**
 * \file
 * \brief [Delete a Node Without Head Pointer
 * in Linked List](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list)
 * @author [Anshu Saini](https://github.com/anshu189)
 */

#include <iostream>
using namespace std;

// Initializing a Linked List using Class Node
class Node{
public:
    int data;
    Node *next;
    // Constructor for Linked List for a deafult value
    Node(int data){
        this -> data=data;
        this -> next=NULL;
    }
};

// Print Linked List Function
void printList(Node* &head){
    Node* temphead = head;
    while(temphead != NULL){
        cout << temphead -> data << " ";
        temphead = temphead -> next;
    }
    cout<<endl;
}

// Appending elements in the Linked List 
void insertattail(Node* &tail, int data){
    Node *hue = new Node(data);
    tail->next=hue;
    tail=hue;
}

// Deleting a single Node without head Pointer in Linked List
// Time Complexity: O(1)
// Auxilliary Space: O(1)
void delwohead(Node* del){
    del->data=del->next->data;
    del->next=del->next->next;
}

static void test( Node* head,Node* tail) {
    Node* tempnode=head; // Declare an unchanged head pointer
    Node* nodetobedeleted=head; // Declaring a Node to store the node which is to be deleted
    // Append elements using for loop in Linked List
    for(int i=0;i<5;++i){
        insertattail(tail,i);
    }

    // Our Linked List right now => 1 0 1 2 3 4
    cout<<"<= Original Linked List =>"<<endl;
    printList(head);

    // Deleting the second(2nd) element from the linked list
    for(int i=0;i<2;++i){
        nodetobedeleted=tempnode;
        tempnode=tempnode->next;
    }
    delwohead(nodetobedeleted); // Funtion to delete a particular Node
    cout<<endl<<"<= New Linked List after deleting second element =>"<<endl;
    
    printList(head); // Prints out the new Linke List after deletion
    cout<<"Test case have been successfully passed!"<<endl<<endl;
}

// Driver Function
int main(){
    Node* mainode=new Node(1);
    Node* head=mainode;
    Node* tail=mainode;
    Node* delnode=mainode;
    
    // Run Self Test Case
    test(head,tail);
    
    // User Driven Code
    int n,ele,ndeleted;
    cout<<"Enter the size of Linked List: ";
    cin>>n; //Input the size of Linked List

    cout<<"Enter the elements to be inserted in Linked List: ";
    // Input the elements for Linked List
    for(int i=0;i<n;++i){
        cin>>ele;
        insertattail(tail,ele);
    }
    mainode=mainode->next;
    head=mainode;
    cout<<"<= Original Linked List =>"<<endl;
    printList(mainode);

    cout<<"Enter the node position to be deleted: ";
    cin>>ndeleted; // Input the node position to be deleted 
    for(int i=0;i<ndeleted;++i){
        delnode=head;
        head=head->next;       
    }
    // Node to be deleted stored in delnode
    delwohead(delnode);
    printList(mainode);
    return 0;
}
