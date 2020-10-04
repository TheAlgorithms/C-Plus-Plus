#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;


#define ff                first
#define ss                second
#define int               long long
#define pb                push_back
#define mp                make_pair
#define pii               pair<int,int>
#define vi                vector<int>
#define mii               map<int,int>
#define pqb               priority_queue<int>
#define pqs               priority_queue<int,vi,greater<int> >
#define setbits(x)        __builtin_popcountll(x)
#define zrobits(x)        __builtin_ctzll(x)
#define mod               1000000007   //10^9 + 7
#define inf               1e18
#define ps(x,y)           fixed<<setprecision(y)<<x
#define mk(arr,n,type)    type*arr = new type[n]
#define w(x)              int x;cin>>x;while(x--)
#define rep(i,n)          for(int i=0;i<(n);++i)
#define repA(i,a,n)       for(int i=a;i<=(n);++i)
#define repD(i,a,n)       for(int i=a;i>=(n);--i)
#define itr(type,it,x)    for(type it = x.begin();it!=x.end();it++)
#define endl              "\n"
mt19937                  rng(chrono::steady_clock::now().time_since_epoch().count());  // to shuffle an array randomly viz. shuffle(arr,arr+n,rng)

typedef tree<int , null_type , less<int> , rb_tree_tag, tree_order_statistics_node_update> pbds;  //policy based data structure


void c_p_c() {

	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

}

class node {
public:
	int data;
	node* next;

// constructor
	node(int d) {
		data = d;
		next = NULL;
	}

};

// We can have a linked list class seperately but we will prefer the node functional approach

/*
class LinkedList{

	node*head;
	node*tail;
public:
	LinkedList(){

	}

	void insert(){

	}

};
*/

int length(node*head) {
	int len = 0;
	while (head != NULL) {
		head = head->next ;
		len += 1;
	}
	return len;
}

void insertAtHead(node*&head, int data) {
	node*n = new node(data);
	n->next = head;
	head = n;
}

// Insert at the tail of the linked list
void insertAtTail(node*&head, int data) {

	if (head == NULL) {
		head = new node(data);
		return;
	}
	node*tail = head;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = new node(data);
	return;
}

// insert at a specified position in the linked list
void insertInMiddle(node*&head, int data, int p) {

	if (head == NULL || p == 0) {
		insertAtHead(head, data);
	}
	else if (p > length(head)) {
		insertAtTail(head, data);
	}
	else {
		// Insert in the middle
		//take p-1 jumps
		int jump = 1;
		node*temp = head;
		while (jump <= p - 1) {
			temp = temp->next;
			jump++;
		}

		node*n = new node(data);
		n->next = temp->next;
		temp->next = n;

	}

	return;
}

// Delete at the head of a linked list
void deleteAtHead(node*&head) {
	if (head == NULL) {
		// LL is empty
		return;
	}
	node*temp = head;
	head = head->next;
	delete temp;
	return;
}

// delete at the tail of a linked list
void deleteAtTail(node*&head) {
	node*prev = NULL;
	node*temp = head;
	while (temp->next != NULL) {
		prev = temp;  //to make prev always one step back of temp
		temp = temp->next;
	}
	delete temp;
	prev->next = NULL;
	return;
}

// delete at a specified position in the linked list
void deleteInMiddle(node*&head, int p) {
	if (head == NULL || p == 0) {
		deleteAtHead(head);
		return;
	}
	else if (p >= length(head) - 1) {
		deleteAtTail(head);
		return;
	}
	else {
		// delete in the middle
		node*prev = NULL;
		node*temp = head;
		int jump = 1;
		// p-1 jumps
		while (jump <= p) {
			prev = temp;
			temp = temp->next;
			jump++;
		}

		prev->next = temp->next;
		delete temp;
		return;

	}
}

// Search a particular element recursively in a linked list
bool searchRecursive(node*head, int key) {

	if (head == NULL) {
		return false;
	}

	// Recursive Case
	if (head->data == key) {
		return true;
	}
	else {
		return searchRecursive(head->next, key);
	}
}

// Search a particular element iteratively in a linked list
bool searchIterative(node*head, int key) {

	while (head != NULL) {
		if (head->data == key) {
			return true;
		}
		head = head->next;
	}
	return false;
}

// Reverse a linked list iteratively
void reverseIterative(node*&head) {
	node*C = head;
	node*P = NULL;
	node*N;

	while (C != NULL) {
		// Save the next node
		N = C->next;
		// Make the current node point to previous
		C->next = P;
		// Just update the previous and current
		P = C;
		C = N;
	}
	head = P;
}

// Reverse a linked list recursively
node* reverseRecursive(node*head) {

	if (head == NULL || head->next == NULL) {
		return head;
	}
	// Recursive Case
	node*smallHead = reverseRecursive(head->next);
	node*C = head;
	C->next->next = C;
	C->next = NULL;
	return smallHead;

}

// Print the linked list
void print(node*head) {   //we are passing head by value so changes made to head will not be reflected in main
	//node*temp = head;
	while (head != NULL) {
		cout << head->data << " -> ";
		head = head->next;
	}
	return;
}

// Take input of the linked list elements
void buildList(node*&head, int n) {
	int i = 0;
	while (i < n) {
		int data;
		cin >> data;
		insertAtTail(head, data);
		i++;
	}
}

// Overloaded ">>" operator for convenient input of linked list
istream& operator>>(istream & is, node*&head) {
	int n; cin >> n;
	buildList(head, n);
	return is;
}

// Overloaded "<<" operator for convenient output of linked list
ostream& operator<<(ostream & os, node * head) {
	print(head);
	return os;
}

// Merge the two sorted parts recursively
node*  merge(node*a, node*b) {

	// Base Case
	if (a == NULL) {
		return b;
	}
	else if (b == NULL) {
		return a;
	}

	// Recursive Case
	node*c;
	// Compare a and b for smaller element
	if (a->data < b->data) {
		c = a;
		c->next = merge(a->next, b);
	}
	else {
		c = b;
		c->next = merge(a, b->next);
	}
	return c;
}



int32_t main() {

	c_p_c();

	node*head = NULL;
	node*head2 = NULL;

	cin >> head >> head2;
	cout << head << endl << head2 << endl;

	node*merged = merge(head, head2);
	cout << merged << endl;

	return 0;
}

