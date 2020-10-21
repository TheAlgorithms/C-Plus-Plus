#include<iostream>
using namespace std;
 
struct bintree_node{
    bintree_node *left;
    bintree_node *right;
    int data;
} ;
class bst{
    bintree_node *root;
    public:
    bst(){
        root=NULL;
    }
    int isempty() {
        return(root==NULL);
    }
    void insert(int item);
    void displayBinTree();
    void printBinTree(bintree_node *);
     
};
void bst::insert(int item){
    bintree_node *p=new bintree_node;
    bintree_node *parent;
    p->data=item;
    p->left=NULL;
    p->right=NULL;
    parent=NULL;
    if(isempty())
        root=p;
    else{
        bintree_node *ptr;
        ptr=root;
        while(ptr!=NULL){
            parent=ptr;
            if(item>ptr->data)        
                ptr=ptr->right;
            else
                ptr=ptr->left;
        }   
        if(item<parent->data)
            parent->left=p;
        else
            parent->right=p;
    }
}
void bst::displayBinTree(){
    printBinTree(root);
}
void bst::printBinTree(bintree_node *ptr){
    if(ptr!=NULL){
        printBinTree(ptr->left);
        cout<<"  "<<ptr->data<<"     ";
        printBinTree(ptr->right);
    }
}
int main(){
    bst b;
    b.insert(20);
    b.insert(10);
    b.insert(5);
    b.insert(15);
    b.insert(40);
    b.insert(45);
    b.insert(30); 
     
    cout<<"Binary tree created: "<<endl;
    b.displayBinTree(); 
}
