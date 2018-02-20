#include <iostream>
  #include <algorithm>
  using namespace std;
  struct node {
    int data;
    struct node * left;
    struct node * right;
  } * root = NULL;

  struct node * insertNode(struct node * tNode, int value) {
    if(tNode == NULL) {
      struct node * newNode = (struct node *)malloc(sizeof(struct node));
      newNode->data = value;
      newNode->left = NULL;
      newNode->right = NULL;
      return newNode;
    }
    if(tNode->data > value)
      tNode->left = insertNode(tNode->left, value);
    else
      tNode->right = insertNode(tNode->right, value);
    return tNode;
  }

  void buildTree(int a[], int N) {
    for(int i = 0; i < N; i++) {
      if(i) {
        insertNode(root, a[i]);
      } else {
        root = insertNode(NULL, a[i]);
      }
    }
  }

  void PostOrderTraversal(struct node * tNode) {
    if(tNode->left != NULL) PostOrderTraversal(tNode->left);
    if(tNode->right != NULL) PostOrderTraversal(tNode->right);
    cout<<tNode->data<<endl;
  }

  int main() {
    int N;
    cin >> N;
    int arr[N];
    for(int i = 0; i < N; i++) {
      cin >> arr[i];
    }
    buildTree(arr, N);
    PostOrderTraversal(root);
  }
