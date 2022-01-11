/**
 * @file 
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
 #include <iostream> // for I/O operations

/**
 * A Node class containing a value and pointer to another link
 * Containing the explicit constructor which contains
 * @param data that always initialize to the node data every time 
 * after creating node and next to nullptr. 
 */
class node{
public:
    int data;            ///< The value / key of the node 
    node*next;          ///<  pointer pointing to the next node adress.
    explicit node(int data){
        this->data=data;
        next=nullptr;
    }
};

/**
 * function use to calculate the mid element of the linked list.
 * @param len is the length of the linked list .
 * @param head stored the first node address of the linkedlist .
 * @returns 'void' 
 */
void midpoint(int len,node*head){
    node*slow = head;
    node*fast=head->next;
    if(len%2){
        while(fast!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        std::cout<<slow->data<<" ";
    }
    else{
        while(fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        std::cout<<slow->data<<" ";
    }
}

/**
 * function takes the head node and traverse the l.l
 * and print the data . 
 * @param head stored the first node address of the linkedlist .
 * @returns 'void' 
 */
void print(node*head){
    node*temp = head;
    while(temp!=nullptr){
        std::cout<<temp->data<<" ";
        temp = temp->next;
    }
}

/**
 * function used to calculate the length of the linked
 * list .
 * @param head stored the first node address of the linkedlist .
 * @returns len that is the length of the linked list.
 */
int length(node*head){
    int len =0;
    node*temp = head;
    while(temp!=nullptr){
        temp=temp->next;
        len++;
    }
    std::cout<<"The middle element is:";
    return len;
    /*
    * returning the final length of the linked list 
    */
}

/**
 * Main function :
 * Initializing head pointer to the nullptr . 
 * creating the  nodes(dynamically) of the linked list and connecting
 * each other by next and head pointer by dynamically.
 * Allows user to calculate the length of the linked list 
 * Also allows user to calculate and display the mid element from the linked list .
 * @returns 0 on exit
 */
int main(){
    node * head = nullptr;
    node *n1 = new  node(1);
    node *n2 = new node(2);
    node *n3 = new node(3);
    node *n4 = new node(4);
    node *n5 = new node(5);
    
    head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next= n4;
    n4->next = n5;
    
    int len1 = length(head);
    midpoint(len1,head);
    return 0;
}
