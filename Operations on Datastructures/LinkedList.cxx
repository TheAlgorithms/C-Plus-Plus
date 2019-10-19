/*
* Data Structures
* Made by Gurpreet Singh
*/


#include <iostream>
using namespace std;

struct Node{
public:
	int data;
	Node* next;
};

class LinkedList
{
private:
	Node *head,*tail;
public:
	LinkedList(){
		head=NULL;
		tail=NULL;
	}
	Node *getHead(){
		return head;
	}
	int getSize(){
		int count=0;
		for(Node *n=head;n!=NULL;n=n->next)
			count++;

		return count;
	}
	void display(Node *n){
		cout<<"Linked List :\t";
		while(n!=NULL){
			cout<<n->data<<"\t";
			n=n->next;
		}
		cout<<"\n";
	}
	void addNodeAtEnd(int element){
		Node *temp=new Node;
		temp->data=element;
		temp->next=NULL;
		if(head==NULL){
			head=temp;
			tail=temp;
		}
		else{
			tail->next=temp;
			tail=tail->next;
		}
	}
	void addNodeAtFront(int element){
		Node *temp=new Node;
		temp->data=element;
		if(head==NULL){
			temp->next=NULL;
			head=temp;
			tail=temp;
		}
		else{
			temp->next=head;
			head=temp;
		}
	}
	void addNodeAtAnyPosition(int element,int position){
		if(position>LinkedList::getSize()||position<=0)
			cout<<"Size Not Possible\n";
		else{
			Node *temp=new Node;
			temp->data=element;

			Node *n = head;
        		while (--position>0){
            		n=n->next;
        		}
        	temp->next=n->next;
        	n->next=temp;
    	}
	}
	void deleteNodeAtHead(){
		if(head->next==NULL){
			cout<<"List cannot be empty. It only contains one element";
			return;
		}
		Node *n=head;
		n=n->next;
		delete head;
		head=n;
	}
	void deleteNodeAtTail(){
		if(head->next==NULL){
			cout<<"List cannot be empty. It only contains one element";
			return;
		}
		Node *n=head;
		Node *temp;
		while(n->next!=NULL){
			temp=n;
			n=n->next;
		}
		delete n;
		temp->next=NULL;
		tail=temp;
	}
	void deleteNodeAtPosition(int position){
		if(head->next==NULL){
			cout<<"List cannot be empty. It only contains one element";
			return;
		}
		if(position>LinkedList::getSize()||position<0)
			cout<<"Size Not Possible\n";
		else{
			Node *n=head;
			while(position-1>0){
				n=n->next;
				position--;
			}
			n->next=n->next->next;
			delete n;
		}
	}
	void searchAnElement(int element){
		bool tf=false;
		for(Node *n=head;n!=NULL;n=n->next){
			if(n->data==element) tf=true;
		}
		tf==true?cout<<"Element Found\n":cout<<"Element not Found\n";
	}
	void reverseDisplay(Node *n){
		if(n==NULL)
			return;
		else{
			reverseDisplay(n->next);
			cout<<n->data<<"\t";
		}
	}
};
int main()
{
	cout<<"Enter the number of nodes you want to create\n";
	int size;cin>>size;

	cout<<"Enter the elements of Node\n";
	LinkedList list;
	int element;int position;
	for(int i=0;i<size;i++){
		cin>>element;
		list.addNodeAtEnd(element);
	}

	list.display(list.getHead());

	cout<<"Enter element to be inserted at front\n";
	cin>>element;
	list.addNodeAtFront(element);
	list.display(list.getHead());

	cout<<"Enter element to be inserted at end\n";
	cin>>element;
	list.addNodeAtEnd(element);
	list.display(list.getHead());

	cout<<"Enter element and its position\n";
	cin>>element;
	cin>>position;
	list.addNodeAtAnyPosition(element,position);
	list.display(list.getHead());

	cout<<"Deleting node at head\n";
	list.deleteNodeAtHead();
	list.display(list.getHead()	);

	cout<<"Deleting node at tail\n";
	list.deleteNodeAtTail();
	list.display(list.getHead()	);

 	cout<<"Enter the element position to be deleted\n";
	cin>>position;
	list.deleteNodeAtPosition(position);
	list.display(list.getHead());

	cout<<"Enter the element to be searched\n";
	cin>>element;
	list.searchAnElement(element);

	cout<<"Reverse display of linked list\n";
	list.reverseDisplay(list.getHead());

	return 0;
}
