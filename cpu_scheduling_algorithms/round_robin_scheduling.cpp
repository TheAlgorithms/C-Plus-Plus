/**
 * @file
 * @brief Implementation of Round Robin Scheduling Algorithm.
 * @details
 * Round Robin is a CPU scheduling algorithm where each process is assigned a
 * fixed time slot (quantum) in cyclic order. It is simple, fair, and
 * starvation-free but may result in high context switching overhead.
 *
 * @see [Round Robin Scheduling on
 * Wikipedia](https://en.wikipedia.org/wiki/Round-robin_scheduling)
 *
 * @author [Kartikay Pandey](https://github.com/Kartikay-0111)
 */

#include <cassert>   ///< for assert
#include <iostream>  ///< for std::cout, std::endl
#include <vector>    ///< for std::vector

/**
 * @namespace scheduling
 * @brief Namespace for scheduling algorithms
 */
namespace scheduling {

/**
 * @brief A struct to represent a process.
 */
struct Process {
    int id;   ///< Process ID
    int bt;   ///< Burst Time
    int wt;   ///< Waiting Time
    int tat;  ///< Turnaround Time
};

/**
 * @brief Function to calculate waiting times for all processes.
 * @param processes Vector of processes
 * @param quantum Time quantum for Round Robin Scheduling
 */
void calculate_waiting_time(std::vector<Process> &processes, int quantum) {
    int n = processes.size();
    std::vector<int> rem_bt(n);  ///< Remaining burst times

    for (int i = 0; i < n; i++) {
        rem_bt[i] = processes[i].bt;
    }

    int t = 0;  ///< Current time

    // Round-robin scheduling logic
    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done =
                    false;  ///< There is at least one process left to execute

                if (rem_bt[i] > quantum) {
                    t += quantum;          ///< Increase time by quantum
                    rem_bt[i] -= quantum;  ///< Decrease remaining burst time
                } else {
                    t += rem_bt[i];  ///< Add remaining burst time
                    processes[i].wt =
                        t - processes[i].bt;  ///< Calculate waiting time
                    rem_bt[i] = 0;            ///< Process is completed
                }
            }
        }

        if (done) {  ///< If the process is completed then break
            break;
        }
    }
}

/**
 * @brief Function to calculate turnaround times for all processes.
 * @param processes Vector of processes
 */
void calculate_turnaround_time(std::vector<Process> &processes) {
    for (auto &process : processes) {
        process.tat = process.bt + process.wt;
    }
}

/**
 * @brief Function to calculate average times and display process details.
 * @param processes Vector of processes
 * @param quantum Time quantum for Round Robin Scheduling
 */
void calculate_avg_time(std::vector<Process> &processes, int quantum) {
    calculate_waiting_time(processes, quantum);
    calculate_turnaround_time(processes);

    int total_wt = 0;   ///< Total waiting time
    int total_tat = 0;  ///< Total turnaround time

    std::cout << "PID\tBT\tWT\tTAT\n";
    for (const auto &process : processes) {
        total_wt += process.wt;
        total_tat += process.tat;
        std::cout << process.id << '\t' << process.bt << '\t' << process.wt
                  << '\t' << process.tat << '\n';
    }

    std::cout << "Average waiting time = "
              << static_cast<float>(total_wt) / processes.size() << '\n';
    std::cout << "Average turnaround time = "
              << static_cast<float>(total_tat) / processes.size() << '\n';
}

}  // namespace scheduling

/**
 * @brief Self-test implementations
 */
static void test() {
    std::vector<scheduling::Process> processes = {
        {1, 10, 0, 0}, {2, 5, 0, 0}, {3, 8, 0, 0}};

    int quantum = 2;

    scheduling::calculate_avg_time(processes, quantum);

    // Validate waiting times
    assert(processes[0].wt == 13);  ///< Validate waiting time for process 1
    assert(processes[1].wt == 10);  ///< Validate waiting time for process 2
    assert(processes[2].wt == 13);  ///< Validate waiting time for process 3

    // Validate turnaround times
    assert(processes[0].tat == 23);  ///< Validate turnaround time for process 1
    assert(processes[1].tat == 15);  ///< Validate turnaround time for process 2
    assert(processes[2].tat == 21);  ///< Validate turnaround time for process 3

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Run self-tests
    return 0;
}
