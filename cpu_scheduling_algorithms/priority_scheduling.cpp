#include <bits/stdc++.h>
using namespace std;

class Process{
    public:
        int id;
        int priority;
        int burst_time;
        int arrival_time;
        int wait_time=0;
};

bool comp1(Process p1, Process p2){
    if(p1.arrival_time<p2.arrival_time)
        return true;
    else if(p1.arrival_time==p2.arrival_time && p1.priority<p2.priority)
        return true;
    return false;
}

bool operator<(Process p1, Process p2){
    if(p1.priority<p2.priority)
        return true;
    return false;
}

int main(){
    int n;
    cout<<"Enter number of processes"<<endl;
    cin>>n;
    cout<<"-------------------------"<<endl;

    priority_queue<Process> p_queue;
    vector<Process> p_list;
    for(int i=1; i<=n; i++){
        Process p;
        p.id=i;
        cout<<"Enter arrival time of Process "<<i<<endl;
        cin>>p.arrival_time;
        cout<<"Enter burst time of Process "<<i<<endl;
        cin>>p.burst_time;
        cout<<"Enter the priority of Process "<<i<<endl;
        cin>>p.priority;
        cout<<endl;
        p_list.push_back(p);
    }

    cout<<endl<<"-------------------------"<<endl<<endl;
    sort(p_list.begin(), p_list.end(), comp1);

    cout<<"Order for process execution: "<<endl;

    cout<<endl<<"Process id \t Start Time \t Execution Time \t Wait Time"<<endl;

    int ptr=1, time=0, exe=0, wait=0, start=0;

    Process p=p_list[0];

    while(true){
        time++; exe++;

        if(exe==p.burst_time){
            cout<<"Process "<<p.id<<"\t\t"<<start<<"\t\t"<<exe<<"\t\t"<<p.wait_time<<endl;
            if(!p_queue.empty()){
                p=p_queue.top();

                exe=0;
                start=time;
                p.wait_time=time-p.arrival_time;
                wait+=p.wait_time;
            }
            p_queue.pop();

            if(p_queue.empty())
                break;
        }

        if(time>=p_list[ptr].arrival_time && ptr<n){
            p_queue.push(p_list[ptr++]);
        }
    }
    cout<<"Process "<<p.id<<"\t\t"<<start<<"\t\t"<<exe<<"\t\t"<<p.wait_time<<endl;

    cout<<endl<<"Average Waiting Time is: "<<(float)wait/n<<endl;
}
