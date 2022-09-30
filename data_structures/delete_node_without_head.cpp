#include <bits/stdc++.h>
using namespace std;

// Initializing a Linked List
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

// Driver Function
int main(){
    Node* mainode=new Node(1);
    Node* head=mainode;
    Node* tail=mainode;
    Node* nodetobedeleted=mainode;

    insertattail(tail,3);
    insertattail(tail,4);
    insertattail(tail,7);
    insertattail(tail,9);
    
    // Our Linked List right now => 1 3 4 7 9
    cout<<"<= Original Linked List =>"<<endl;
    printList(head);

    // Let assume we want to delete the 2nd element from the Linked List
    for(int i=0;i<2;++i){
        nodetobedeleted=head;
        head=head->next;
    }
    // This will delete the second element from the Linked List i.e. 3
    delwohead(nodetobedeleted);
    cout<<endl<<"<= New Linked List after deleting second element =>"<<endl;
    printList(mainode);
    return 0;
}