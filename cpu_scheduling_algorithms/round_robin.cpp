/**
 * @file
 * @brief Implementation of Round CPU scheduling algorithm
 * @details
 * Round Robin is a CPU scheduling algorithm where each process is assigned a
 * fixed time slot in a cyclic way. It is basically the preemptive version of
 * First come First Serve CPU Scheduling algorithm.
 * @link https://en.wikipedia.org/wiki/Round-robin_scheduling
 * @author [Varad Pundlik](https://github.com/varadpundlik)
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

/** @class Job
    @brief class to represent each process or job
*/
class Job {
    int id;
    string name;
    int at;   // Arrival time
    int wt;   // Waiting time
    int bt;   // Burst time
    int b1;   // Remaining burst time
    int tat;  // Turnaround time
    int ct;   // Completion time

 public:
    Job(int i, string n, int a, int b) {
        id = i;
        name = n;
        at = a;
        bt = b;
        b1 = bt;
        wt = 0;
        tat = 0;
        ct = 0;
    }
    /** @brief prints the porcess data
     *  @returns void
     */
    void printJob() {
        cout << name << endl;
        cout << "id : " << id << endl;
        cout << "waiting time : " << wt << endl;
        cout << "burst time : " << bt << endl;
        cout << "turn around time : " << tat << endl;
        cout << "completion time : " << ct << endl;
    }

    friend class Scheduler;
};
/** @class Schedduler
 *  @brief class to performs schedulig algorithms
 *  @param taskList List of processes
 *  @param num number of jobs
 */
class Scheduler {
    int num;               // Number of jobs
    vector<Job> taskList;  // List of jobs
    double avgWT;          // Average waiting time
    double avgTAT;         // Average turnaround time

 public:
    Scheduler(int n, vector<Job> t) {
        num = n;
        taskList = t;
        avgTAT = 0;
        avgWT = 0;
    }
    /** @brief round robin cpu scheduling algorithm
     *  @returns pair of avg. waiting time and avg. Turn Around time
     */
    pair<double, double> roundRobin(int tm) {
        int totalTAT = 0;  // Total Turnaround Time
        int totalWT = 0;   // Total Waiting Time

        queue<int> ready;  // Queue to store indices of ready jobs

        // Sort jobs by arrival
        sort(taskList.begin(), taskList.end(),
             [](const Job& jl, const Job& jr) { return jl.at < jr.at; });

        int temp = 0;

        cout << endl << endl;

        int t = 0;  // Current time
        int i = 0;
        int init_at = taskList[0].at;  // Initial arrival time of jobs

        // Add jobs with the same initial arrival time to the ready queue
        while (i < num) {
            if (taskList[i].at == init_at) {
                ready.push(i);
                i++;
            } else
                break;
        }

        // Main Round Robin scheduling loop
        while (!ready.empty()) {
            int j = ready.front();
            ready.pop();
            temp = t;

            // Execute a job for a time quantum or until completion
            if (taskList[j].b1 < tm)
                t += taskList[j].b1;
            else
                t += tm;

            taskList[j].b1 =
                max(taskList[j].b1 - tm, 0);  // Update remaining burst time

            // Add jobs that arrive while a job is executing and have remaining
            // burst time
            for (int i = 0; i < num; i++) {
                if (taskList[i].at <= t && taskList[i].at > temp &&
                    taskList[i].b1 > 0) {
                    ready.push(i);
                }
            }

            // If the job is completed, calculate turnaround time and waiting
            // time
            if (taskList[j].b1 > 0) {
                ready.push(j);
            } else {
                taskList[j].ct = t;
                taskList[j].tat = taskList[j].ct - taskList[j].at;
                taskList[j].wt = taskList[j].tat - taskList[j].bt;
                totalWT += taskList[j].wt;
                totalTAT += taskList[j].tat;
            }
        }

        // Calculate and display average waiting time and average turnaround
        // time
        avgWT = (double)totalWT / (double)num;
        avgTAT = (double)totalTAT / (double)num;

        return {avgWT, avgTAT};
    }

    void display() {
        cout << "Status of all the proceses post completion :" << endl;
        cout << "id\tname\tat\tbt\tct\twt\ttat" << endl;
        for (auto i : taskList) {
            cout << i.id << "\t" << i.name << "\t" << i.at << "\t" << i.bt
                 << "\t" << i.ct << "\t" << i.wt << "\t" << i.tat << endl;
        }
    }
};
/** @brief functoin for testing round robin algorithm
 *  @param input number of jobs and each job's id name arrival time and burst
 * time
 * @returns void
 */

void test() {
    vector<Job> t;
    Job j1(1, "P1", 0, 5);
    Job j2(2, "P2", 1, 4);
    Job j3(3, "P3", 2, 2);
    Job j4(4, "P4", 4, 1);
    t.push_back(j1);
    t.push_back(j2);
    t.push_back(j3);
    t.push_back(j4);
    Scheduler s(4, t);
    pair<double, double> p;
    p = s.roundRobin(2);
    // s.display();
    pair<double, double> exp = {4.75, 7.75};
    assert(p == exp);
    cout << "Test case successfully passed!!!" << endl;
}

/** @brief entrypoint of program
 *  @returns 0
 */
int main() {
    test();
    return 0;
}
