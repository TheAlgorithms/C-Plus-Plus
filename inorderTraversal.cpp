#include<iostream>
#include<vector>
using namespace std;

struct Node{
  struct Node* left;
  struct Node* right;
  int val;
  Node(int val){
    //parameterized constructor
    this->val = val;
    left = right = NULL; 
  }
};

void insertNode(struct Node* root,int val){
  if(root == NULL)
  return;
  struct Node* prev = NULL;
  
  while(root!=NULL){
    prev = root;
    if(root -> val < val)
    root = root->right;
    else if(root->val > val)
    root = root->left;
    else if(root->val == val)
    return;
  }

  if(prev->val < val){
    prev->right = new Node(val);
  }else{
    prev->left = new Node(val);
  }
  
}


//inorder traversal using recursion technique.
void inorder(struct Node* root){
  if(root == NULL)
  return;
  
  inorder(root->left);
  cout<<root->val<<" ";
  inorder(root->right);
}

int main(){
  int n;
  cout<<"Enter the number of nodes you want to enter : ";
  cin>>n;
  int v;
  cout<<"Enter the parent node : ";cin>>v;
  struct Node* root = new Node(v);
  while(n--){
      cout<<"Enter the value : ";
      cin>>v;
      insertNode(root,v);
  }
  inorder(root);
  return 0;
}
