#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter burst times for each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end(), compareByBurstTime);

    processes[0].waitingTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = processes[0].burstTime;

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    cout << "P" << processes[0].id << "\t" << processes[0].burstTime << "\t\t" << processes[0].waitingTime << "\t\t" << processes[0].turnaroundTime << endl;

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = totalTurnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        totalTurnaroundTime += processes[i].burstTime;

        cout << "P" << processes[i].id << "\t" << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }

    double avgWaitingTime = static_cast<double>(totalWaitingTime) / n;
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}
