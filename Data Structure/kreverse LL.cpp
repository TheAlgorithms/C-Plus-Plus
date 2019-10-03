#include<iostream>
#include<conio.h>
using namespace std;

class node{             //creating a class for linked list implementation
	public:
		int data;
		node *next;
	node(int d){
		data=d;
		next=NULL;
	}
};
	
	void insertatbeg(node *&head,int data){  //function to insert a node at beginning of the linked list
		node *n=new node(data);
		n->next=head;
		head=n;
	}
	
	void print(node *head){  //function to print the linked list
		while(head!=NULL){
			cout<<head->data<<" ";
			head=head->next;
		}
	}
	
	node *kreverse(node *&head,int k){  //funtion to reverse the linked list in groups of "k"
		node *c=head;
		node *p=NULL;
		node *n=NULL;
		int count=0;
		while(c!=NULL&&count<k){
			n=c->next;
			c->next=p;
			p=c;
			c=n;
			count++;
		}
		if (n != NULL){
			head->next = kreverse(n, k);
		}
		return p;  
}


int main(){
	node *head=NULL;  //you can give various test cases at run time
	int n,k;
	cin>>n;
	cin>>k;
	int arr[200];
	int i=0;
	while(i<n){
		cin>>arr[i];
		i++;
	}
	int j=n-1;
	while(j>=0){
		insertatbeg(head,arr[j]);
		j--;
	}
	head=kreverse(head,k);
	print(head);
	
	
	return 0;
}
