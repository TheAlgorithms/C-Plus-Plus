#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T>
class TreeNode {
   public:
    T data;
    vector<TreeNode<T>*> children;

    TreeNode(T data) { this->data = data; }

    ~TreeNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }
};

bool areIdentical(TreeNode<int> *root1, TreeNode<int> * root2)
{
    
    if(root1 == NULL && root2 == NULL)
    {
		return false;
    }
    
    if(root1->data == root2->data)
    {
        return true;
    }
    
    int x = root1->children.size();
    int y = root2->children.size();
    
    if(x ==y)
    {
        for(int i=0;i<x;i++)
        {
           if(areIdentical(root1->children[i],root2->children[i]))
           {
               return true;
           }
         	return false;
        }
    }
    else
    {
        return false;
	}
}

TreeNode<int>* takeInputLevelWise() {
    int rootData;
    cin >> rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);

    queue<TreeNode<int>*> pendingNodes;

    pendingNodes.push(root);
    while (pendingNodes.size() != 0) {
        TreeNode<int>* front = pendingNodes.front();
        pendingNodes.pop();
        int numChild;
        cin >> numChild;
        for (int i = 0; i < numChild; i++) {
            int childData;
            cin >> childData;
            TreeNode<int>* child = new TreeNode<int>(childData);
            front->children.push_back(child);
            pendingNodes.push(child);
        }
    }

    return root;
}

int main() {
    TreeNode<int>* root1 = takeInputLevelWise();
    TreeNode<int>* root2 = takeInputLevelWise();
    cout << (areIdentical(root1, root2) ? "true" : "false");
}