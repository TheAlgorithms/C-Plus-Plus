#include <iostream>
using namespace std;

class node
{
public:
    int info;
    node* next;
    node(int x, node* n=NULL)
    {
        info=x;
        next=n;
    }
};


class stacktype
{
    node* top;
public:

    stacktype()
    {
        top=NULL;
    }
    void push(node*);
    int pop();
    int isempty();
    void clr();
    void display();
    node* createnewnode(int);
    int countelements();
    void displaytopmost();
};
int stacktype::isempty()
{
    if(top==NULL)
        return 1;
    else
        return 0;
}
void stacktype::clr()
{
    node* p;
    p=top;
    top=top->next;
    for(p=top;p!=NULL;p=top)
    {
        delete p;
        top=top->next;
    }
}
int stacktype::pop()
{
    int d=0;
    node* p;
    p=top;
    top=top->next;
    d=p->info;
    delete p;
    return d;
}
node* stacktype::createnewnode(int x)
{
    node* nptr;
    nptr=new node(x);
    nptr->info=x;
    nptr->next=NULL;//grounding
    return nptr;
}
void stacktype::push(node* nptr)
{
    if(top==NULL)
        top=nptr;
    else
    {
        nptr->next=top;
        top=nptr;
    }
}
void stacktype::display()
{
    node* ptr;
    if(top==NULL)
        cout<<"STACK IS EMPTY. NOTHING TO BE DISPLAYED"<<endl;
    else
    {
        cout<<"CONTENTS OF THE STACK STARTING FROM THE TOPMOST POINTER: ";
        for(ptr=top;ptr!=NULL;ptr=ptr->next)
            cout<<ptr->info<<"\t";
        cout<<endl;
    }
}
int stacktype::countelements()
{
    int c=0;
    node* ptr;
    for(ptr=top;ptr!=NULL;ptr=ptr->next)
        c++;
    return c;
}
void stacktype::displaytopmost()
{
    cout<<"THE TOPMOST ELEMENT IS "<<top->info<<endl;
}

int main()
{
    stacktype s;
    int e,a,d,choice, num;
    char c='y';
    node* temp;
    while(c=='y'||c=='Y')
    {
        cout<<"MAIN MENU"<<endl;
        cout<<"1. TO PUSH AN ELEMENT"<<endl;
        cout<<"2. TO POP THE TOPMOST ELEMENT"<<endl;
        cout<<"3. TO CHECK WHETHER THE STACK IS EMPTY"<<endl;
        cout<<"4. TO DISPLAY THE ELEMENTS OF THE STACK"<<endl;
        cout<<"5. TO CLEAR THE STACK"<<endl;
        cout<<"6. TO COUNT THE ELEMNTS IN STACK"<<endl;
        cout<<"7. TO DISPLAY THE TOPMOST ELEMENT"<<endl;
        cout<<"ENTER YOUR CHOICE 1-7"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1:cout<<"ENTER AN INTEGER"<<endl;
                    cin>>a;
                    temp=s.createnewnode(a);
                    s.push(temp);
                    s.display();
                    break;
            case 2:e=s.isempty();
                    if(e==1)
                        cout<<"STACK IS EMPTY"<<endl;
                    else
                    {
                        d=s.pop();
                        cout<<d<<" HAS BEEN DELETED"<<endl;
                        s.display();
                    }
                    break;
            case 3:e=s.isempty();
                    if(e==1)
                        cout<<"THE STACK IS EMPTY"<<endl;
                    else
                        cout<<"STACK IS NOT EMPTY"<<endl;
                    break;
            case 4:s.display();
                    break;
            case 5:s.clr();
                    cout<<"THE STACK HAS BEEN CLEARED"<<endl;
                    break;
            case 6:num=s.countelements();
                    if(num==0)
                    {
                        cout<<"NO ELEMENTS ARE PRESENT IN THE STACK"<<endl;
                    }
                    else
                    {
                        cout<<num<<" ELEMTS ARE PRESENT IN THE STACK"<<endl;
                    }
                    break;
            case 7:e=s.isempty();
                    if(e==1)
                        cout<<"STACK IS EMPTY"<<endl;
                    else
                    {
                        s.displaytopmost();
                    }
                    break;
            default:cout<<"ERROR IN INPUT"<<endl;
        }
        cout<<"DO YOU WANT TO CONTINUE? (Y/N)"<<endl;
        cin>>c;
    }
    return 0;
}
