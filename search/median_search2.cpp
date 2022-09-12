/**
 * @file
 *
 * @details
 * Given a linked list L[0,....,n] of n numbers, find the middle node.
 *
 * Here are some example lists you can use to see how the algorithm works
 * A = [1,2,3,4,5]
 * B = [1,2,3,4,5,6]
 * print median(A) #should be 39
 * print median(B) #should be 4
 *
 * @author [Benjamin Weiss](https://github.com/weiss-ben)
 */

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
 #include <iostream>
 #include <cassert>

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {
/**
 * @namespace median_search
 * @brief Functions for the Median Search algorithm implementation.
 */
namespace median_search2 {
/**
* This function searches for the median of a linked list.
* @param head, The head of the linked list.
* @returns Median node of the linked list.
*/  
ListNode* middleNode(ListNode* head) {
    if(!head)
        return nullptr;
        
    //Fast and slow pointers
    ListNode* fastptr;
    ListNode* slowptr = fastptr = head;
    
	// fast jumps 2 while slow jumps 1    
    while(fastptr->next && fastptr->next->next) {
        slowptr = slowptr->next;
        fastptr = fastptr->next->next;
    }
    return (fastptr->next) ? slowptr->next : slowptr;
        
}
}  // namespace median_search2
}  // namespace search

/**
 * Function to test above algorithm
 */
void test(){
	ListNode* head = new ListNode;
	head->val = 1;
	
	ListNode* temp1 = head;
	for(int i = 1; i < 6; ++i)
	{
		ListNode* temp2 = new ListNode;
		temp2->val = i;
		
		temp1->next = temp2;
		temp1 = temp2;
	}
	
	ListNode* median = search::median_search2::middleNode(head);
	assert(3 == median->val);		// 3 is the value of the median node.
	std::cout << "test case:1 passed\n";
	
	// Clean up
	while(head)
	{
		ListNode* t = head->next;
		delete head;
	}
	
	ListNode* head = new ListNode;
	head->val = 1;
	
	ListNode* temp1 = head;
	for(int i = 1; i < 7; ++i)
	{
		ListNode* temp2 = new ListNode;
		temp2->val = i;
		
		temp1->next = temp2;
		temp1 = temp2;
	}
	
	ListNode* median = search::median_search2::middleNode(head);
	assert(4 == median->val);		// 3 is the value of the median node.
	std::cout << "test case:1 passed\n";
	
	// Clean up
	while(head)
	{
		ListNode* t = head->next;
		delete head;
	}
	std::cout << "--All tests passed--\n";
}

/**
 * Main function
 */
int main()
{
	test();
	return 0;
}
