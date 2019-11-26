#include "XORLinkedlist.h"

XORLinkedlist::XORLinkedlist()
{
	m_headNode = nullptr;
	cout << "Constructor called " << endl;
}

XORLinkedlist::~XORLinkedlist()
{
	cout << "Destructor called " << endl;
}

void XORLinkedlist::Createlist()
{
	int NoOfNodes;
	int NodeInfo;
	struct node* newNode;
	struct node* auxNode;
	cout << "Enter number of nodes to be created in linked list" << endl;
	cin >> NoOfNodes;

	for (int indx = 0; indx < NoOfNodes; indx++)
	{
		cout << "Enter nodeInfo" << endl;
		cin >> NodeInfo;
		
		newNode = createNode();
		newNode->data = NodeInfo;
		
		newNode->npx = XOR(m_headNode, nullptr);

		if (m_headNode)
		{
			m_headNode->npx = XOR(newNode, XOR(m_headNode->npx, nullptr));
		}
		
		m_headNode = newNode;

		cout << "Node inserted " << endl;
	}

}

void XORLinkedlist::forwardTraverse()
{
	node *curr;
	node *prev = nullptr;
	node *next;
	curr = m_headNode;

	while (curr != nullptr)
	{
		cout << "data: " << curr->data << endl;
		next = XOR(prev, curr->npx);

		prev = curr;
		curr = next;
		

	}
	
}


void XORLinkedlist::backwordTraverse()
{

}

node* XORLinkedlist::XOR(node *a, node *b)
{
	return (node *)((uintptr_t)a ^ (uintptr_t)b);
}

node * XORLinkedlist::createNode()
{
	struct node* n = nullptr;
	n = new struct node;
	//n->npx = nullptr;

	return n;
}

