#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;


class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        left = right = NULL;
    }
};

static int idx = -1;

Node* buildTree(vector<int> nodes){
    
    idx++;
    if(nodes[idx] == -1){
        return nullptr;
    }

    Node* currNode = new Node(nodes[idx]);
    currNode->left = buildTree(nodes);
    currNode->right = buildTree(nodes);

    return currNode;
}


void topView(Node* root){
    queue<pair<Node*,int>> Q; 
    map<int, int> m;

    Q.push(make_pair(root, 0));

    while(!Q.empty()){
        pair<Node*, int> curr = Q.front(); 
        Q.pop();

        Node* currNode = curr.first;
        int currHd = curr.second;

        if(m.count(currHd) == 0) {
            m[currHd] = currNode->data;
        }

        if(currNode->left != NULL){
            pair<Node*, int> left = make_pair(currNode->left, currHd-1); 
            Q.push(left);
        }

        if(currNode->right != NULL){
            pair<Node* , int> right = make_pair(currNode->right, currHd+1);
            Q.push(right);
        }
    }

    for(auto it : m){
        cout << it.second << " "; 
    }

    cout << endl;
}

int main()
{
   vector<int> nodes = {1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1};
   Node* root = buildTree(nodes);

   cout << "root = " << root->data <<  endl;

   topView(root);
}