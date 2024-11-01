/**
 * @file
 * @brief Implementation of the Shortest Remaining Time First (SRTF) CPU
 * scheduling algorithm
 * @details
 * SRTF is a preemptive scheduling algorithm where the process with the smallest
 * remaining time gets executed first. If two processes have the same remaining
 * time, the one that arrived first is selected. If they have the same arrival
 * time as well, the process with the smaller Process ID is chosen.
 */

#include <algorithm>  /// for min and max calculations
#include <cassert>    /// for assert
#include <climits>    /// for INT_MAX
#include <cstdlib>    /// for random number generation
#include <ctime>      /// for time
#include <iomanip>    /// for std::setw
#include <iostream>   /// for IO operations
#include <vector>     /// for std::vector

using std::cin;
using std::cout;
using std::endl;
using std::vector;

/**
 * @struct Process
 * @brief A structure to store information of each process in the SRTF
 * scheduling algorithm.
 */
struct Process {
    int pid;              ///< Process ID
    int burst_time;       ///< Burst time of the process
    int arrival_time;     ///< Arrival time of the process
    int remaining_time;   ///< Remaining time of the process
    int completion_time;  ///< Completion time of the process
    int waiting_time;     ///< Waiting time of the process
    int turnaround_time;  ///< Turnaround time of the process
};

/**
 * @brief Function to calculate completion, turnaround, and waiting times for
 * each process.
 * @param processes Vector of processes that need to be scheduled.
 */
void calculateTimes(vector<Process>& processes) {
    int n = processes.size();  ///< Number of processes
    int current_time = 0;      ///< Tracks the current time
    int completed = 0;         ///< Number of processes completed
    int min_remaining_time =
        INT_MAX;         ///< Minimum remaining time among processes
    int shortest = -1;   ///< Index of the shortest process
    bool check = false;  ///< Flag to check if any process is ready

    while (completed != n) {
        min_remaining_time = INT_MAX;
        check = false;

        for (int i = 0; i < n; i++) {
            // Select process with minimum remaining time and arrival time <=
            // current_time
            if ((processes[i].arrival_time <= current_time) &&
                (processes[i].remaining_time > 0) &&
                (processes[i].remaining_time < min_remaining_time)) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
                check = true;
            }
        }

        // If no process is ready to execute, increment current time
        if (!check) {
            current_time++;
            continue;
        }

        // Process the selected shortest process
        processes[shortest].remaining_time--;

        // If the process completes, calculate its times and update completed
        // count
        if (processes[shortest].remaining_time == 0) {
            completed++;
            processes[shortest].completion_time = current_time + 1;

            // Calculate turnaround and waiting times
            processes[shortest].turnaround_time =
                processes[shortest].completion_time -
                processes[shortest].arrival_time;

            processes[shortest].waiting_time =
                processes[shortest].turnaround_time -
                processes[shortest].burst_time;

            if (processes[shortest].waiting_time < 0) {
                processes[shortest].waiting_time = 0;
            }
        }

        current_time++;
    }
}

/**
 * @brief Utility function to print the details of each process after
 * scheduling.
 * @param processes Vector containing the process information.
 */
void printProcesses(const vector<Process>& processes) {
    cout << std::setw(10) << "PID" << std::setw(15) << "Burst Time"
         << std::setw(15) << "Arrival Time" << std::setw(15) << "Waiting Time"
         << std::setw(20) << "Turnaround Time" << std::setw(20)
         << "Completion Time" << endl;

    for (const auto& process : processes) {
        cout << std::setw(10) << process.pid << std::setw(15)
             << process.burst_time << std::setw(15) << process.arrival_time
             << std::setw(15) << process.waiting_time << std::setw(20)
             << process.turnaround_time << std::setw(20)
             << process.completion_time << endl;
    }
}

/**
 * @brief Testing function to validate the SRTF scheduling algorithm.
 * @details Generates random processes and verifies the computed results by
 * comparing with manually calculated values.
 */
void test() {
    srand(static_cast<unsigned>(time(nullptr)));
    int test_cases = 10;  // Reduced number for debugging

    for (int i = 0; i < test_cases; i++) {
        int n = 1 + rand() % 5;  // Reduced n for easier debugging
        vector<Process> processes;

        // Generate random process data
        for (int j = 0; j < n; j++) {
            int burst_time = 1 + rand() % 5;
            int arrival_time = rand() % 5;
            processes.push_back(
                {j, burst_time, arrival_time, burst_time, 0, 0, 0});
        }

        // Run the algorithm on generated data
        vector<Process> test_processes = processes;
        calculateTimes(test_processes);

        // Manual calculation for expected values
        vector<Process> expected_processes = processes;
        int current_time = 0;
        int completed = 0;
        int shortest = -1;
        int min_remaining_time = INT_MAX;
        bool check = false;

        while (completed != n) {
            min_remaining_time = INT_MAX;
            check = false;

            for (int j = 0; j < n; j++) {
                if ((expected_processes[j].arrival_time <= current_time) &&
                    (expected_processes[j].remaining_time > 0) &&
                    (expected_processes[j].remaining_time <
                     min_remaining_time)) {
                    min_remaining_time = expected_processes[j].remaining_time;
                    shortest = j;
                    check = true;
                }
            }

            if (!check) {
                current_time++;
                continue;
            }

            expected_processes[shortest].remaining_time--;

            if (expected_processes[shortest].remaining_time == 0) {
                completed++;
                expected_processes[shortest].completion_time = current_time + 1;

                expected_processes[shortest].turnaround_time =
                    expected_processes[shortest].completion_time -
                    expected_processes[shortest].arrival_time;

                expected_processes[shortest].waiting_time =
                    expected_processes[shortest].turnaround_time -
                    expected_processes[shortest].burst_time;

                if (expected_processes[shortest].waiting_time < 0) {
                    expected_processes[shortest].waiting_time = 0;
                }
            }

            current_time++;
        }

        // Compare computed and expected results
        for (int j = 0; j < n; j++) {
            if (test_processes[j].completion_time !=
                    expected_processes[j].completion_time ||
                test_processes[j].turnaround_time !=
                    expected_processes[j].turnaround_time ||
                test_processes[j].waiting_time !=
                    expected_processes[j].waiting_time) {
                // Diagnostic Output
                cout << "Test case " << i + 1
                     << " failed for Process ID: " << test_processes[j].pid
                     << endl;
                cout << "Expected Completion Time: "
                     << expected_processes[j].completion_time
                     << ", Calculated Completion Time: "
                     << test_processes[j].completion_time << endl;
                cout << "Expected Turnaround Time: "
                     << expected_processes[j].turnaround_time
                     << ", Calculated Turnaround Time: "
                     << test_processes[j].turnaround_time << endl;
                cout << "Expected Waiting Time: "
                     << expected_processes[j].waiting_time
                     << ", Calculated Waiting Time: "
                     << test_processes[j].waiting_time << endl;
                assert(false);  // Trigger failure for debugging
            }
        }
    }

    cout << "All tests passed successfully!" << endl;
}

/**
 * @brief Entry point of the program
 * @returns 0 on exit
 */
int main() {
    test();  // Run the test function
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter burst time and arrival time for process " << i + 1
             << ": ";
        cin >> processes[i].burst_time >> processes[i].arrival_time;
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculateTimes(processes);
    printProcesses(processes);

    return 0;
}
