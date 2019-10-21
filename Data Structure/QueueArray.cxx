#include <iostream>
using namespace std;

struct Node{
public:
	int data;
	Node* next;
};

class QueueLinkedList
{
private:
	Node *head,*tail;
public:
	QueueLinkedList(){
		head=NULL;
		tail=NULL;
	}
	Node *getHead(){
		return head;
	}
	void Queue(int element){
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
	void Dequeue(){
		if(head->next==NULL){
			head=NULL;
			cout<<"List is empty.";
			return;
		}
		Node *n=head;
		cout<<"deleted node is "<<n->data<<endl;
		n=n->next;

		delete head;
		head=n;
	}
	void peekQueue(){
		cout<<head->data<<endl;
	}
	void peekDequeue(){
		cout<<tail->data<<endl;
	}
};
int main()
{
	cout<<"Enter the number of nodes you want to create\n";
	int size;cin>>size;

	cout<<"Enter the elements of Queue\n";
	QueueLinkedList list;
	int element;int position;
	for(int i=0;i<size;i++){
		cin>>element;
		list.Queue(element);
	}
	list.Dequeue();

	cout<<"First element of Queue is ";list.peekQueue();
	cout<<"Last element of Queue is ";list.peekDequeue();

	return 0;
}
