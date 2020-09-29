#include<iostream>
 
using namespace std;
 
int main()
{
    int n,b[20],w[20],a[20],i,j;
    float avg1=0,avg2=0;
    cout<<"Enter total number of processes: ";
    cin>>n;
 
    cout<<"\nEnter the Burst Time with respective process number\n";
    for(i=0;i<n;i++)
    {
        cout<<"P["<<i+1<<"]: ";
        cin>>b[i];
    }
 
    w[0]=0;    
 
    for(i=1;i<n;i++)
    {
        w[i]=0;
        for(j=0;j<i;j++)
            w[i]+=b[j];
    }
 
    cout<<"\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";
 
    for(i=0;i<n;i++)
    {
        a[i]=b[i]+w[i];
        avg1=avg1+w[i];
        avg2=avg2+a[i];
        cout<<"\nP["<<i+1<<"]"<<"\t\t"<<b[i]<<"\t\t"<<w[i]<<"\t\t"<<a[i];
    }
 
    avg1=avg1/i;
    avg2=avg2/i;
    cout<<"\n\nAverage Waiting Time: "<<avg1;
    cout<<"\nAverage Turnaround Time: "<<avg2;
 
    return 0;
}
