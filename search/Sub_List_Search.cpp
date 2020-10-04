

/**
 * @file
 * @brief Searching a linked list inside another linked list
 * @author [Aaryan Singh](https://github.com/Aaryan2104)
 * @details
 * 1.Create two linked lists first and second, and set pointers to the head nodes of each list, pointer1 and pointer2 respectively.
 * 2.Compare the data in pointer1 and pointer2, if they match then increment both pointers.
 * 3.If a mismatch occurs at any point, bring pointer1 to the head of first list, and pointer2 to successive pointer if its initial value.
     and go to step 2.
 * If pointer1 becomes NULL before any mismatch can occur, the search is successful.  
 * If pointer2 becomes NULL before pointer1, then search is unsuccessful.
 
 Some examples : Search if list 1 is present in list 2:
 1.
 List 1 : 55->68->23
 List 2 : 23->67->55->68->23->12
 Successful search, as List 1 is in List 2 (nodes 3 to 5)
 
 2.
 List 1: 22->45->65
 List 2: 22->45
 Unsuccessful, List 2 reaches its end (NULL) before List-1.
 */
 


#include <iostream> 
using namespace std; 

/** @brief A structure that defines the node of a linked list, contains "data" and "next" link to the successive node
**/

struct Node 
{ 
	int data; 
	Node* next; 
}; 


/** @brief Function SublistSearch(Node*, Node*) searches if first list is present inside of second list
	@returns true if search successful, else returns false
**/

 
bool Sub_List_Search(Node* first, Node* second) 
{ 
	Node* temp1 = first;
	Node* temp2 = second; 


	if (first == NULL && second == NULL) 
		return true; 


	if ( first == NULL && second != NULL) 
		return true; 
	
	if( first != NULL && second == NULL) 
		return false;


	while (second != NULL) 
	{ 

		temp2 = second; 

		// Start matching first list with second list 
		while (temp1 != NULL) 
		{ 

			if (temp2 == NULL) 
				return false; 

			if (temp1->data == temp2->data) 
			{ 
				temp1 = temp1->next; 
				temp2 = temp2->next; 
			} 
			else break; 
			
		} 

		if (temp1 == NULL) 
			return true; 

		temp1 = first; 
		second = second->next; 
	} 

	return false; 
} 

/** 
	@brief Function printList which accepts a pointer to node and print the entire list from that node
	@returns 0
**/

void print_List(Node* temp) 
{ 
	while (temp != NULL) 
	{ 
		cout<<temp->data; 
		temp = temp->next; 
	} 
} 

/** @brief Function newNode which creates a new node, equals "data" stored in node to input parameter key
		   and sets its "pointer to node" to NULL
	@returns pointer to the the new node created
**/

Node* newNode(int data) 
{ 
	Node *node = new Node; 
	node-> data= data; 
	node->next = NULL; 
	return node; 
} 




/** @brief Test function1 with lists a: 5->6->7->8 
									 b: 5->6->5->6->7->8
	@returns none
**/		

void test_function1() {
	
	
	Node* first = newNode(5); 
	first->next = newNode(6); 
	first->next->next = newNode(7); 
	first->next->next->next = newNode(8); 

	Node* second = newNode(5); 
	second->next = newNode(6); 
	second->next->next = newNode(5); 
	second->next->next->next = newNode(6); 
	second->next->next->next->next = newNode(7); 
	second->next->next->next->next->next = newNode(8); 

	if(Sub_List_Search(first,second) == true)  
		cout << "Search successful, list" << print_List(first)<<" found"<<endl;
	else
		cout << "Search unsuccessful, list not found"<<endl;
	 
}  

/** @brief Test function2 with lists a: 22->33->44 
									 b: 22->33->11->22->33
	@returns none
**/							


void test_function2() {
	
	Node* first = newNode(22); 
	first->next = newNode(33); 
	first->next->next = newNode(44); 
	 

	Node* second = newNode(22); 
	second->next = newNode(33); 
	second->next->next = newNode(11); 
	second->next->next->next = newNode(22); 
	second->next->next->next->next = newNode(33); 
	
	if(Sub_List_Search(first,second) == true)  
		cout << "Search successful, list"<<print_List(first)<<" found"<<endl;
	else
		cout << "Search unsuccessful, list not found"<<endl;
	
	
	
}  
  
/** 
	@brief Main function
	@returns 0 on exit
	
**/
  

int main() 
{ 
	
	test_function1();
	test_function2();

	return 0; 
} 

