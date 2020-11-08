/*
Data structure: LinkedList
 
Problem:  The code is the solution to create copy of linked list with random pointers.

Problem link:  https://leetcode.com/problems/copy-list-with-random-pointer/

APPROACH:

Step 1:Create a copy of each node and insert the copy to the right side of the node.(repeat this for each node)

Step 2:we need to copy the random pointers of the original nodes to the copy nodes.

Step 3:Detach the original list with the copy list.

step 4:Return head of copy list.

*/

#include<iostream>
#include <cstdio>
#include <cstdlib>

//definition of a node 
struct Node {  
    int val;
    Node* next;
    Node* random;
    
    Node(int value) {
        val = value;
        next = NULL;
        random = NULL;
    }
};

//function to print the copy list
void print(Node *start) 
{ 
    Node *ptr = start; 
    while (ptr) 
    { 
        std::cout << "Data = " << ptr->val << ", Random  = "<< ptr->random->val <<"\n"; 
        ptr = ptr->next; 
    } 
} 
	
	//method that returns the head of the copy.
    Node* copyRandomList(Node* head) 
    {
        if(head==NULL)
        {
            return NULL;
    	}
    	
		//declaration of node pointers    
        Node* l1=head;
        Node* l3=head;
        
        //creating copy of original linked list without setting random pointers(STEP 1)
        while(l1!=NULL)
        {
        	//creation of new node
            Node* l2 =new Node(l1->val);
            
            //inserting it in the middle of two existing nodes.
            l2->next=l1->next;
            l1->next=l2;
            
            //iterating to next node in the original list
            l1=l1->next->next;
        }
        
        Node* new_head=head->next;
        Node* l4=head;
        
        //setting  random pointers(STEP 2)
        while(l3!=NULL)
        {   
            if(l3->random!=NULL)
            {
            l3->next->random=l3->random->next;
        	}
        	
            l3=l3->next->next;
        }
        
        //detaching the copy and the original list(STEP 3)
        while(l4!=NULL&&l4->next!=NULL)
        {
            
            Node* l5=l4->next;
            
            l4->next=l5->next;
            
            if(l5->next!=NULL)
            {
            l5->next=l5->next->next;
			}
				
            l4=l4->next;
        }
        
        //return head of copy list(STEP 4)
        return new_head;
    }
    
    int main()
    {
		Node* original = new Node(1); 
    	original->next = new Node(2); 
    	original->next->next = new Node(3); 
    	original->next->next->next = new Node(4); 
    	original->next->next->next->next = new Node(5); 
  
    	// 1's random points to 3 
    	original->random = original->next->next; 
  
    	// 2's random points to 1 
    	original->next->random =original; 
  
    	// 3's and 4's random points to 5 
    	original->next->next->random = original->next->next->next->next; 
    	original->next->next->next->random=original->next->next->next->next; 
  
    	// 5's random points to 2 
    	original->next->next->next->next->random =original->next; 
  
	    std::cout << "Original list : \n"; 
    	print(original); 
  
    	std::cout << "\nCloned list : \n"; 
    	
    	Node *cloned_list = copyRandomList(original); 
    	print(cloned_list); 
    return 0; 
	}
    
    
    
