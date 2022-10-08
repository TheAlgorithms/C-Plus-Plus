#include<bits/stdc++.h>
#include<tree.cpp>

vector<int> inorderTraversal(node* root) {
        if(root==NULL){
            return {};
        }
        stack<node*>s;
        vector<int>v;
        node* temp=root;
        while(true){
            if(temp!=NULL){
                s.push(temp);
                temp=temp->left;
            } 
            if(temp==NULL && !s.empty()){
                v.push_back(s.top()->val);
                temp=s.top()->right;
                s.pop();
            }
            if(temp==NULL && s.empty()) break;
        }
    return v;
}