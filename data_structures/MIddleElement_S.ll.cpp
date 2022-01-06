/**
 * @file MiddleEle_SingLL.cpp
 * @brief Implementation of [Finding middle element in 
 * a single linked list](https://simple.wikipedia.org/wiki/Linked_list)
 * @details
 * The linked list is a data structure used for holding a sequence of
 * values, which can be added, displayed, reversed, or removed.
 * ### Algorithm
 * This can be done by the slow and fast pointer approach 
 * (two pointer approach),basically in this we make two pointer
 * slow and fast we point slow = head , and fast to the head->next
 * and if length of the L.L is even then traverse till fast!=NULL
 * and we move slow by one step and fast by one step and when fast
 * became null then we just print the slow->data , (our mid element).
 * For the odd length all the process will be same but only one diff. 
 * isthat we need to check instead of fast!=null we have to chek 
 * fast->next!=null and similarlly we print the slow->data
 */


#include <iostream>  /// for I/O operations
 
using namespace std;// defining namespace for cout , cin

/**
 * A Node class containing a value and pointer to another link
 */
class node{
public:
    int data;
    node*next;
    node(int data){
        this->data=data;
        next=NULL;
    }
};
/*
 * A midpoint function use to calculate the mid element of the l.l
 */


void midpoint(int len,node*head){
    node*slow = head;
    node*fast=head->next;
    if(len%2){
        while(fast!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        cout<<slow->data<<" ";
    }
    else{
        while(fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        cout<<slow->data<<" ";
    }
}

/**
 * A print function takes the head node and traverse the l.l
 * and print the data
 */
void print(node*head){
    node*temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
}
/**
 * A length function takes head pointer as a arg and 
 * and len variable increment by 1 whenever we move head by 1
 */
int length(node*head){
    int len =0;
    node*temp = head;
    while(temp!=NULL){
        temp=temp->next;
        len++;
    }
    cout<<"The middle element is:";
    return len;
    /*
    * returning the final length of the linked list 
    */
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){

    /*
    * creating all nodes of the linked list and connecting
    * each other by next and head pointer by dynamically.
    */

    node * head = NULL;
    node* n1 = new  node(1);
    node * n2 = new node(2);
    node * n3 = new node(3);
    node * n4 = new node(4);
    node * n5 = new node(5);
    
    head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next=n4;
    n4->next = n5;
    
    int len1 = length(head);
    midpoint(len1,head);
    return 0;


}