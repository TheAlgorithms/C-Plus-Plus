//Round robin algorithm
#include<bits/stdc++.h>
using namespace std;
class job{
    public:
        int WT,BT,AT,TAT,PRO;
};
int main(){
    int n,tq,counter = 0;
    printf("Enter the number of the process\n");
    cin>>n;
    printf("Enter the time quantum\n"); // Enter time quantum
    cin>>tq;
    vector<job>a(n);
    float total_WT=0, total_TAT=0,Avg_WT,Avg_TAT;
    int temp[n];
    cout<<"Enter the process id, arrival time, burst time respectively,"<<n<<" times\n";
    for(int i =0; i<n ;i++){ // Enter arrival time, burst time with respect to process id
        cin>>a[i].PRO>>a[i].AT>>a[i].BT;
        temp[i] = a[i].BT;
    }
    cout<<"Your input is:-"<<endl;
	cout<<"Process Id\tArrival Time\tBurst Time\n";
    for(int i=0; i<n; i++){
		cout<<a[i].PRO<<"\t\t"<<a[i].AT<<"\t\t"<<a[i].BT<<endl;
	}
    queue<int>q; //Ready queue
    map<int,int>mp;
    int idx = n,t = 0;
    while( counter!=n ){
        for(int i =0; i<n; i++){
            if(a[i].AT<=t and a[i].BT>0 and (idx==n or idx!=i) and mp.find(i)== mp.end()){
                mp[i]++;
                q.push(i);
            }
        }
        if(idx!=n and a[idx].BT>0){
            q.push(idx);
            mp[idx]++;
        }
        int val = min(a[q.front()].BT,tq);
        t+=val;
        idx = q.front();
        a[idx].BT -= val;
        if(a[q.front()].BT == 0){
            counter++;
            a[q.front()].WT = t-temp[q.front()]-a[q.front()].AT;
            a[q.front()].TAT = a[q.front()].WT+temp[q.front()];

            total_WT+=a[q.front()].WT;
            total_TAT+=a[q.front()].TAT;
        }
        mp.erase(idx);
        q.pop();
    }
    Avg_WT=total_WT/n;
    Avg_TAT=total_TAT/n;
	cout<<endl<<"Final Result::"<<endl;
    cout<<"Process Id\tWaiting Time\tTurn Around Time\n";
    for(int i =0; i<n; i++){ // Output of waiting time, turn around time respective to process ids.
        cout<<a[i].PRO<<"\t\t"<<a[i].WT<<"\t\t"<<a[i].TAT<<endl;
    }
    printf("Avg waiting time of the process is %.2f\n",Avg_WT); // Average waiting time
    printf("Avg turn around time of the process %.2f\n",Avg_TAT);// Average Turn Around time
    return 0;
}