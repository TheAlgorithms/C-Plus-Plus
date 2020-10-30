/**
 * @file
 * @brief Implementation of Round Robin Scheduling
 * @details
 * Round Robin is a CPU scheduling algorithm where time slices are assigned to each process in a cyclic order.
 * To schedule processes fairly, this scheduler usually employs time sharing, giving each process a time slot or
 * quantum, and interrupting the process if it is not completed by then. The process is resumed the next time a
 * quanta is assigned to it. If a process terminates, the scheduler selects the first process in the ready queue to
 * execute. Round Robin Algorithm is a preemptive algorithm as the scheduler forces the process out of the CPU once
 * the time quota expires.
 * This program here computes the average turn around time and the average waiting time of the processes.
 * Reference: (https://en.wikipedia.org/wiki/Round-robin_scheduling)
 * @author [Srijita Pal](https://github.com/srijita1297)
 */


#include<iostream>
#include<cassert>
using namespace std;

struct process{
    int arr;
    int bt;
    int temp;
};

/**
* @struct details of the processes
* @param arr arrival time
* @param bt burst time
* @param temp supporting parameter initially made equal to the burst time
*/


int main(){

    int quanta;
    cout<<"Enter the time quanta [between 1 and 100]: ";
    cin>>quanta;

    int n,i;
    struct process pr[50];

    cout<<"\nEnter the number of processes [<=50]: ";
    cin>>n;
    cout<<"\nEnter the arrival times of all the processes in order: ";
    for(i=0;i<n;i++)
        cin>>pr[i].arr;
    cout<<"\nEnter the execution or burst times of all the processes accordingly: ";
    for(i=0;i<n;i++){
        cin>>pr[i].bt;
        pr[i].temp=pr[i].bt;
    }

    //To compute waiting time and turn around time

    int total=0,flag=0,x=n;
    int wait_time=0,turn_around_time=0;
    float awt,atat;
    i=0;

    cout<<"\nProcess ID\tBurst Time\tTurn Around Time\tWaiting Time";
    for(total=0,i=0;x!=0;){
        if(pr[i].temp<=quanta && pr[i].temp>0){
            total=total+pr[i].temp;
            pr[i].temp=0;
            flag=1;
        }
        else if(pr[i].temp>0){
            pr[i].temp=pr[i].temp-quanta;
            total=total+quanta;
        }
        if(pr[i].temp==0 && flag==1){
            x--;
            cout<<"\nProcess["<<i+1<<"]\t"<<pr[i].bt<<"\t\t"<<total-pr[i].arr<<"\t\t\t"<<total-pr[i].arr-pr[i].bt;
            wait_time=wait_time+total-pr[i].arr-pr[i].bt;
            turn_around_time=turn_around_time+total-pr[i].arr;
            flag=0;
        }
        if(i==n-1)
            i=0;
        else if(pr[i+1].arr<=total)
            i++;
        else
            i=0;
    }

    awt=wait_time*1.0/n;
    atat=turn_around_time*1.0/n;

    cout<<"\nThe average waiting time is "<<awt;
    cout<<"\nThe average turn around time is "<<atat;
    cout<<"\nTotal execution time is "<<total;


    return 0;

}
