#include <iostream>
using namespace std;
#define maxsize 4
int main()
{
    int pid[maxsize],priority[maxsize],burst[maxsize],wt[maxsize],tat[maxsize],temp,i,j;
    float awt=0,atat=0;
    cout<<"\n\n**************************************************************************************************************************************************************************************\n";
    cout<<"\nPriority Scheduling (Non - Preemptive)\n";
    cout<<"\nLowest the number Highest the Priority\n";
    cout<<"\n**************************************************************************************************************************************************************************************\n";
    cout<<"\nEnter Process Priority & Burst Time\n";
    for(i=0;i<maxsize;i++)
    {
        cout<<endl;
        pid[i]=i+1;
        cout<<"Process : P"<<pid[i]<<endl;
        cout<<"Priority : ";
        cin>>priority[i];
        cout<<"Burst Time : ";
        cin>>burst[i];
    }
    //sort processes according to priorities using Bubble Sort
    for(i=0;i<maxsize;i++)
    {
        for(j=0;j<maxsize-i-1;j++)
        {
            if(priority[j]>priority[j+1])
            {
                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;

                temp=priority[j];
                priority[j]=priority[j+1];
                priority[j+1]=temp;

                temp=burst[j];
                burst[j]=burst[j+1];
                burst[j+1]=temp;
            }
        }
    }
    for(i=0;i<maxsize;i++)
    {
        wt[i]=0;
        tat[i]=0;
        for(j=0;j<i;j++)
        {
            wt[i]=wt[i]+burst[j]; //calculates waiting time
        }
        awt=awt+wt[i];
        tat[i]=wt[i]+burst[i]; //calculates turn around time
        atat=atat+tat[i];
    }
    cout<<"\n________________________________________________________________________________\n";
    cout<<"\nProcess\t\tPriority\tBurstTime\tWaiting Time\tTurn Around Time\n";
    for(i=0;i<maxsize;i++)
    {
        cout<<"P"<<pid[i]<<"\t\t"<<priority[i]<<"\t\t"<<burst[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }
    cout<<"________________________________________________________________________________\n";
    cout<<"\n\nGantt Chart\n\n| ";
    for(i=0;i<maxsize;i++)
    {
        cout<<"P"<<pid[i]<<" | ";
    }
    awt=awt/maxsize; //calculates average waiting time
    atat=atat/maxsize; //calculates average turn around time
    cout<<"\n\nAverage Waiting Time : "<<awt<<endl;
    cout<<"\nAverage Turn Around Time : "<<atat<<endl<<endl;
    return 0;
}
