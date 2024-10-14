/**
 * @file
 * @brief Implementation of SJF CPU scheduling algorithm
 * @details
 * shortest job first (SJF), also known as shortest job next (SJN), is a
 * scheduling policy that selects for execution the waiting process with the
 * smallest execution time. SJN is a non-preemptive algorithm. Shortest
 * remaining time is a preemptive variant of SJN.
 * <a href="https://www.guru99.com/shortest-job-first-sjf-scheduling.html">
 * detailed description on SJF scheduling </a>
 * <a href="https://github.com/LakshmiSrikumar">Author : Lakshmi Srikumar </a>
 */

#include <algorithm>      /// for sorting
#include <cassert>        /// for assert
#include <iomanip>        /// for formatting the output
#include <iostream>       /// for IO operations
#include <queue>          /// for std::priority_queue
#include <random>         /// random number generation
#include <unordered_set>  /// for std::unordered_set
#include <vector>         /// for std::vector

using std::cin;
using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
using std::priority_queue;
using std::tuple;
using std::unordered_set;
using std::vector;

/**
 * @brief Comparator function for sorting a vector
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param t1 First tuple<S,T,E>t1
 * @param t2 Second tuple<S,T,E>t2
 * @returns true if t1 and t2 are in the CORRECT order
 * @returns false if t1 and t2 are in the INCORRECT order
 */
template <typename S, typename T, typename E>
bool sortcol(tuple<S, T, E>& t1, tuple<S, T, E>& t2) {
    if (get<1>(t1) < get<1>(t2) ||
        (get<1>(t1) == get<1>(t2) && get<0>(t1) < get<0>(t2))) {
        return true;
    }
    return false;
}

/**
 * @class Compare
 * @brief Comparator class for priority queue
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 */
template <typename S, typename T, typename E>
class Compare {
 public:
    /**
     * @param t1 First tuple
     * @param t2 Second tuple
     * @brief A comparator function that checks whether to swap the two tuples
     * or not.
     * <a
     * href="https://www.geeksforgeeks.org/comparator-class-in-c-with-examples/">
     * detailed description of comparator </a>
     * @returns true if the tuples SHOULD be swapped
     * @returns false if the tuples SHOULDN'T be swapped
     */
    bool operator()(tuple<S, T, E, double, double, double>& t1,
                    tuple<S, T, E, double, double, double>& t2) {
        // Compare burst times for SJF
        if (get<2>(t2) < get<2>(t1)) {
            return true;
        }
        // If burst times are the same, compare arrival times
        else if (get<2>(t2) == get<2>(t1)) {
            return get<1>(t2) < get<1>(t1);
        }
        return false;
    }
};

/**
 * @class SJF
 * @brief Class which implements the SJF scheduling algorithm
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 */
template <typename S, typename T, typename E>
class SJF {
    /**
     * Priority queue of schedules(stored as tuples) of processes.
     * In each tuple
     * @tparam 1st element: Process ID
     * @tparam 2nd element: Arrival Time
     * @tparam 3rd element: Burst time
     * @tparam 4th element: Completion time
     * @tparam 5th element: Turnaround time
     * @tparam 6th element: Waiting time
     */
    priority_queue<tuple<S, T, E, double, double, double>,
                   vector<tuple<S, T, E, double, double, double>>,
                   Compare<S, T, E>>
        schedule;

    // Stores final status of all the processes after completing the execution.
    vector<tuple<S, T, E, double, double, double>> result;

    // Stores process IDs. Used for confirming absence of a process while  it.
    unordered_set<S> idList;

 public:
    /**
     * @brief Adds the process to the ready queue if it isn't already there
     * @param id Process ID
     * @param arrival Arrival time of the process
     * @param burst Burst time of the process
     * @returns void
     *
     */
    void addProcess(S id, T arrival, E burst) {
        // Add if a process with process ID as id is not found in idList.
        if (idList.find(id) == idList.end()) {
            tuple<S, T, E, double, double, double> t =
                make_tuple(id, arrival, burst, 0, 0, 0);
            schedule.push(t);
            idList.insert(id);
        }
    }

    /**
     * @brief Algorithm for scheduling CPU processes according to
     * the Shortest Job First (SJF) scheduling algorithm.
     *
     * @details Non pre-emptive SJF is an algorithm that schedules processes
     * based on the length of their burst times. The process with the smallest
     * burst time is executed first.In a non-preemptive scheduling algorithm,
     * once a process starts executing,it runs to completion without being
     * interrupted.
     *
     * I used a min priority queue because it allows you to efficiently pick the
     * process with the smallest burst time in constant time, by maintaining a
     * priority order where the shortest burst process is always at the front.
     *
     * @returns void
     */

    vector<tuple<S, T, E, double, double, double>> scheduleForSJF() {
        // Variable to keep track of time elapsed so far
        double timeElapsed = 0;

        while (!schedule.empty()) {
            tuple<S, T, E, double, double, double> cur = schedule.top();

            // If the current process arrived at time t2, the last process
            // completed its execution at time t1, and t2 > t1.
            if (get<1>(cur) > timeElapsed) {
                timeElapsed += get<1>(cur) - timeElapsed;
            }

            // Add Burst time to time elapsed
            timeElapsed += get<2>(cur);

            // Completion time of the current process will be same as time
            // elapsed so far
            get<3>(cur) = timeElapsed;

            // Turnaround time = Completion time - Arrival time
            get<4>(cur) = get<3>(cur) - get<1>(cur);

            // Waiting time = Turnaround time - Burst time
            get<5>(cur) = get<4>(cur) - get<2>(cur);

            // Turnaround time >= Burst time
            assert(get<4>(cur) >= get<2>(cur));

            // Waiting time is never negative
            assert(get<5>(cur) >= 0);

            result.push_back(cur);
            schedule.pop();
        }
        return result;
    }
    /**
     * @brief Utility function for printing the status of
     *  each process after execution
     * @returns void
     */

    void printResult(
        const vector<tuple<S, T, E, double, double, double>>& processes) {
        cout << std::setw(17) << left << "Process ID" << std::setw(17) << left
             << "Arrival Time" << std::setw(17) << left << "Burst Time"
             << std::setw(17) << left << "Completion Time" << std::setw(17)
             << left << "Turnaround Time" << std::setw(17) << left
             << "Waiting Time" << endl;

        for (const auto& process : processes) {
            cout << std::setprecision(2) << std::fixed << std::setw(17) << left
                 << get<0>(process) << std::setw(17) << left << get<1>(process)
                 << std::setw(17) << left << get<2>(process) << std::setw(17)
                 << left << get<3>(process) << std::setw(17) << left
                 << get<4>(process) << std::setw(17) << left << get<5>(process)
                 << endl;
        }
    }
};

/**
 * @brief Computes the final status of processes after
 * applying non-preemptive SJF scheduling
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param input A vector of tuples containing Process ID, Arrival time, and
 * Burst time
 * @returns A vector of tuples containing Process ID, Arrival time, Burst time,
 *         Completion time, Turnaround time, and Waiting time
 */
template <typename S, typename T, typename E>
vector<tuple<S, T, E, double, double, double>> get_final_status(
    vector<tuple<S, T, E>> input) {
    // Sort the processes based on Arrival time and then Burst time
    sort(input.begin(), input.end(), sortcol<S, T, E>);

    // Result vector to hold the final status of each process
    vector<tuple<S, T, E, double, double, double>> result(input.size());
    double timeElapsed = 0;

    for (size_t i = 0; i < input.size(); i++) {
        // Extract Arrival time and Burst time
        T arrival = get<1>(input[i]);
        E burst = get<2>(input[i]);

        // If the CPU is idle, move time to the arrival of the next process
        if (arrival > timeElapsed) {
            timeElapsed = arrival;
        }

        // Update timeElapsed by adding the burst time
        timeElapsed += burst;

        // Calculate Completion time, Turnaround time, and Waiting time
        double completion = timeElapsed;
        double turnaround = completion - arrival;
        double waiting = turnaround - burst;

        // Store the results in the result vector
        result[i] = make_tuple(get<0>(input[i]), arrival, burst, completion,
                               turnaround, waiting);
    }

    return result;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // A vector to store the results of all processes across all test cases.
    vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>>
        finalResult;

    for (int i{}; i < 10; i++) {
        std::random_device rd;  // Seeding
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(1, 10);

        uint32_t n = distr(eng);
        SJF<uint32_t, uint32_t, uint32_t> readyQueue;
        vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>>
            input(n);

        // Generate random arrival and burst times
        for (uint32_t i{}; i < n; i++) {
            get<0>(input[i]) = i;
            get<1>(input[i]) = distr(eng);  // Random arrival time
            get<2>(input[i]) = distr(eng);  // Random burst time
        }

        // Print processes before scheduling
        cout << "Processes before SJF scheduling:" << endl;
        readyQueue.printResult(input);

        // Add processes to the queue
        for (uint32_t i{}; i < n; i++) {
            readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]),
                                  get<2>(input[i]));
        }

        // Perform SJF schedulings
        auto finalResult = readyQueue.scheduleForSJF();

        // Print processes after scheduling
        cout << "\nProcesses after SJF scheduling:" << endl;
        readyQueue.printResult(finalResult);
    }
    cout << "All the tests have successfully passed!" << endl;
}

/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    test();
    return 0;
}
