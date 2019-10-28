#include<iostream>

using namespace std;

struct person
{
	int data;
	person *next;
};

class group
{
	private:
		person *ref;
		int numb;
	public:
		group()
		{
			ref = nullptr;
			numb = 0;
		}
		~group()
		{
			delete ref;
		}
		void insert(int);
		void sike();
};

void group::insert(int tot)
{
	numb = tot;
	int vals=1;
	if(tot<1)
		return;
	person *temp, *vamp;
	ref = new person;
	ref->data = vals;
	ref->next = ref;
	temp = ref;
	while(--tot)
	{
		vamp = temp->next;
		temp->next = new person;
		temp = temp->next;
		temp->data = ++vals;
		temp->next = vamp;
	}
}

void group::delete_them()
{
	person *temp=ref, *vamp=ref;
	//cout<<numb<<endl;
	/*
	do
	{
		cout<<temp->data<<endl;
		temp = temp->next;
	}
	while(temp != ref);
	*/
	cout<<"Starting at "<<temp->data<<endl;
	while(numb>1)
	{
		vamp = temp->next;
		vamp = vamp->next;
		cout<<"Deleting "<<temp->next->data<<endl;
		delete temp->next;
		temp->next = vamp;
		temp = vamp;
		numb--;
	}
	cout<<"Survivor: "<<temp->data<<endl;
}

int main(int argc, char *argv[])
{
	int n=0;
	char *x;
	if(argc==2)
	{
		x = argv[1];
		while(*x!='\0')
			n = n*10 + *(x++) - '0';
	}
	else
		n=7;
	group josephis;
	josephis.insert(n);
	josephis.delete_them();
}

