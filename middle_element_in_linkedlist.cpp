#include <iostream>
using namespace std;
struct node{
	long long int data;
	struct node *next;
};

node* create(int size){
	struct node *start,*temp,*end,*p;
	p=new node;
	temp=start=p;
	cin>>p->data;
	for(int i=1;i<size;i++){
		p=new node;
		temp->next=p;
		cin>>p->data;
		p->next= NULL;
		temp=p;
	}
	end=temp;
	return start;
}
node *midd(node *start){
	node *ptr,*ptr2;
	ptr=ptr2=start;
	if(ptr2->next!=NULL)ptr2=ptr2->next;
	while(ptr2->next!=NULL){
		ptr=ptr->next;
		ptr2=ptr2->next;
		if(ptr2->next!=NULL)ptr2=ptr2->next;
	}
	return ptr;
}
void display(node *start){
	node *p,*ptr;
	ptr=p=start;
	cout<<ptr->data<<" ";
	while(ptr->next!=NULL){
		ptr=ptr->next;
		cout<<ptr->data<<" ";
	}
}
int main()
{
    node *p,*x;
    long long int t;
    cin>>t;
    p=create(t);
    x=midd(p);
    cout<<x->data;
    return 0;
}


