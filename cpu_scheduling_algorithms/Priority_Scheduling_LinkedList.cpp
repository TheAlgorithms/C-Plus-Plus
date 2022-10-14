#include <iostream>
#include <stdlib.h>
using namespace std;
struct proc
{
    int pid,priority,burst,wt,tat;
    struct proc *next;
    struct proc *prev;
};
struct proc *start=NULL;
struct proc *temp,*tmp;
struct proc *last=NULL;
struct proc *newnode;

void sort(struct proc *q)
{
    //Bubble Sort
    struct proc *i,*j;
    int temp;
    for(i=q;i!=NULL;i=i->next)
    {
        for(j=i->next;j!=NULL;j=j->next)
        {
            if(i->priority>j->priority)
            {
                temp=i->pid;
                i->pid=j->pid;
                j->pid=temp;

                temp=i->priority;
                i->priority=j->priority;
                j->priority=temp;

                temp=i->burst;
                i->burst=j->burst;
                j->burst=temp;
            }
        }
    }
}

int main()
{
    int i,j,n;
    float awt=0,atat=0;
    cout<<"\n\n**************************************************************************************************************************************************************************************\n";
    cout<<"\nPriority Scheduling (Non - Preemptive)\n";
    cout<<"\nLowest the number Highest the Priority\n";
    cout<<"\n**************************************************************************************************************************************************************************************\n";
    cout<<"\nEnter Number of Processes : ";
    cin>>n;
    cout<<"\nEnter Process Priority & Burst Time\n";
    for(i=0;i<n;i++)
    {
        newnode=(struct proc *)malloc(sizeof(struct proc));
        cout<<endl;
        newnode->pid=i+1;
        cout<<"Process : P"<<newnode->pid<<endl;
        cout<<"Priority : ";
        cin>>newnode->priority;
        cout<<"Burst Time : ";
        cin>>newnode->burst;
        if(start==NULL)
        {
            start=newnode;
            last=newnode;
            start->next=NULL;
            start->prev=NULL;
        }
        else
        {
            last->next=newnode;
            newnode->next=NULL;
            newnode->prev=last;
            last=newnode;
        }
    }
    //sort processes according to priorities using Bubble Sort
    sort(start);
    if(start==NULL)
    {
        cout<<"\nProcesses are not present !!!\n";
    }
    else
    {
        temp=start;
        while(temp!=NULL)   
        {
            temp->wt=0;
            temp->tat=0;
            tmp=start;
            while(tmp!=temp)
            {
                temp->wt=temp->wt+tmp->burst; //calculates waiting time
                tmp=tmp->next;
            }
            awt=awt+temp->wt;
            temp->tat=temp->wt+temp->burst; //calculates turn around time
            atat=atat+temp->tat;
            temp=temp->next;
        }
    }
    if(start==NULL)
    {
        cout<<"\nProcesses are not present !!!\n";
    }
    else
    {
        cout<<"\n________________________________________________________________________________\n";
        cout<<"\nProcess\t\tPriority\tBurstTime\tWaiting Time\tTurn Around Time\n";
        temp=start;
        while(temp!=NULL)
        {
            cout<<"P"<<temp->pid<<"\t\t"<<temp->priority<<"\t\t"<<temp->burst<<"\t\t"<<temp->wt<<"\t\t"<<temp->tat<<endl;
            temp=temp->next;
        }
        cout<<"________________________________________________________________________________\n";
    }    
    cout<<"\n\nGantt Chart\n\n| ";
    temp=start;
    while(temp!=NULL)
    {
        cout<<"P"<<temp->pid<<" | ";
        temp=temp->next;
    }
    awt=awt/n; //calculates average waiting time
    atat=atat/n; //calculates average turn around time
    cout<<"\n\nAverage Waiting Time : "<<awt<<endl;
    cout<<"\nAverage Turn Around Time : "<<atat<<endl<<endl;
    return 0;
}
