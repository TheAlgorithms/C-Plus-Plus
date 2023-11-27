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

#include <algorithm>  /// for max function
#include <cassert>    /// for testing purpose
#include <iostream>   /// for printing results
#include <queue>      /// for job queue
#include <string>     /// for job name
#include <utility>    /// for using pair
#include <vector>     /// for tasklist of processes

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::pair;
using std::queue;
using std::string;
using std::vector;

/** @class Job
    @brief class to represent each process or job
*/
class Job {
    int id;
    string name;
    int arrivalTime;         ///< Arrival time
    int waitingTime{0};      ///< Waiting time
    int burstTime;           ///< Burst time
    int remainingBurstTime;  ///< Remaining burst time
    int turnAroundTime{0};   ///< Turnaround time
    int completionTime{0};   ///< Completion time

 public:
    Job(int i, string n, int a, int b)
        : id(i),
          name(std::move(std::move(n))),
          arrivalTime(a),
          burstTime(b),
          remainingBurstTime(burstTime) {}
    /** @brief prints the process data
     *  @returns void
     */
    void printJob() {
        cout << name << endl;
        cout << "id : " << id << endl;
        cout << "waiting time : " << waitingTime << endl;
        cout << "burst time : " << burstTime << endl;
        cout << "turn around time : " << turnAroundTime << endl;
        cout << "completion time : " << completionTime << endl;
    }

    friend class Scheduler;
};
/** @class Schedduler
 *  @brief class to performs schedulig algorithms
 *  @param taskList List of processes
 *  @param num number of jobs
 */
class Scheduler {
    int num;                      // Number of jobs
    vector<Job> taskList;         // List of jobs
    double avgWaitingTime{0};     // Average waiting time
    double avgTurnAroundTime{0};  // Average turnaround time

 public:
    Scheduler(int n, vector<Job> t)
        : num(n), taskList(std::move(std::move(t))) {}
    /** @brief round robin cpu scheduling algorithm
     *  @returns pair of avg. waiting time and avg. Turn Around time
     */
    pair<double, double> roundRobin(int tm) {
        int totalTurnAroundTime = 0;  // Total Turnaround Time
        int totalWaitingTime = 0;     // Total Waiting Time

        queue<int> ready;  // Queue to store indices of ready jobs

        // Sort jobs by arrival
        sort(taskList.begin(), taskList.end(),
             [](const Job& jl, const Job& jr) {
                 return jl.arrivalTime < jr.arrivalTime;
             });

        int temp = 0;

        cout << endl << endl;

        int t = 0;  // Current time
        int i = 0;
        int init_arrival_time =
            taskList[0].arrivalTime;  // Initial arrival time of jobs

        // Add jobs with the same initial arrival time to the ready queue
        while (i < num) {
            if (taskList[i].arrivalTime == init_arrival_time) {
                ready.push(i);
                i++;
            } else {
                break;
            }
        }

        // Main Round Robin scheduling loop
        while (!ready.empty()) {
            int j = ready.front();
            ready.pop();
            temp = t;

            // Execute a job for a time quantum or until completion
            if (taskList[j].remainingBurstTime < tm) {
                t += taskList[j].remainingBurstTime;
            } else {
                t += tm;
            }

            taskList[j].remainingBurstTime =
                max(taskList[j].remainingBurstTime - tm,
                    0);  // Update remaining burst time

            // Add jobs that arrive while a job is executing and have remaining
            // burst time
            for (int i = 0; i < num; i++) {
                if (taskList[i].arrivalTime <= t &&
                    taskList[i].arrivalTime > temp &&
                    taskList[i].remainingBurstTime > 0) {
                    ready.push(i);
                }
            }

            // If the job is completed, calculate turnaround time and waiting
            // time
            if (taskList[j].remainingBurstTime > 0) {
                ready.push(j);
            } else {
                taskList[j].completionTime = t;
                taskList[j].turnAroundTime =
                    taskList[j].completionTime - taskList[j].arrivalTime;
                taskList[j].waitingTime =
                    taskList[j].turnAroundTime - taskList[j].burstTime;
                totalWaitingTime += taskList[j].waitingTime;
                totalTurnAroundTime += taskList[j].turnAroundTime;
            }
        }

        // Calculate and display average waiting time and average turnaround
        // time
        avgWaitingTime =
            static_cast<double>(totalWaitingTime) / static_cast<double>(num);
        avgTurnAroundTime =
            static_cast<double>(totalTurnAroundTime) / static_cast<double>(num);

        return {avgWaitingTime, avgTurnAroundTime};
    }

    void display() {
        cout << "Status of all the proceses post completion :" << endl;
        cout << "id\tname\tarrivalTime\tburstTime\tcompletionTime\twaitingTim"
                "e\tTurnAroun"
                "dTime"
             << endl;
        for (const auto& i : taskList) {
            cout << i.id << "\t" << i.name << "\t" << i.arrivalTime << "\t"
                 << i.burstTime << "\t" << i.completionTime << "\t"
                 << i.waitingTime << "\t" << i.turnAroundTime << endl;
        }
    }
};
/** @brief functoin for testing round robin algorithm
 *  @param input number of jobs and each job's id name arrival time and burst
 * time
 * @returns void
 */
static void test() {
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
    test();  // run self-test implimentations
    return 0;
}
