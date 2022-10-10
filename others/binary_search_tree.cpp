#include<iostream>
using namespace std;

struct BSTNode
{
  int data;
  BSTNode* left;
  BSTNode* right;
};

BSTNode* GetNewNode(int data)
{
  BSTNode* newNode = new BSTNode();
  newNode -> data = data;
  newNode -> left = NULL;
  newNode -> right = NULL;
  return newNode;
}

BSTNode* Insert(BSTNode* root, int data)  //BST** root
{
  if(root == NULL)  //*root
  {
    root = GetNewNode(data);  //*root
  }
  else if(data <= root -> data)
  {
    root -> left = Insert(root -> left, data);  //insert data in left subtree
  }
  else
  {
    root -> right = Insert(root -> right, data);
  }
  return root;
}

bool Search(BSTNode* root, int data)
{
  if(root == NUL)
    return false;
  else if(root -> data == data)
    return true;
  else if(data <= root -> data)
    return Search(root -> left, data);
  else
    return Search(root -> right, data);
}

int main()
{
  BSTNode* root = NULL;
  root = Insert(root, 15);  //&root
  root = Insert(root, 10);  //&root
  root = Insert(root, 20);  //&root
  root = Insert(root, 25);  //&root
  root = Insert(root, 8);   //&root
  root = Insert(root, 12);  //&root
  
  int number;
  cout << "Enter number be searched\n";
  cin >> number;
  
  if(Search(root, number) == true)
    cout << "Found" << endl;
  else
    cout << "Not found" << endl;
}
