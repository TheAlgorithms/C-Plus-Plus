//struct ListNode {
//    int val;
//    ListNode *next;
//    ListNode(int x) : val(x), next(NULL) {}
//};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *first, *last;
        int carry = 0;

        first = new ListNode(0);
        last = first;
        while (l1 != NULL || l2 != NULL || carry) {
            ListNode *l;
            int sum = (l1? l1->val : 0) + (l2? l2->val : 0) + carry;

            carry = 0;
            if (sum > 9) {
                sum = sum % 10;
                carry = 1;
            }
            l = new ListNode(sum);
            last->next = l;
            last = l;

            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }

        return first->next;
    }
};