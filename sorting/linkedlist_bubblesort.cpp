/* 
what is BubbleSort?
Bubble sort is a simple sorting algorithm. This sorting algorithm is comparison-based algorithm in which each pair of adjacent elements 
is compared and the elements are swapped if they are not in order. This algorithm is not suitable for large data sets as its average and worst case complexity 
are of Ο(n2) where n is the number of items.
*/

/*  
what is linked list? 
A linked list is a linear data structure that stores a collection of data elements dynamically.
Nodes represent those data elements, and links or pointers connect each node.
Each node consists of two fields, the information stored in a linked list and a pointer that stores the address of its next node.
The last node contains null in its second field because it will point to no node.
A linked list can grow and shrink its size, as per the requirement.
It does not waste memory space.
*/

#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node* next;
} Node;

struct Node* swap(struct Node* ptr1, struct Node* ptr2)
{
	struct Node* tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return ptr2;
}

int bubbleSort(struct Node** head, int count)
{
	struct Node** h;
	int i, j, swapped;

	for (i = 0; i <= count; i++)
	{

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++)
		{

			struct Node* p1 = *h;
			struct Node* p2 = p1->next;

			if (p1->data > p2->data)
			{
				*h = swap(p1, p2);
				swapped = 1;
			}

			h = &(*h)->next;
		}

		if (swapped == 0)
			break;
	}
}

void print_list(struct Node* n)
{
	while (n != NULL)
	{
		cout << n->data << " -> ";
		n = n->next;
	}
	cout << endl;
}

void insert_at_the_front(struct Node** start_ref, int data)
{
	struct Node* ptr1 = (struct Node*)malloc(sizeof(struct Node));
	ptr1->data = data;
	ptr1->next = *start_ref;
	*start_ref = ptr1;
}

int main()
{
	int arr[] = { 60, 95, 33, 35, 103, 22 };
	int listsize, i;
	struct Node* start = NULL;
	listsize = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < listsize; i++)
	{
        insert_at_the_front(&start, arr[i]);
    }
	cout <<"Linked list before sorting the elements: \n";
	print_list(start);
	bubbleSort(&start, listsize);
	cout <<"Linked list after sorting the elements: \n";
	print_list(start);
	return 0;
}

