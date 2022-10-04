#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node {
	int val;
	struct Node* next;
	Node(int x)
	{
		val = x;
		next = NULL;
	}
};


class Linked_list {

public:
	Node* head;
	Node* sorted;

	void push(int val)
	{
		Node* newnode = new Node(val);
		newnode->next = head;
		head = newnode;
	}

	void sort(Node* headref)
	{
		sorted = NULL;
		Node* current = headref;
		while (current != NULL) {
			Node* next = current->next;
			InsertedSort(current);
			current = next;
		}
		head = sorted;
	}


	void InsertedSort(Node* newnode)
	{
		if (sorted == NULL || sorted->val >= newnode->val) {
			newnode->next = sorted;
			sorted = newnode;
		}
		else {
			Node* current = sorted;
			while (current->next != NULL
				&& current->next->val < newnode->val) {
				current = current->next;
			}
			newnode->next = current->next;
			current->next = newnode;
		}
	}
	void Display(Node* head)
	{
		while (head != NULL) {
			cout << head->val << " ";
			head = head->next;
		}
	}
};


int main(void)
{
	Linked_list list;
	list.head = NULL;
	list.push(12);
	list.push(18);
	list.push(1);
	list.push(98);
	list.push(2);
	cout << "Before sorting" << endl;
	list.Display(list.head);
	cout << endl;
	list.sort(list.head);
	cout << "After sorting" << endl;
	list.Display(list.head);
}
