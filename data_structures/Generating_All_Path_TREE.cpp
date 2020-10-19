/*
	It will print all the paths from root to leafs
	Input format :
	dot (.) represents NULL node and Input is taking in preorder format

	      A
	    /   \
	   B     C
	  / \   / \
	 D   E F   G

	 Input will be A B D . . E . . C F . . G . .
	 Output :
	 A B D
	 A B E
	 A C F
	 A C G
*/

#include<bits/stdc++.h>

using namespace std;

typedef struct btnode{
	btnode *lc;
	char data;
	btnode *rc;
}*btptr;

void insert(btptr &T,char n)
{
	if(T==NULL)
	{
		T = new btnode;
		T->data = n;
		T->lc = NULL;
		T->rc = NULL;
	}
	char ch;
	cin>>ch;
	if(ch!='.')
		insert(T->lc,ch);
	cin>>ch;
	if(ch!='.')	
		insert(T->rc,ch);
	else return;
}

void printPath(btptr T,vector<char> &v)
{
	if(T->lc==NULL && T->rc==NULL)
	{
		v.push_back(T->data);
		for(int i=0;i<v.size();i++)
			cout<<v[i]<<" ";
		v.pop_back();
		cout<<"\n";
		return;
	}
	v.push_back(T->data);
	printPath(T->lc,v);
	printPath(T->rc,v);
	v.pop_back();
}

int main()
{
	btptr T = NULL;
	char ch;
	cin>>ch;
	vector<char> v;
	insert(T,ch);
	printPath(T,v);
}