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
    ListNode* deleteMiddle(ListNode* head) {
        if(head==NULL)
        {
            return head;
        }
        if(head->next==NULL)
        {
            head=NULL;
            return head;
        }
        // ListNode *temp=head;
        // int count=0;
        // while(temp!=NULL)
        // {
        //     count++;
        //     temp=temp->next;
        // }
        // int mid=count/2;

        // ListNode *temp1=head;
        // int n=0;
        // while(temp1!=NULL)
        // {
            
        //     if(n+1==mid)
        //     {
        //         temp1->next=temp1->next->next;
        //         break;
        //     }
        //     temp1=temp1->next;
        //     n++;
        // }
        // return head;


        ListNode* fast=head;
        ListNode* slow=head;
        if(fast->next->next==NULL)
        {
            fast->next=NULL;
            return head;
        }

        while(fast->next!=NULL && fast->next->next!=NULL)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* temp=head;
        while(temp!=NULL)
        {
            if(temp->next==slow and fast->next==NULL)
            {
                temp->next=slow->next;
                break;
            }
            else if(temp->next==slow and fast->next->next==NULL)
            {
                temp=slow;
                temp->next=temp->next->next;
                break;
            }
           
            temp=temp->next;
        }
        return head;
    }
};
