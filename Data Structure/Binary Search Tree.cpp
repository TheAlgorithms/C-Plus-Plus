#include<iostream>
using namespace std;

//*****************************************************************************************************

template <typename T>
struct Node
{
	T val;
	Node <T> * left;
	Node <T> * right;
	Node();
	Node(const T & dataIn, Node <T> * l = nullptr, Node <T> * r = nullptr);
};

template <typename T>
Node <T> :: Node()
{
	val = 0;
	left = nullptr;
	right = nullptr;
}

template <typename T>
Node <T> :: Node(const T & dataIn, Node <T> * l, Node <T> * r)
{
	val = dataIn;
	left = l;
	right = r;
}

//*****************************************************************************************************

template <typename T>
class BST
{
private:
		Node <T> * root;
		void _destruct(Node <T> * pRoot);
		Node <T> * _retrieve(Node <T> * pRoot, const T & dataOut)	const;
		Node <T> * _insert(Node <T> * pRoot, const T & dataOut)	const;
		Node <T> * _remove(Node <T> * pRoot, const T & dataOut)	const;
		void _findMaxInLeftST(Node <T> * pRoot, T & pMax) const;
		void _preOrder(Node <T> * pRoot)	const;
		void _inOrder(Node <T> * pRoot)	const;
		void _postOrder(Node <T> * pRoot)	const;
public:
	BST();
	~BST();
	bool retrieve(T & dataOut)	const;
	bool insert(const T & dataIn);
	bool remove (T & dataOut);
	T findMaxInLeftST() const;
	void preOrder()	const;
	void inOrder()	const;
	void postOrder()	const;
};

template <typename T>
BST <T> :: BST ()
{
	root = nullptr;
}

template <typename T>
BST <T> :: ~BST()
{
	_destruct(root);
}

template <typename T>
void BST <T> ::_destruct(Node <T> * pRoot)
{
	if (pRoot)
	{
		_destruct(pRoot->left);
		_destruct(pRoot->right);
		delete pRoot;
	}
}

template <typename T>
bool BST <T> ::retrieve(T & dataOut)	const
{
	bool success = false;
	Node <T> * pFound;

	pFound = _retrieve(root, dataOut);

	if (pFound)
	{
		dataOut = pFound->val;
		success = true;
	}

	return success;
}

template <typename T>
Node <T> * BST <T> ::_retrieve(Node <T> * pRoot, const T & dataOut)	const
{
	if (pRoot)
	{
		if (pRoot->val > dataOut)
			pRoot = _retrieve(pRoot->left, dataOut);
		else if (pRoot->val < dataOut)
			pRoot = _retrieve(pRoot->right, dataOut);
	}

	return pRoot;
}

template <typename T>
bool BST <T> :: insert(const T & dataIn)
{
	bool success = false;
	Node <T> * pFound;

	pFound = _retrieve(root, dataIn);

	if (!pFound)
	{
		root = _insert(root, dataIn);
		success = true;
	}

	return success;
}

template <typename T>
Node <T> * BST <T> ::_insert(Node <T> * pRoot, const T & dataIn)	const
{
	if (pRoot)
	{
		if (pRoot->val > dataIn)
			pRoot->left = _insert(pRoot->left, dataIn);
		else
			pRoot->right = _insert(pRoot->right, dataIn);
	}
	else
		pRoot = new (nothrow) Node <T>(dataIn);

	return pRoot;
}

template <typename T>
bool BST <T> :: remove(T & dataOut)
{
	bool success = false;
	Node <T> * pFound;

	pFound = _retrieve(root, dataOut);

	if (pFound)
	{
		dataOut = pFound->val;
		root = _remove(root, dataOut);
		success = true;
	}

	return success;
}

template <typename T>
Node <T> * BST <T> ::_remove(Node <T> * pRoot, const T & dataOut)	const
{
	Node <T> * pMax;
	Node <T> * pDel;

	if (pRoot)
	{
		if (pRoot->val > dataOut)
			pRoot->left = _remove(pRoot->left, dataOut);
		else if (pRoot->val < dataOut)
			pRoot->right = _remove(pRoot->right, dataOut);
		else
		{
			if ((pRoot->left) && (pRoot->right))
			{
				pMax = pRoot->left;

				while ((pMax) && (pMax->right))
					pMax = pMax->right;

				pRoot->val = pMax->val;
				pRoot->left = _remove(pRoot->left, pMax->val);
			}
			else
			{
				pDel = pRoot;

				if (pRoot->left)
					pRoot = pRoot->left;
				else
					pRoot = pRoot->right;

				delete pDel;
			}
		}
	}

	return pRoot;
}

template <typename T>
T BST <T>::findMaxInLeftST()	const
{
	T max = root->val;

	_findMaxInLeftST(root->left, max);

	return max;
}

template <typename T>
void BST <T>::_findMaxInLeftST(Node <T> * pRoot, T & pMax)	const
{
	if (pRoot)
	{
		if (pRoot->right)
		{
			_findMaxInLeftST(pRoot->right, pMax);
		}
		else
			pMax = pRoot->val;
	}
}

template <typename T>
void BST <T> ::preOrder()	const
{
	_preOrder(root);
	cout << "\n";
}

template <typename T>
void BST <T>:: _preOrder(Node <T> * pRoot)	const
{
	if (pRoot)
	{
		cout << pRoot->val<< "  ";
		_preOrder(pRoot->left);
		_preOrder(pRoot->right);
	}
}

template <typename T>
void BST <T> ::inOrder()	const
{
	_inOrder(root);
	cout << "\n";
}

template <typename T>
void BST <T> :: _inOrder(Node <T> * pRoot)	const
{
	if (pRoot)
	{
		_inOrder(pRoot->left);
		cout << pRoot->val << "  ";
		_inOrder(pRoot->right);
	}
}

template <typename T>
void BST <T> ::postOrder()	const
{
	_postOrder(root);
	cout << "\n";
}

template <typename T>
void BST <T> :: _postOrder(Node <T> * pRoot)	const
{
	if (pRoot)
	{
		_postOrder(pRoot->left);
		_postOrder(pRoot->right);
		cout << pRoot->val<< "  ";
	}
}

//*****************************************************************************************************

int main()
{
	BST <int> tree;
	int value;
	int choice;

	cout<<"Enter the value of root node : ";
	cin >> value;

	if (!tree.insert(value))
		cout << "Could not insert value \n";

	do
	{
		cout << "\n1. Insert";
		cout << "\n2. Delete";
		cout << "\n3. Retrieve";
		cout << "\n4. Display Max Left Subtree";
		cout << "\n5. Display Preorder Depth First";
		cout << "\n6. Display Inorder Depth First";
		cout << "\n7. Display Postorder Depth First";
		cout << "\n\n0. Quit \n";

		cout << "\nEnter Your Choice : ";
		cin >> choice;

		switch(choice)
		{
			case 1:
				cout<<"\nEnter the value to be Inserted : ";
				cin >> value;
				if (!tree.insert(value))
					cout << "Could not insert value! \n";
				break;
			case 2:
				cout<<"\nEnter the value to be Deleted : ";
				cin >> value;
				if (!tree.remove(value))
					cout << "Could not remove value! \n";
				break;
			case 3:
				cout << "\nEnter the value to be retrieved : ";
				cin >> value;
				if (!tree.retrieve(value))
					cout << "Value could not be retrieved! \n";
				else
				{
					cout << "Value found! \n";
					cout << "Value: " << value << "\n";
				}
				break;
			case 4:
				value = tree.findMaxInLeftST();
				cout << "Max value in left subtree: " << value << "\n";
				break;
			case 5:
				tree.preOrder();
				break;
			case 6:
				tree.inOrder();
				break;
			case 7:
				tree.postOrder();
				break;
		}
	}
	while(choice != 0);

	return 0;
}