link-https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/

striver link-https://takeuforward.org/data-structure/remove-n-th-node-from-the-end-of-a-linked-list/




ListNode * dummy=new ListNode();
start->next=head;
ListNode* fast=start;
ListNode* slow=start;
for(int i=1;i<=n;i++)
  fast=fast->next;
while (fast->next!=NULL)
{
   fast=fast->next;
   slow=slow->next;
}
slow->next=slow->next->next;
return start->next;
//  this is my second contribution
