#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct node
{
	int data;
	struct node *npx;
};

class XORLinkedlist
{
	struct node *m_headNode;
	
public:
	XORLinkedlist();
	~XORLinkedlist();
	void Createlist();
	void forwardTraverse();
	void backwordTraverse();

private:
	node* createNode();
	node* XOR(node *a, node *b);


};