#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left, * right;
	TreeNode(int data)
	{
		this->data = data;
		left = right = NULL;
	}
};

void print(vector<int>ans) {
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
}

TreeNode* newNode(int data)
{
	TreeNode* temp = new TreeNode(data);
	return temp;
}


TreeNode* make_BST(TreeNode* root, int data)
{
	if (root == NULL)
		return newNode(data);
	else
	{
		if (data <= root->data)
			root->left = make_BST(root->left, data);
		else
			root->right = make_BST(root->right, data);

		return root;
	}
}


void Postorder(TreeNode* root, vector<int>&ans)
{
	if (root == NULL)
		return;

	Postorder(root->left,ans);
	Postorder(root->right,ans);

	ans.push_back(root->data);
}


void Inorder(TreeNode* root, vector<int>& ans)
{
	if (root == NULL)
		return;

	Inorder(root->left,ans);
	ans.push_back(root->data);
	Inorder(root->right,ans);
}

void Preorder(TreeNode* root, vector<int>&ans)
{
	if (root == NULL)
		return;

	ans.push_back(root->data);
	Preorder(root->left,ans);
	Preorder(root->right,ans);
}

void test(TreeNode* testcase) {


	vector<int> ans_pre = { 100,20,10,30,200,150,300 }, ans_post = { 10,30,20,150,300,200,100 }, ans_in = { 10,20,30,100,150,200,300 };
	vector<int> ans1, ans2, ans3;

	Inorder(testcase, ans1);
	assert(ans_in == ans1);
	cout << "Inorder successfull : ";
	print(ans1);
	cout << endl;

	Preorder(testcase, ans2);
	assert(ans_pre == ans2);
	cout << "Preorder successfull : ";
	print(ans2);
	cout << endl;

	Postorder(testcase, ans3);
	assert(ans_post== ans3);
	cout << "Postorder successfull : ";
	print(ans3);
	cout << endl;


	cout << "TestCases Passed";

}

int main() {

	vector<int>v = { 100,20,200,10,30,150,300 };

	int i = 0;

	TreeNode* root = NULL;
	while (i < v.size()) {
		root = make_BST(root, v[i]);
		i++;
	}
	test(root);


	return 0;

}

