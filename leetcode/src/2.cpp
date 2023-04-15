/* You are given two non - empty linked lists representing two non - negative integers.
 * The digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbersand return the sum as a linked list.
 */

#include <memory>

 /*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0;
    std::unique_ptr<ListNode> head(new ListNode(0));
    ListNode* sum = head.get();

    while(l1 || l2) {
        int val = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
        carry = val/10;
        sum->next = new ListNode(val%10);
        sum = sum->next;
        l1 = (l1 ? l1->next : nullptr);
        l2 = (l2 ? l2->next : nullptr);
    }
    if(carry){
        sum->next = new ListNode(carry);
    }

    return head->next;
}
};
