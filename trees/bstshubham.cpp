#include<iostream>
using namespace std;
struct node{
    int val;
    node* left;
    node* right;
};

class BST
{
public:
    node *root;
    BST(){
   	 root=NULL;
    }
    node* insert(int,node*p);
    node* deleteNode(int,node*);
    void inorder(node *p);
    node *inordersuccessor(node* p);
   	 
};
node* BST::inordersuccessor(node* p){
    p=p->right;
    while(p->left!=NULL){
   	 p=p->left;
    }
    return p;
}
node* BST::insert(int val,node* p){
    
    if(!p){
   	 node* temp=new node;
   	 temp->val=val;
   	 temp->left=NULL;
   	 temp->right=NULL;
   	 if(root==NULL)
   		 root=temp;
   	 return temp;
    }
    if(val<p->val)
   	 p->left=insert(val,p->left);
    else if(val>p->val)
   	 p->right=insert(val,p->right);
    else
   	 cout<<"Duplicates not allowed in a Binary Search Tree";

    return p;

}
node* BST::deleteNode(int val,node*p){
    if(p==NULL){
   	 cout<<"Number not found";
   	 return p;
    }
    
    if(val<p->val)
   	 p->left=deleteNode(val,p->left);
    else if(val>p->val)
   	 p->right=deleteNode(val,p->right);
    else{
   	 //node to be deleted
   	 if(!p->left && p->right){
   		 if(p==root){
   			 root=root->right;
   			 delete p;
   			 return root;
   		 }
   		 return p->right;
   	 }
   	 else if(p->left && !p->right){
   		 if(p==root){
   			 root=root->left;
   			 delete(p);
   			 return root;
   		 }
   		 return p->left;
   	 }
   	 else if(p->left && p->right){
   		 node *temp=inordersuccessor(p);
   		 p->val=temp->val;
   		 p->right=deleteNode(temp->val,p->right);

   	 }
   	 else{
   		 if(p==root)
   			 root=NULL;
   		 delete p;
   		 return NULL;
   	 }
    }
    return p;
}
void BST::inorder(node* p){
    if(!p)
   	 return ;
    inorder(p->left);
    cout<<" "<<p->val;
    inorder(p->right);
}
int main(){
    BST tree;
    int choice=1;
    int val;
    while(choice!=4){
   	 cout<<"\n1.Insert in BST\n2.Delete from BST\n3.Display inorder\n4.Exit";
   	 cin>>choice;
   	 switch(choice){
   		 case 1:
   		 cout<<"\nNumber to be inserted:";cin>>val;
   		 tree.insert(val,tree.root);
   		 break;
   		 case 2:
   		 cout<<"\n Number to be deleted";cin>>val;
   		 tree.deleteNode(val,tree.root);
   		 break;
   		 case 3:
   		 cout<<"\nInorder:";
   		 tree.inorder(tree.root);
   		 break;
   		 default:break;
   	 }

    }

    return 0;
}

