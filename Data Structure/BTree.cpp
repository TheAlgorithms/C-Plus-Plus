#include <iostream>
#include <climits>
#include <cstdbool>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;
typedef struct BTreeNode {
	int *keys;  // An array of keys
	struct BTreeNode *P; // An array of parent pointer
	struct BTreeNode **C; // An array of child pointers
	int n;     // Current number of keys
	bool leaf; // Is true when node is leaf. Otherwise false
} BTreeNode;


BTreeNode *root; // Pointer to root node
int t;  // Minimum degree


void traverse(); // A function to traverse all nodes in a subtree rooted with this node
BTreeNode* search(int k); // function to search a key in this tree
void insertElement(int k); // The main function that inserts a new key in this B-Tree
void removeElement(int k); // The main function that removes a new key in thie B-Tree
void BTreeInit(int _t); // Initializes tree as empty


BTreeNode* _createNode(bool _leaf);
void _insert(BTreeNode* present, int k);
void _balancing(BTreeNode* present);
void _balancingAfterDel(BTreeNode* present);


BTreeNode* _splitChild(BTreeNode* present);
void _traverse(BTreeNode* present);
BTreeNode* _search(BTreeNode* present, int k);
void _remove(BTreeNode* present, int k);


void _borrowFromRight(BTreeNode* present, int idx);
void _borrowFromLeft(BTreeNode* present, int idx);
BTreeNode* _merge(BTreeNode* present);

int _getLevel(BTreeNode* present);
void _getNumberOfNodes(BTreeNode* present, int* numNodes, int level);
void _mappingNodes(BTreeNode* present, BTreeNode ***nodePtr, int* numNodes, int level);
void printTree();

void BTreeInit(int _t)
{
	root = NULL;  t = _t - 1;
}


void traverse()
{
	if (root != NULL) _traverse(root);
}


BTreeNode* search(int k)
{
	return (root == NULL) ? NULL : _search(root, k);
}


BTreeNode* _createNode(bool _leaf)
{
	BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
	int i;

	// Copy the given minimum degree and leaf property
	newNode->leaf = _leaf;

	// Allocate memory for maximum number of possible keys
	// and child pointers
	newNode->keys = (int*)malloc(sizeof(int) * (t + 1));
	newNode->C = (BTreeNode**)malloc(sizeof(BTreeNode*)*(t + 2));

	// Initialize child
	for (i = 0; i < t + 2; i++)
		newNode->C[i] = NULL;

	// Initialize the number of keys as 0
	newNode->n = 0;

	// Initialize parent
	newNode->P = NULL;

	return newNode;
}




void _traverse(BTreeNode* present)
{
	// There are n keys and n+1 children, travers through n keys and first n children
	int i;
	for (i = 0; i < present->n; i++)
	{
		// If this is not leaf, then before printing key[i],
		// traverse the subtree rooted with child C[i].
		if (present->leaf == false)
			_traverse(present->C[i]);

		printf(" ");
		printf("%d", present->keys[i]);
	}

	// Print the subtree rooted with last child
	if (present->leaf == false)
		_traverse(present->C[i]);
}


BTreeNode* _search(BTreeNode* present, int k)
{
	// Find the first key greater than or equal to k
	int i = 0;
	while (i < present->n && k > present->keys[i])
		i++;

	// If the found key is equal to k, return this node
	if (present->keys[i] == k)
		return present;

	// If key is not found here and this is a leaf node
	if (present->leaf == true)
		return NULL;

	// Go to the appropriate child
	return _search(present->C[i], k);
}


void insertElement(int k)
{
	// Find key in this tree, and If there is a key, it prints error message.
	if (search(k) != NULL)
	{
		printf("The tree already has %d \n", k);
		return;
	}

	// If tree is empty
	if (root == NULL)
	{
		// Allocate memory for root
		root = _createNode(true);
		root->P = NULL; // Init parent
		root->keys[0] = k;  // Insert key
		root->n = 1;  // Update number of keys in root
	}
	else // If tree is not empty
		_insert(root, k);
}


void _insert(BTreeNode* present, int k)
{
	// Initialize index as index of rightmost element
	int i = present->n;

	// If this is a leaf node
	if (present->leaf == true)
	{
		//-------------------------------------------------------------------------------------------------------
		//Write your code.
		for (int j = i - 1; j >= 0; j--)
		{
			if (present->keys[j] > k)
			{
				present->keys[j + 1] = present->keys[j];
			}
			else
			{
				present->keys[j + 1] = k;
				present->n++;
				_balancing(present);
				return;
			}
		}
		present->keys[0] = k;
		present->n++;
		_balancing(present);


		//-------------------------------------------------------------------------------------------------------
	}
	else // If this node is not leaf
	{
		//-------------------------------------------------------------------------------------------------------
		//Write your code.
		for (int j = 0; j < present->n; j++)
		{
			if (k <= present->keys[j])
			{
				_insert(present->C[j], k);
				return;
			}
		}
		if (k > present->keys[present->n - 1])
		{
			_insert(present->C[present->n], k);
		}



		//-------------------------------------------------------------------------------------------------------
	}
}


void _balancing(BTreeNode* present)
{
	BTreeNode* parent;

	if (present->n <= t)
	{
		return;
	}
	else if (present->P == NULL)
	{
		root = _splitChild(present);
		return;
	}
	else
	{
		parent = _splitChild(present);
		_balancing(parent);
	}
}


BTreeNode * _splitChild(BTreeNode* present)
{
	int i;
	int splitIndex;
	int risingKey;
	int parentIndex;
	BTreeNode *currentParent;
	BTreeNode *left;
	BTreeNode *right = _createNode(present->leaf);

	splitIndex = t / 2;

	right->n = present->n - splitIndex - 1;
	risingKey = present->keys[splitIndex];

	if (present->P != NULL)
	{
		currentParent = present->P;
		for (parentIndex = 0; parentIndex < currentParent->n + 1 && currentParent->C[parentIndex] != present; parentIndex++);
		for (i = currentParent->n; i > parentIndex; i--)
		{
			currentParent->C[i + 1] = currentParent->C[i];
			currentParent->keys[i] = currentParent->keys[i - 1];
		}
		currentParent->n = currentParent->n + 1;
		currentParent->keys[parentIndex] = risingKey;

		currentParent->C[parentIndex + 1] = right;
		right->P = currentParent;
	}

	for (i = splitIndex + 1; i < present->n + 1; i++)
	{
		right->C[i - splitIndex - 1] = present->C[i];
		if (present->C[i] != NULL)
		{
			right->leaf = false;

			if (present->C[i] != NULL)
			{
				present->C[i]->P = right;
			}
			present->C[i] = NULL;
		}
	}

	for (i = splitIndex + 1; i < present->n; i++)
	{
		right->keys[i - splitIndex - 1] = present->keys[i];
	}
	left = present;
	left->n = splitIndex;

	if (present->P != NULL)
		return present->P;
	else
	{
		root = _createNode(present->leaf);
		root->keys[0] = risingKey;
		root->n = 1;
		root->C[0] = left;
		root->C[1] = right;
		left->P = root;
		right->P = root;
		root->leaf = false;
		return root;
	}
}


void removeElement(int k)
{
	if (!root)
	{
		printf("The tree is empty\n");
		return;
	}

	// Call the remove function for root
	_remove(root, k);

	// If the root node has 0 keys, make its first child as the new root
	//  if it has a child, otherwise set root as NULL
	if (root->n == 0)
	{
		BTreeNode *tmp = root;
		if (root->leaf)
		{
			root = NULL;
		}
		else
		{
			root = root->C[0];
			root->P = NULL;
		}

		// Free the old root
		free(tmp);
	}
	return;
}

void _remove(BTreeNode* present, int k)
{
	//-------------------------------------------------------------------------------------------------------
	//Write your code.
	for (int i = 0; i < present->n; i++)
	{
		if (k < present->keys[i])
		{
			_remove(present->C[i], k);
			return;
		}
		else if (k == present->keys[i])
		{
			if (present->leaf != true) {
				BTreeNode* max = present->C[i];
				while (max->leaf != true)
				{
					max = max->C[max->n];
				}
				present->keys[i] = max->keys[max->n - 1];
				max->n--;
				_balancingAfterDel(max);
			}
			else
			{
				for (int j = i + 1; j < present->n; j++)
				{
					present->keys[j - 1] = present->keys[j];
				}
				present->n--;
				_balancingAfterDel(present);
			}

			return;
		}
	}
	if (present->n > 0 && k > present->keys[present->n - 1])
		_remove(present->C[present->n], k);






	//-------------------------------------------------------------------------------------------------------
}

void _balancingAfterDel(BTreeNode* present) // repairAfterDelete
{
	int minKeys = (t + 2) / 2 - 1;
	BTreeNode* parent;
	BTreeNode* next;
	int parentIndex = 0;

	if (present->n < minKeys)
	{
		if (present->P == NULL)
		{
			if (present->n == 0)
			{
				root = present->C[0];
				if (root != NULL)
					root->P = NULL;
			}
		}
		else
		{
			parent = present->P;
			for (parentIndex = 0; parent->C[parentIndex] != present; parentIndex++);
			if (parentIndex > 0 && parent->C[parentIndex - 1]->n > minKeys)
			{
				_borrowFromLeft(present, parentIndex);

			}
			else if (parentIndex < parent->n && parent->C[parentIndex + 1]->n >minKeys)
			{
				_borrowFromRight(present, parentIndex);
			}
			else if (parentIndex == 0)
			{
				// Merge with right sibling
				next = _merge(present);
				_balancingAfterDel(next->P);
			}
			else
			{
				// Merge with left sibling
				next = _merge(parent->C[parentIndex - 1]);
				_balancingAfterDel(next->P);

			}

		}
	}
}


void _borrowFromRight(BTreeNode* present, int parentIdx)  ////////////
{
	int i;
	BTreeNode * rightSib;
	BTreeNode * parentNode = present->P;

	rightSib = parentNode->C[parentIdx + 1];
	present->n++;

	present->keys[present->n - 1] = parentNode->keys[parentIdx];
	parentNode->keys[parentIdx] = rightSib->keys[0];

	if (!present->leaf)
	{
		present->C[present->n] = rightSib->C[0];
		present->C[present->n]->P = present;

		for (i = 1; i < rightSib->n + 1; i++)
		{
			rightSib->C[i - 1] = rightSib->C[i];
		}

	}
	for (i = 1; i < rightSib->n; i++)
	{
		rightSib->keys[i - 1] = rightSib->keys[i];
	}
	rightSib->n--;
}


void _borrowFromLeft(BTreeNode* present, int parentIdx) /////////
{
	int i;
	BTreeNode * leftSib;
	BTreeNode * parentNode = present->P;
	present->n = present->n + 1;

	for (i = present->n - 1; i > 0; i--)
	{
		present->keys[i] = present->keys[i - 1];
	}
	leftSib = parentNode->C[parentIdx - 1];

	if (!present->leaf)
	{
		for (i = present->n; i > 0; i--)
		{
			present->C[i] = present->C[i - 1];
		}
		present->C[0] = leftSib->C[leftSib->n];
		leftSib->C[leftSib->n] = NULL;
		present->C[0]->P = present;
	}

	present->keys[0] = parentNode->keys[parentIdx - 1];
	parentNode->keys[parentIdx - 1] = leftSib->keys[leftSib->n - 1];

	leftSib->n = leftSib->n - 1;
}


BTreeNode* _merge(BTreeNode* present)  //////
{
	BTreeNode* parentNode = present->P;
	int parentIndex = 0;
	int fromParentIndex;
	int i;

	for (parentIndex = 0; parentNode->C[parentIndex] != present; parentIndex++);
	BTreeNode* rightSib = parentNode->C[parentIndex + 1];

	present->keys[present->n] = parentNode->keys[parentIndex];
	fromParentIndex = present->n;

	for (i = 0; i < rightSib->n; i++)
	{
		present->keys[present->n + 1 + i] = rightSib->keys[i];
	}
	if (!present->leaf)
	{
		for (i = 0; i <= rightSib->n; i++)
		{
			present->C[present->n + 1 + i] = rightSib->C[i];
			present->C[present->n + 1 + i]->P = present;
		}
	}

	for (i = parentIndex + 1; i < parentNode->n; i++)
	{
		parentNode->C[i] = parentNode->C[i + 1];
		parentNode->keys[i - 1] = parentNode->keys[i];
	}
	parentNode->n--;
	present->n = present->n + rightSib->n + 1;
	return present;
}


int _getLevel(BTreeNode* present)
{
	int i;
	int maxLevel = 0;
	int temp;
	if (present == NULL) return maxLevel;
	if (present->leaf == true)
		return maxLevel + 1;

	for (i = 0; i < present->n + 1; i++)
	{
		temp = _getLevel(present->C[i]);

		if (temp > maxLevel)
			maxLevel = temp;
	}

	return maxLevel + 1;
}

void _getNumberOfNodes(BTreeNode* present, int* numNodes, int level)
{
	int i;
	if (present == NULL) return;

	if (present->leaf == false)
	{
		for (i = 0; i < present->n + 1; i++)
			_getNumberOfNodes(present->C[i], numNodes, level + 1);
	}
	numNodes[level] += 1;
}

void _mappingNodes(BTreeNode* present, BTreeNode ***nodePtr, int* numNodes, int level)
{
	int i;
	if (present == NULL) return;

	if (present->leaf == false)
	{
		for (i = 0; i < present->n + 1; i++)
			_mappingNodes(present->C[i], nodePtr, numNodes, level + 1);
	}

	nodePtr[level][numNodes[level]] = present;
	numNodes[level] += 1;
}


void printTree()
{
	int level;
	int *numNodes;
	int i, j, k;

	level = _getLevel(root);
	numNodes = (int *)malloc(sizeof(int) * (level));
	memset(numNodes, 0, level * sizeof(int));

	_getNumberOfNodes(root, numNodes, 0);

	BTreeNode ***nodePtr;
	nodePtr = (BTreeNode***)malloc(sizeof(BTreeNode**) * level);
	for (i = 0; i < level; i++) {
		nodePtr[i] = (BTreeNode**)malloc(sizeof(BTreeNode*) * numNodes[i]);
	}

	memset(numNodes, 0, level * sizeof(int));
	_mappingNodes(root, nodePtr, numNodes, 0);

	for (i = 0; i < level; i++) {
		for (j = 0; j < numNodes[i]; j++) {
			cout << "[";
			for (k = 0; k < nodePtr[i][j]->n; k++)
				cout << nodePtr[i][j]->keys[k] << " ";
			cout << "] ";
		}
		cout << endl;
	}

	for (i = 0; i < level; i++) {
		free(nodePtr[i]);
	}
	free(nodePtr);
}

int main(void) {
	BTreeInit(3); // Max degree 3
	insertElement(1);
	insertElement(2);
	insertElement(3);
	insertElement(4);
	insertElement(5);
	insertElement(6);
	insertElement(7);
	insertElement(8);
	insertElement(9);
	insertElement(10);
	insertElement(11);
	insertElement(12);
	insertElement(13);
	insertElement(14);
	insertElement(15);
	insertElement(16);
	insertElement(17);
	insertElement(18);
	insertElement(19);
	insertElement(20);
	removeElement(14);
	printTree();
	removeElement(19);
	printTree();


	BTreeInit(4); // Max degree 4
	insertElement(1); insertElement(3); insertElement(7); insertElement(10); insertElement(11); insertElement(13);	insertElement(14);
	insertElement(15); insertElement(18); insertElement(16); insertElement(19); insertElement(24); insertElement(25); insertElement(26);
	removeElement(13);
	printTree();

	return 0;
}

