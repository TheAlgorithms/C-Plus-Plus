#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm> 
#include <queue> 
#include <iomanip>   
 
using namespace std; 
 
struct Process { 
    int id, bt, at, start, comp; 
}; 
vector<int> find_response(vector<Process>& input, int n) { 
  vector<int> rt(n); 
  for (int i = 0; i < n; i++) { 
  rt[i] = abs(input[i].start - input[i].at); 
  } 
  return rt; 
} 
vector<int> find_tat(vector<Process>& input, int n) { 
  vector<int> tat(n); 
  for (int i = 0; i < n; i++) { 
  tat[i] = abs(input[i].comp - input[i].at); 
  } 
  return tat; 
} 
vector<int> find_wt(vector<Process>& input, vector<int>& tat, int n) { 
  vector<int> wt(n); 
  for (int i = 0; i < n; i++) { 
  wt[i] = abs(tat[i] - input[i].bt); 
  } 
  return wt; 
  } 
  static bool comp(Process& a, Process& b) { 
  if (a.at == b.at) return a.id < b.id; 
  return a.at < b.at; 
} 
void schedule(vector<Process>& input, int n, int tq) { 
    sort(input.begin(), input.end(),comp); 
 
    queue<int> readyQueue; 
    int time = 0, completed = 0; 
    vector<int> remaining(n); 
    vector<bool> visited(n, false); 
 
    for(int i = 0; i < n; i++) { 
        remaining[i] = input[i].bt; 
        input[i].start=-1; 
    } 
 
    readyQueue.push(0);  
    visited[0] = true; 
 
    while(!readyQueue.empty()) { 
        int i = readyQueue.front(); 
        readyQueue.pop(); 
 
        if (input[i].start == -1) { 
            input[i].start = time; 
        } 
 
        int exec_time = min(tq, remaining[i]); 
        time += exec_time; 
        remaining[i] -= exec_time; 
 
        if (remaining[i] == 0) { 
            input[i].comp = time; 
            completed++; 
        } 
 
        for (int j = 1; j < n; j++) { 
            if (input[j].at <= time && !visited[j]) { 
                readyQueue.push(j); 
                visited[j] = true; 
            } 
        } 
 
        if (remaining[i] > 0) { 
            readyQueue.push(i); 
        } 
    } 
} 
 
 
int main() { 
    int n; 
    cout << "Enter the number of processes: " << endl; 
    cin >> n; 
    int tq; 
    cout << "Enter the time quanta: " << endl; 
    cin >> tq; 
 
    vector<Process> input(n); 
    for (int i = 0; i < n; i++) { 
        cout << "Enter the id, burst time and arrival time of process " << i + 1 << ":" << endl; 
        cin >> input[i].id >> input[i].bt >> input[i].at; 
    } 
 
    schedule(input, n, tq); 
    vector<int> response = find_response(input, n); 
    vector<int> turntime = find_tat(input, n); 
    vector<int> waittime = find_wt(input, turntime, n); 
 
    cout << setw(8) << "Process"  
         << setw(8) << "Burst"  
         << setw(8) << "Arrival"  
         << setw(8) << "Start"  
         << setw(12) << "Completion"  
         << setw(10) << "Response"  
         << setw(12) << "Turn Around"  
         << setw(8) << "Waiting"  
         << endl; 
 
    for (int i = 0; i < n; i++) { 
        cout << setw(8) << "P" + to_string(input[i].id) 
             << setw(8) << input[i].bt  
             << setw(8) << input[i].at  
             << setw(8) << input[i].start  
             << setw(12) << input[i].comp  
             << setw(10) << response[i]  
             << setw(12) << turntime[i]  
             << setw(8) << waittime[i]  
             << endl; 
    } 
 
    return 0; 
} 
