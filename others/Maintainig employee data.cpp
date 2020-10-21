/*Design and Implement a menu driven program in C++ using circular singly linked list (CSLL) for maintaining the employee information of a super market. Provide the facility for creation of CSLL of N employees, Display the employee list, insertion of a new employee. */
#include<iostream> 
#include<ctype.h> 
using namespace std;

class node { 
public: 
int id; 
char g; 
char name[10], deg[10]; 
node *next; 
public: 
void getinfo() { 
cout<<"Enter the ID of employee"<<endl; 
cin>>id; 
cout<<"Enter the name of employee"<<endl; 
cin>>name; 
cout<<"Enter the designation of employee"<<endl; 
cin>>deg; 
cout<<"Enter the gender of employee"<<endl; 
cin>>g; 
} 
};

class cll { 
public: 
node *head; 
cll() { head = NULL; } 
void create(); 
void insert(); 
void del(); 
void display(); 
int count(); 
};

int cll:: count() /* Number of nodes in the list*/ 
{ 
int j=0; 
node *s, *head; 
s=head; 
do { 
s=s->next; 
j=j+1; 
} while(s->next!=head); 
return j; 
} 

void cll :: create() { 
int i=0,n; 
cout<<"Enter the number of employees"<<endl; 
cin>>n; 
node *temp,*p; 
for(i=0; i<n;i++) { 
temp=new node; 
temp->getinfo(); 
temp->next=NULL; 
if (head==NULL) { 
head=temp; 
head->next=head; } 
else { 
p=head; 
while(p->next!=head) 
  p=p->next; 
p->next=temp; 
temp->next=head; 
} 
} 
}

void cll::insert() { 
int pos; 
node a; 
cout<<"Enter the position at which it is to be inserted"<<endl; 
cin>>pos; 
node *temp, *p; 
p=head; 
temp=new node; 
temp->getinfo(); 
temp->next=NULL; 
if(pos==1) { 
while(p->next!=head) 
  p=p->next; 
p->next=temp; 
temp->next=head; 
head=temp; 
} 
else if(pos==count()+1) { 
while(p->next!=head) 
  p=p->next; 
p->next=temp; 
temp->next=head; 
} 
else if(1<pos && pos<count()+1) { 
int j; 
for(j=2;j<pos;j++) 
  p=p->next; 
temp->next=p->next; 
p->next=temp; 
} 
}

void cll:: del() { 
int emp_id; 
cout<<"Enter the ID of employee to be deleted"<<endl; 
cin>>emp_id; 
node *p,*pre; 
p=head; 
pre=head; 
while(p->next!=head) { 
if(p->id==emp_id) { 
pre->next=p->next; 
delete(p); 
cout<<emp_id<<'\t'<<"item deleted"<<endl; 
} 
else { 
pre=p; 
p=p->next; 
} 
} 
} 

void cll::display() { 
node *p; 
p=head; 
if(head==NULL) { 
cout<<"EMPTY List"; 
}
cout<<"Employee Id"<<'\t'<<"Employee Name"<<'\t'<<"Employee Designation"<<'\t'<<"Employee Gender"<<endl; 
do { 
cout<<p->id<<'\t'<<'\t'<<p->name<<'\t'<<'\t'<<p->deg<<'\t'<<'\t'<<p- >g<<'\t'<<'\t'<<endl; 
p=p->next; }while(p!= head); } 

int main() { 
cll emp; 
int choice, ch; 
do { 
cout<<"1. Registration"<<endl; cout<<"2. Insertion"<<endl; cout<<"3. Delete"<<endl; cout<<"4. Display"<<endl; cout<<"Enter your choice "<<endl; cin>>choice; 
switch(choice) { 
case 1: 
emp.create(); 
break; 
case 2: 
emp.insert(); 
break; 
case 3: 
emp.del(); 
break; 
case 4: 
cout<<"Employees of the company are:- "<<endl; 
emp.display(); 
break; 
default: 
cout<<"Wrong choice"; 
} cout<<"Do you want to continue(1/0)"<<endl; 
cin>>choice; 
} while(choice==1); }
