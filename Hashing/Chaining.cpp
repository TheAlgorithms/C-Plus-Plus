#include<iostream>
#include<math.h>
using namespace std;
struct node{
	int data;
	struct node *next;
} *head[100],*curr;

void init(){
	for(int i=0;i<100;i++)
		head[i]=NULL;
}

void add(int x,int h){
	struct node *temp = new node;
	temp->data = x;
	temp->next = NULL;
	if(head[h]==NULL){
		head[h] = temp;
		curr=head[h];
	}
	else{
		curr=head[h];
		while(curr->next!=NULL)
			curr=curr->next;
		curr->next = temp;
	}
}

void display(int mod){
	struct node *temp;
	int i;
	for(i=0;i<mod;i++){
		if(head[i]==NULL){
			cout<<"Key = "<<i<<" is empty"<<endl;
		}
		else{
			cout<<"Key = "<<i<<" Value = ";
			temp = head[i];
			while(temp->next!=NULL){
				cout<<temp->data<<" ";
				temp=temp->next;
			}
			cout<<temp->data;
			cout<<endl;
		}
	}
}

int hash(int x,int mod){
	return x%mod;
}

void find(int x,int h){
	struct node *temp =head[h];
	if(head[h]==NULL){
		cout<<"Element not found";
		return;
	}
	while(1){
		if(temp->data==x)
			break;
		else if(temp->next==NULL)
			break;
		temp=temp->next;
	}
	if(temp->next!=NULL)
		cout<<"Element found";
	else{
		if(temp->data==x)
			cout<<"Element found";
		else
			cout<<"Element not found";
	}
}	

int main(void){
	init();
	int c,x,mod;
	cout<<"Enter the size of Hash Table. = ";
	cin>>mod;
	while(1){
		cout<<endl;
		cout<<"PLEASE CHOOSE -"<<endl;
		cout<<"1. Add element."<<endl;
		cout<<"2. Find element."<<endl;
		cout<<"3. Generate Hash."<<endl;
		cout<<"4. Display Hash table."<<endl;
		cout<<"5. Exit."<<endl;
		cin>>c;
		switch(c){
			case 1:{
				cout<<"Enter element to add = ";
				cin>>x;
				int h = hash(x,mod);
				if(h<0)
					h=fabs(h);
				add(x,h);
				break;
			}
			case 2:{
				cout<<"Enter element to search = ";
				cin>>x;
				int h=hash(x,mod);
				find(x,h);
				break;
			}
			case 3:{
				cout<<"Enter element to generate hash = ";
				cin>>x;
				cout<<"Hash of "<<x<<" is = "<<hash(x,mod);
				break;
			}
			case 4:{
				display(mod);
			}
			default:{
				break;
			}
		}
		if(c>4)
			break;
		cout<<endl;
	}
	/*add(1,&head1);
	add(2,&head1);
	add(3,&head2);
	add(5,&head1);
	display(&head1);
	display(&head2);*/
	return 0;
}