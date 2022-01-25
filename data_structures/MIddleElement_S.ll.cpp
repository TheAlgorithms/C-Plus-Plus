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
#include <cassert>   ///  for assert
#include <iostream> /// for I/O operations

/**
 * @brief A Node class containing a value and pointer to another link
 * Containing the explicit constructor which contains
 * after creating node and next to nullptr. 
 */
class node{
public:
    int data=0;            ///< The value / key of the node 
    node*next;          ///<  pointer pointing to the next node adress.
 /*
 * @param data stores the value of the node
 */
    explicit node(int data){
        this->data=data;
        next=nullptr;
    }
};

/**
 * @brief Function use to calculate the mid element of the linked list
 * @param len length of the linked list
 * @param head stores the first node address of the LinkedList
 * @returns void 
 */
int  midpoint(int len,node*head){
    node*slow = head;
    node*fast=head->next;
    if(len%2){
        while(fast!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow->data;
        // std::cout<<slow->data<<" ";
    }
    else{
        while(fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }

        return slow->data;
    }
    return 0;
}

/**
 * @brief function takes the head node and traverses the l.l
 * and prints the data 
 * @param head stores the first node address of the linkedlist 
 * @returns void 
 */
void print(node*head){
    node*temp = head;
    while(temp!=nullptr){
        std::cout<<temp->data<<" ";
        temp = temp->next;
    }
}

/**
 * @brief Utility function to calculate the length of the linked list
 * @param head stores the first node address of the LinkedList
 * @returns the length of the linked list
 */
int length(node*head){
    int len =0;
    node*temp = head;
    while(temp!=nullptr){
        temp=temp->next;
        len++;
    }
    return len;
    /*
    * returning the final length of the linked list 
    */
}
/**
* @brief Self-test implementations
 * Initializing head pointer to the nullptr . 
 * creating the  nodes(dynamically) of the linked list and connecting
 * each other by next and head pointer by dynamically.
 * Allows user to calculate the length of the linked list 
 * Also allows user to calculate and display the mid element from the linked list .
* @return void
*/

static void test(){
	// 1st test
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
    // Length of the linked list
    assert(len1 == 5);
    //Midpoint of linked list 
    assert(midpoint(len1,head) == 3);
    std::cout<<"All tests have sucessfully passed!"<<std::endl;
}
/**
 * Main function :
 * @returns 0 on exit
 */
int main(){
	test();  //run self-test implementations
    return 0;
}
