/**
 * @file
 * @brief Given a linked list L[0,....,n] of n numbers, find the middle node.
 * 
 * @details The technique utilized in this implementation is the "Floyd's tortise and hare" approach. Wikipedia link to technique: https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_tortoise_and_hare
 * This technique uses two pointers that iterate through the list at different 'speeds' in order to solve problems.
 * In this implementation, for every iteration the slow pointer advances one node while the fast pointer advances two nodes. 
 * The result of this is that since the fast pointer moves twice as fast as the slow pointer, when the fast pointer reaches the end of the list 
 * the slow pointer will be pointing to the middle node of the list. 
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
    int val;                                                   ///< the value stored in the node
    ListNode *next;                                            ///< pointer to the next node
    ListNode() : val(0), next(nullptr) {}                     ///< default constructor
    ListNode(int x) : val(x), next(nullptr) {}               ///< constructor with value for node->val provided
    ListNode(int x, ListNode *next) : val(x), next(next) {}  ///< constructor with values provided for node->val and node->next
 };
 
 #include <iostream> /// for IO operations
 #include <cassert>  /// for assert

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {
/**
 * @namespace median_search
 * @brief Functions for the Median Search algorithm implementation. Wkipedia link to algorithm: https://en.wikipedia.org/wiki/Median_search
 */
namespace median_search2 {
/**
* This function searches for the median of a linked list.
* @param head The head of the linked list.
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
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
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
	
	head = new ListNode;
	head->val = 1;
	
	temp1 = head;
	for(int i = 1; i < 7; ++i)
	{
		ListNode* temp2 = new ListNode;
		temp2->val = i;
		
		temp1->next = temp2;
		temp1 = temp2;
	}
	
	median = search::median_search2::middleNode(head);
	assert(4 == median->val);		// 3 is the value of the median node.
	std::cout << "test case:1 passed\n";
	
	// Clean up
	while(head)
	{
		ListNode* t = head->next;
		delete head;
	}
	std::cout << "test case:2 passed\n";
	std::cout << "--All tests passed--\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
	test();  // run self-test implementations
	return 0;
}
