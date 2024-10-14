// #include <iostream>
// #include <vector>
// using namespace std;


// class Node {
//     public:
//     int data;
//     Node* left;
//     Node* right;

//     Node(int data){
//         this->data = data;
//         left = right = NULL;
//     }
// };

// static int idx = -1;

// Node* buildTree(vector<int> nodes){
//     idx++;

//     if(nodes[idx] == -1){
//         return NULL;
//     }

//     Node* currNode = new Node(nodes[idx]);
//     currNode->left = buildTree(nodes);
//     currNode->right = buildTree(nodes);

//     return currNode;
// }

// int sumNode(Node* root){
//     if(root == NULL){
//         return 0;
//     }

//     int leftSum = sumNode(root->left);
//     int rightSum = sumNode(root->right);

//     return leftSum + rightSum + root->data;

// }

// int main()
// {
//     vector<int>  nodes = {1,2,3,-1,-1,5,-1,-1,3,-1,6,-1,-1};

//    Node* root =  buildTree(nodes);
   
//    cout << "Roots = " << root->data << endl;

//    Node* root2 = new Node(5);
//    root2->left = new Node(3);
//    root2->right = new Node(10);
//    cout << "Sum of nodes :" << sumNode(root2) << " ";
// }

#include <iostream>
using namespace std;

int f(int* a, int b) {
    b = b - 1;
    if (b == 0) return 1;
    *a = *a + 1; // '*a' accesses the value pointed to by pointer 'a'
    return f(a, b) * (*a);
}

int main() {
    int a = 3;
    int b = 3;
    cout <<  f(&a, b);
}
