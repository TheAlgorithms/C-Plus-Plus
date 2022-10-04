#include<bits/stdc++.h>
using namespace std;
#define maxElements 4
// Creating a node class
class Node {
public:
   // Initialising data members
   int num_elements; 
   int array[maxElements];
   Node* next; 

   Node(int n) 
   {
       next = NULL;
       num_elements = 0; 
       array[n]; 
   }
};
// Unrolled Linked List Class
class UnrolledLinkedList {
public:
   Node *head; 
   Node *tail; 
   int node_size; 
   int tot_nodes; 
   
   UnrolledLinkedList(int capacity)
   {
       head = NULL; 
       tail = NULL;
       tot_nodes = 0; 
       node_size = capacity + 1; 
   }

   // Insertion Operation Function
   void insert(int num){
       tot_nodes++; 
       if (head == NULL) { 
           head = new Node(node_size); 
           head->array[0] = num; 
           head->num_elements++; 
           tail = head;
           return;
       }
       
       if (tail->num_elements + 1 < node_size) { 
           tail->array[tail->num_elements] = num;
           tail->num_elements++;  
       }
    
       else {
           Node *new_node = new Node(node_size);
           int j = 0;
           
           for (int i = tail->num_elements / 2 + 1;i < tail->num_elements; i++)
               new_node->array[j++] = tail->array[i];

           new_node->array[j++] = num;
           new_node->num_elements = j;
           tail->num_elements = tail->num_elements / 2 + 1;
           tail->next = new_node;
           tail = new_node;
       }
   }
   // Print Operation Function
   void print()
   {
       cout<<"Unrolled Linked List: "<<endl;
       Node *temp = head;
       while (temp != NULL) {
           for (int i = 0; i < temp->num_elements; i++)
               cout<<(temp->array[i])<<" ";
           cout<<endl;
           temp = temp->next;
       }
   }
};

// Main Function
int main(){
   UnrolledLinkedList *list = new UnrolledLinkedList(4); 
   int n; 
   cin>>n;
   for (int i = 0; i <n; i++) {
       int x;
       cin>>x;
       list->insert(x);
   }
   list->print();
};
