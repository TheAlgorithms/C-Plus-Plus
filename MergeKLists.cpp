#include <iostream>
#include <queue>
#include <vector>

using namespace std; 
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
 };
ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return NULL;
        ListNode* ans = new ListNode(0);
        ListNode* temp = ans;
        priority_queue<pair<int,ListNode*> , vector<pair<int,ListNode*> > , greater < pair<int,ListNode*> > > Q;
        for(int i=0;i<lists.size();i++) {
            if(lists[i]!=NULL)
                Q.push(make_pair(lists[i]->val,lists[i]->next));
        }
        
        while(!Q.empty()) {
            pair<int,ListNode*> topp = Q.top();
            ans->next = new ListNode(topp.first);
            ans = ans->next;
            Q.pop();
            if(topp.second!=NULL)
                Q.push(make_pair(topp.second->val,topp.second->next));
        }
        return temp->next;
    }
 int main() {
    //create n sorted lists and give it to mergeKLists function.
    return 0;
 }