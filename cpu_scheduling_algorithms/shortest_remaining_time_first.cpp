#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
//SRTF Algorithm
//Author : @Jayesh212

//structure to encapsulate details of a single process
typedef struct Process{
	int burstTime;
	int arrivalTime;
	int processId;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
	int remainingBurstTime;
}Process;

//Arrival Time Comparator function for use in sort
bool arrivalTimeComparator(Process &p1,Process &p2)
{
	return p1.arrivalTime < p2.arrivalTime;
}

//A structure for implementing operator() used as comparator
struct remainingBurstTimeComparator{
	bool operator()(Process &p1,Process &p2)
	{
		return p1.remainingBurstTime > p2.remainingBurstTime;
	}
};

//schedules the processes and fills the waiting time and details into each process structure
vector<Process> ScheduleUsingSRTF(vector<Process> &processes)
{
	priority_queue<Process,vector<Process>,remainingBurstTimeComparator> readyQueue;
	vector<Process>::iterator it;
	int remainingProcesses = processes.size();
	int currentTime = 0;
	vector<Process> completed;
	while(remainingProcesses)
	{
		for(it=processes.begin();it!=processes.end();it++)
		{
			if((*it).arrivalTime <= currentTime)
			{
				readyQueue.push(*it);
				processes.erase(it);
				if(processes.size()==0)break;
			}
		}
		currentTime+=1;
		if(!readyQueue.empty())
		{
			Process process = readyQueue.top();
			readyQueue.pop();
			process.remainingBurstTime-=1;
			if(process.remainingBurstTime==0)
			{
				//process execution completed
				process.completionTime  = currentTime;
				process.turnAroundTime = currentTime  - process.arrivalTime;
				process.waitingTime = process.turnAroundTime - process.burstTime;
				completed.push_back(process);
				remainingProcesses--;
			}
			else readyQueue.push(process);
		}
	}
	return completed;
}

void printCompletionChart(vector<Process> &processes)
{
	cout<<"Processes ordered on basis of completion"<<endl<<endl;
	for(auto it:processes)
	{
		cout<<"ID: "<<it.processId<<" A.T. :"<<it.arrivalTime<<" B.T. :"<<it.burstTime<<" C.T. :"<<it.completionTime<<" T.A.T. :"<<it.turnAroundTime<<endl;
	}
	cout<<endl;
	cout<<"A.T. -> Arrival Time , B.T. -> Burst Time , C.T. -> Completion Time , T.A.T. -> Turn Around Time"<<endl;
}

//main driver code
int main()
{
	vector<Process> processes;
	int processCount = 10;
	//A sample test case
	for(int i = 0;i<processCount;i++)
	{
		//add process data arrival Time, burst time and Pid 
		Process process;
		process.processId = i +1;
		process.arrivalTime = i + 1;
		process.burstTime = (processCount - i)*2;
		process.remainingBurstTime = (processCount - i)*2;
		processes.push_back(process);
	}
	//sort on arrival time basis
	sort(processes.begin(),processes.end(),arrivalTimeComparator);
	//schedule processes
	processes = ScheduleUsingSRTF(processes);
	//printing in the chart format
	printCompletionChart(processes);
	return 0;
}