/**
 * @file fcfs.cpp
 * @brief An implementation of First Come First Serve Scheduling Algorithm
 *
 * @details
 * This algorithm allots CPU to processes on the basis of arrival time.
 * If there is a clash between two processes, the one with the smaller
 * PID is given priority.
 *
 * @author [Daksh Krishna Khanna](https://github.com/DakshKK)
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @struct process
 * @brief A struct which contains the details about the process.
 *
 * @var pid Holds the process ID for a process.
 * @var at  The arrival time of a given process.
 * @var bt  The burst time of a given process.
 * @var ct  The completion time of a given process (To be calculated).
 */

struct process {
    unsigned pid;  ///< process ID
    unsigned at;   ///< Arrival Time
    unsigned bt;   ///< Burst Time
    unsigned ct;   ///< Completion Time
};

/**
 * @fn void find_completion_time(std::vector<process> &proc)
 * @brief A function to calculate the completion time of all processes.
 *
 * @param proc A vector, which holds all processes, to be worked on.
 */

void find_completion_time(std::vector<process> *proc) {
    unsigned count = (*proc).size();
    unsigned end =
        0;  ///< To maintain how many processes have finished execution
    unsigned time = 0;  ///< To maintain what the current time in the system is
    unsigned max_at =
        std::max_element((*proc).begin(), (*proc).end(),
                         [](const process &a, const process &b) -> bool {
                             return a.at < b.at;
                         })
            ->at +
        1;
    while (end < count) {
        unsigned min_at = max_at;  ///< To find the smallest arrival time
        int idx = -1;              ///< Index at which the process is
        for (const auto &p : (*proc)) {
            if (!p.ct && min_at > p.at) {
                min_at = p.at;
                idx = static_cast<int>(p.pid);
            }
        }
        if (time < min_at) {
            time = min_at;
        }
        time +=
            (*proc)[idx]
                .bt;  ///< Add the burst time, to mark the end time of execution
        (*proc)[idx].ct =
            time;  ///< Completion time is the end time of execution
        end++;
    }
}

/**
 * @fn void find_avg_time(std::vector<process> &proc)
 * @brief A function to calculate completion time and averages of turn-around
 * and waiting time.
 *
 * @param proc A vector, which holds all processes, to be worked on.
 */

void find_avg_time(const std::vector<process> &proc) {
    float ta{0};  ///< To keep a running total of the turn-around time.
    float w{0};   ///< To keep a running total of the waiting time.

    std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : proc) {
        unsigned p_ta = p.ct - p.at;  ///< Turn-Around time is the difference
                                      ///< between completion and arrival time.
        unsigned p_w = p_ta - p.bt;   ///< Waiting time is the difference
                                      ///< between turn-around and burst time.
        std::cout << p.pid << '\t' << p.at << '\t' << p.bt << '\t' << p.ct
                  << '\t' << p_ta << '\t' << p_w << '\n';
        ta += static_cast<float>(p_ta);
        w += static_cast<float>(p_w);
    }

    ta /= proc.size();  ///< Get the average
    w /= proc.size();

    std::cout << std::endl;
    std::cout << "Average Waiting Time: " << w << '\n'
              << "Average Turn-Around Time: " << ta << '\n';
}

/**
 * Main Function
 */

int main() {
    std::vector<process> proc = {
        {0, 5, 2, 0}, {1, 5, 3, 0}, {2, 1, 4, 0}, {3, 2, 2, 0},
        {4, 1, 2, 0}, {5, 1, 1, 0}};  ///< A vector of process with
                                      ///< corresponding data.

    find_completion_time(&proc);
    find_avg_time(proc);

    std::vector<process> test = {
        {0, 5, 2, 12}, {1, 5, 3, 15}, {2, 1, 4, 5}, {3, 2, 2, 10},
        {4, 1, 2, 7},  {5, 1, 1, 8}};  ///< A vector to verify if the method
                                       ///< executed correctly.

    assert(std::equal(
        proc.begin(), proc.end(), test.begin(),
        [](const process &a, const process &b) { return a.ct == b.ct; }));

    return 0;
}
