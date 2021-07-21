#include<bits/stdc++.h>
using namespace std;


class Node{
	public:
	int data;
	Node * next;
	
};

void build(Node *&head, int d){
	
	//Create a newNode;
	Node * newNode = new Node();
	
	// point newNode to head
	newNode -> next = head;
	
	// now head will become you newly created Node;
	head = newNode;
	
	
	// put the data into newNode;
	newNode -> data = d;
}

int Length(Node * head){                       // count the length of Linked list;
	int count = 0;
	while(head != NULL){
		count++;
		head = head -> next;	
	}	
	return count;
}

void RemoveNthNode(Node *& head, int k){                           // Remove Nth Node from the End.
	int n = Length(head);	
	int x = n - k + 1;                                               // calculating the node from end;
	int  jump = 1;
	
	
	cout << x << endl;
	Node * temp = head;
	while(jump < x -1){
		jump++;
		temp = temp -> next;
	}
	
	
	Node * temp2 = temp -> next;
	temp -> next = temp2 -> next;
	free(temp2);
}

void Display(Node * head){                                             // Display the linked list ( linked list traversal);
	
	
	while(head != NULL){
		cout << head -> data << "->";
		head = head -> next;
	}	
	cout << endl;
}

int main(){
	Node * head = NULL;
	
	
	int a[5] = {5, 4, 3, 2, 1};                                         // Array to linked list;
	for(int i=0;i<5;i++){
		build(head, a[i]);
	}
	
	
	Display(head);	
	int k;
	cin>>k;
	
	RemoveNthNode(head, k);
	
	Display(head);
}
