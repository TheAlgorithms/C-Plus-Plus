
/**
 * @file mlfq_scheduling.cpp
 * @brief Implementation of Multilevel Feedback Queue CPU Scheduling.
 * @details Uses three scheduling queues. Q0 uses Round Robin with a time
 * quantum of 4, Q1 uses Round Robin with a time quantum of 8, and Q2
 * uses FCFS scheduling. Processes begin in Q0 and are demoted when
 * they exhaust their time quantum. Higher-priority arrivals can
 * preempt lower-priority processes. A preempted process retains its
 * unused quantum when it resumes.
 * @author https://github.com/akshitam18
 */

#include <algorithm>  /// for min() and stable_sort()
#include <cassert>    /// for assert() in test cases
#include <deque>      /// for deque scheduling queues
#include <iostream>   /// for output operations
#include <vector>     /// for storing processes

using std::cout;
using std::deque;
using std::endl;
using std::min;
using std::stable_sort;
using std::vector;

/**
 * @brief Stores the information of a process.
 */
struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int level;
    int quantum_remaining;
    int original_index;

    Process(int process_id, int arrival_time, int burst_time)
        : id(process_id),
          arrival(arrival_time),
          burst(burst_time),
          remaining(burst_time),
          completion(-1),
          level(-1),
          quantum_remaining(0),
          original_index(-1) {}
};

/**
 * @brief Schedules processes using Multilevel Feedback Queue scheduling.
 * @param processes Vector containing the processes.
 * @returns The processes with updated completion times, in their original
 * input order.
 */
vector<Process> mlfqScheduling(vector<Process> processes) {
    const int quantum[2] = {4, 8};
    deque<int> queues[3];

    int time = 0;
    int completed = 0;
    int next = 0;
    int n = static_cast<int>(processes.size());

    for (int i = 0; i < n; i++) {
        assert(processes[i].arrival >= 0 && processes[i].burst > 0);
        processes[i].original_index = i;
    }

    stable_sort(processes.begin(), processes.end(),
                [](const Process& a, const Process& b) {
                    return a.arrival < b.arrival;
                });

    auto addArrivals = [&]() {
        while (next < n && processes[next].arrival <= time) {
            processes[next].level = 0;
            processes[next].quantum_remaining = quantum[0];
            queues[0].push_back(next);
            next++;
        }
    };

    while (completed < n) {
        addArrivals();

        if (queues[0].empty() && queues[1].empty() && queues[2].empty()) {
            time = processes[next].arrival;
            addArrivals();
        }

        int level = 0;
        while (level < 3 && queues[level].empty()) {
            level++;
        }

        int index = queues[level].front();
        queues[level].pop_front();

        Process& p = processes[index];
        int run_time = p.remaining;

        if (level < 2) {
            run_time = min(run_time, p.quantum_remaining);
        }

        // A newly arriving higher-priority process can interrupt execution.
        if (next < n && processes[next].arrival > time &&
            processes[next].arrival - time < run_time) {
            run_time = processes[next].arrival - time;
        }

        time += run_time;
        p.remaining -= run_time;

        if (level < 2) {
            p.quantum_remaining -= run_time;
        }

        addArrivals();

        if (p.remaining == 0) {
            p.completion = time;
            completed++;
        } else if (level < 2 && p.quantum_remaining == 0) {
            p.level = level + 1;

            if (p.level < 2) {
                p.quantum_remaining = quantum[p.level];
            }

            queues[p.level].push_back(index);
        } else {
            queues[level].push_front(index);
        }
    }

    stable_sort(processes.begin(), processes.end(),
                [](const Process& a, const Process& b) {
                    return a.original_index < b.original_index;
                });

    return processes;
}

/**
 * @brief Runs test cases for MLFQ scheduling.
 */
static void test() {
    // Test 1: Processes sharing the same arrival time.
    vector<Process> processes;
    processes.emplace_back(1, 0, 3);
    processes.emplace_back(2, 0, 5);

    vector<Process> result = mlfqScheduling(processes);

    assert(result[0].completion == 3);
    assert(result[1].completion == 8);

    // Test 2: A new Q0 process preempts a Q1 process.
    vector<Process> preemption;
    preemption.emplace_back(1, 0, 10);
    preemption.emplace_back(2, 5, 1);

    result = mlfqScheduling(preemption);

    assert(result[0].id == 1);
    assert(result[0].completion == 11);
    assert(result[1].id == 2);
    assert(result[1].completion == 6);

    // Test 3: Empty input.
    result = mlfqScheduling({});
    assert(result.empty());

    // Test 4: CPU remains idle until the first process arrives.
    vector<Process> idle;
    idle.emplace_back(1, 5, 2);
    idle.emplace_back(2, 10, 1);

    result = mlfqScheduling(idle);

    assert(result[0].completion == 7);
    assert(result[1].completion == 11);

    // Test 5: A process finishes exactly at its time quantum.
    vector<Process> quantum_boundary;
    quantum_boundary.emplace_back(1, 0, 4);
    quantum_boundary.emplace_back(2, 0, 2);

    result = mlfqScheduling(quantum_boundary);

    assert(result[0].completion == 4);
    assert(result[1].completion == 6);

    // Test 6: A Q2 process is interrupted by a new Q0 process.
    vector<Process> lower_priority;
    lower_priority.emplace_back(1, 0, 20);
    lower_priority.emplace_back(2, 13, 1);

    result = mlfqScheduling(lower_priority);

    assert(result[0].completion == 21);
    assert(result[1].completion == 14);

    // Test 7: Results preserve the original input order.
    vector<Process> unsorted;
    unsorted.emplace_back(1, 5, 2);
    unsorted.emplace_back(2, 0, 3);

    result = mlfqScheduling(unsorted);

    assert(result[0].id == 1);
    assert(result[0].completion == 7);
    assert(result[1].id == 2);
    assert(result[1].completion == 3);

    cout << "All tests passed successfully!" << endl;
}

int main() {
    test();
    return 0;
}
