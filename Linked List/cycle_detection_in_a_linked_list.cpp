//Question_link : https://leetcode.com/problems/linked-list-cycle/
//Problem Description : Check if there is a cycle in a linked list. If it does, return true; else return false.


//Approach: Below is a classic algorithm for detection of cycles called Floyd's Cycle Detection Algorithm. 
//Here we use two pointers to traverse the list: The first one is moving one node at the time and the second two nodes at the time.
//If there is a cycle, sooner or later pointers will meet and we return true. 
//If the fast pointer reached the end of the list, that means there is no cycle and we can return false.


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        //Nodes slow and fast pointing to head initially which would then traverse over the list to find the loop
        ListNode *slow = head, *fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            
            //When there is a loop
            if (slow == fast) return true;
        }
        
        
        //No loop is present
        return false;
    }
};
