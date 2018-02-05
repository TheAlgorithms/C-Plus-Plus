#include<iostream>
using namespace std;
struct node{
	long long int data;
	struct node *next;
};

node* create(int size){
	struct node *start,*temp,*end,*p;
	p=new node;
	temp=start=p;
	long long int x;
	cin>>x;
	p->data=x;
	for(int i=1;i<size;i++){
		p=new node;
		temp->next=p;
		cin>>x;
		p->data=x;
		p->next= NULL;
		temp=p;
	}
	end=temp;
	return start;
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

int inter(node *p,node *s,int n,int m){
	int t=n+m;
	int flag=1;
	long long int x=-10000000001;
	while(t--){
		if(p==NULL){
			if(flag)
			cout<<"-1";
			return -1;
		}
		else if(s==NULL){
			if(flag)
			cout<<"-1 ";
			return -1;
		}
		else if(s->data==p->data){
			if(x!=s->data){
				cout<<s->data<<" ";
				flag=0;
				x=s->data;
			}
			s=s->next;
			p=p->next;
			t--;
		}
		else if(s->data<p->data){
			s=s->next;
		}
		else {
			p=p->next;
		}
	}
	return -1;
}
int main()
{
    int n,m;
    node *p,*s;
    cin>>n;
	p=create(n);
    cin>>m;
	s=create(m);
	inter(p,s,n,m);
    return 0;
}

