//Question link: https://leetcode.com/problems/swap-nodes-in-pairs/
//Problem Description: Given a linked list, swap every two adjacent nodes and return its head.
//                     You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)


//Approach: pp points to the pointer to the current node.
//So at first, pp points to head, and later it points to the next field of ListNodes.
//Pointers curr and nxt point to the current node and the next node.
//We need to go from *pp == curr -> nxt -> (nxt->next) to *pp == nxt -> curr -> (nxt->next).


//Solution:
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) { 
        ListNode **pp = &head, *curr, *nxt;
        while ((curr = *pp) && (nxt = curr->next)) {
            
            //Swapping the nodes
            curr->next = nxt->next;
            nxt->next = curr; 
            *pp = nxt; 
            
            //Traversing in the list
            pp = &(curr->next);
        } 
        return head;
    }
};
