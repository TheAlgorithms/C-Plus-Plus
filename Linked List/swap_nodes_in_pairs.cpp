//Question link: 



//Problem Approach: pp points to the pointer to the current node.
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
        ListNode **pp = &head, *a, *b;
        while ((a = *pp) && (b = a->next)) {
            a->next = b->next;
            b->next = a; 
            *pp = b; 
            pp = &(a->next);
        } 
        return head;
    }
};
