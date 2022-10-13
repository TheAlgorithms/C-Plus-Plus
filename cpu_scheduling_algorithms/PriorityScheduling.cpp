#include<iostream>
using namespace std;
struct Process {
   int pid; // Process ID
   int bt; // CPU Burst time required
   int priority; // Priority of this process
};
// sorting the Process acc. to the priority
bool compare(Process a, Process b) {
   return (a.priority > b.priority);
}
void waitingtime(Process pro[], int n, int wt[]) {
   // Initial waiting time for a process is 0
   wt[0] = 0;
   // calculating waiting time
   for (int i = 1; i < n ; i++ )
      wt[i] = pro[i-1].bt + wt[i-1] ;
}
 // Function to calculate turn around time
void turnarround( Process pro[], int n, int wt[], int tat[]) {
   // calculating turnaround time by adding
   // bt[i] + wt[i]
   for (int i = 0; i < n ; i++)
      tat[i] = pro[i].bt + wt[i];
}
//Function to calculate average time
void avgtime(Process pro[], int n) {
   int wt[n], tat[n], total_wt = 0, total_tat = 0;
   //Function to find waiting time of all processes
   waitingtime(pro, n, wt);
   //Function to find turn around time for all processes
   turnarround(pro, n, wt, tat);
   //Display processes along with all details
   cout << "\nProcesses "<< " Burst time " << " Waiting time " << " Turn around time\n";
   // Calculate total waiting time and total turn
   // around time
   for (int i=0; i<n; i++) {
      total_wt = total_wt + wt[i];
      total_tat = total_tat + tat[i];
      cout << " " << pro[i].pid << "\t\t" << pro[i].bt << "\t " << wt[i] << "\t\t " << tat[i] <<endl;
   }
   cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
   cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}
void scheduling(Process pro[], int n) {
   // Sort processes by priority
   sort(pro, pro + n, compare);
   cout<< "Order in which processes gets executed \n";
   for (int i = 0 ; i < n; i++)
      cout << pro[i].pid <<" " ;
   avgtime(pro, n);
}
// main function
int main() {
   Process pro[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
   int n = sizeof pro / sizeof pro[0];
   scheduling(pro, n);
   return 0;
}
