#include<bits/stdc++.h>
using namespace std;

class btSearchTree;
class Node{
    int data;
    Node* left;
    Node* right;
public:
    Node(){
        data = 0;
        left = NULL;
        right = NULL;
    }
    Node(int value){
        data = value;
        left = NULL;
        right = NULL;
    }
    friend class btSearchTree;
};

class btSearchTree{
private:
    Node* root;
public:    
    btSearchTree(){
        root = NULL;
        cout<<"Empty Search Tree Created!"<<endl;
    }
    
    void insert(int value);
    void inOrder(Node* root);
    void inOrderDisplay();
};

void btSearchTree :: insert(int value){
    Node* pNew;
    pNew = new Node(value);
    if(root == NULL){
        root = pNew;
        cout<<"\nRoot Created = "<<root->data<<endl;
    }
    else{
        Node* temp;
        temp = root;
        do{
            if(value < temp->data){  //compare value of inserted node with root for direction decision
                if(temp->left == NULL){
                    temp->left = pNew;
                    cout<<"\nNode Inserted to left of : "<<temp->data<<endl;
                    break;
                }
                else{
                    temp = temp->left;
                }
            }
            else if(value > temp->data){
                if(temp->right == NULL){
                    temp->right = pNew;
                    cout<<"\nNode Inserted to right of : "<<temp->data<<endl;
                    break;
                }
                else{
                    temp = temp->right;
                }
                
            }
            else{
                cout<<"Duplicate value found!"<<endl;
                break;
            }
        }while(temp != NULL);
    }
}

void btSearchTree :: inOrder(Node* root){
    if(root != NULL){
        inOrder(root->left);
        cout<<root->data<<" - ";
        inOrder(root->right);
    }
}

void btSearchTree :: inOrderDisplay(){
    return inOrder(root);
}

int main()
{
    btSearchTree bst1; //class object

    bst1.insert(5);
    bst1.insert(6);
    bst1.insert(1);
    bst1.insert(3);
    bst1.insert(4);
    bst1.insert(10);

    bst1.inOrderDisplay();
    
    return 0;
}