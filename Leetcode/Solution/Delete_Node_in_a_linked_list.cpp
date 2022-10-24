class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node -> next == NULL){
            delete node;
        }
        
        swap(node -> val,node->next->val);
        ListNode* temp=node->next;
        node->next=temp->next;
        delete temp;
    }
};
