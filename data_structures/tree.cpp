#include<iostream>
using namespace std;

class binaryTree
{
    public:
    class Node
    {   public:
        int val;
        Node *left;
        Node *right;
        Node(int val)
        {
            this->val=val;
            left=nullptr;
            right=nullptr;
        }
    };
    private:
    Node *root=nullptr;
    Node *insert(Node *myNode,int idx,int value,string dir)
    {
        if(myNode==nullptr)
        {
            Node *basecase=new Node(value);
            return basecase;
        }
        if(idx==dir.length())
        {
            myNode->val=value;
            return myNode;
        }
        if(dir[idx]=='R')
        {
            myNode->right=insert(myNode->right,idx+1,value,dir);
        }
        else
        {
            myNode->left=insert(myNode->left,idx+1,value,dir);
        }
        return myNode;
    }
    public:
    void insert(int value,string dir)
    {
        this->root=insert(root,0,value,dir);

    }
    private:
    void display(Node *myNode)
    {
        if(myNode==nullptr)
        {   
            return;
        }
        if(myNode->left!=nullptr)
        {
            cout<<myNode->left->val<<" -> ";
        }
        else
        {
            cout<<" -> ";
        }
        cout<<myNode->val;
        if(myNode->right!=nullptr)
        {
            cout<<" <- "<<myNode->right->val;
        }
        else
        {
            cout<<" <- ";
        }
        cout<<endl;
        display(myNode->left);
        display(myNode->right);
    
    }
    public:
    void display()
    {
        display(root);
    }

};

int main()
{
    binaryTree bt;
    bt.insert(15,"");
    bt.insert(28,"R");
    bt.insert(86,"L");
    bt.insert(21,"LR");
    bt.insert(80,"RR");
    bt.insert(72,"RL");
    bt.insert(5,"L");
    bt.display();
    return 0;
}
