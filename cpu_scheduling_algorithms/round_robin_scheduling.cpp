/**
 * @file
 * @brief Implementation of Round Robin CPU Scheduling Algorithm
 * @details
 * Round Robin is a preemptive CPU scheduling algorithm in which every process
 * is assigned a fixed time quantum. If a process is not completed within its
 * quantum, it is moved to the end of the ready queue until it finishes.
 *
 * @author Mannan Loomba
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::queue;
using std::tuple;
using std::unordered_set;
using std::vector;
using std::sort;

/**
 * @class RoundRobin
 * @brief Class implementing the Round Robin CPU Scheduling Algorithm
 *
 * @tparam S Process ID type
 * @tparam T Arrival Time type
 * @tparam E Burst Time type
 */
template <typename S, typename T, typename E>
class RoundRobin {
 private:
    /**
     * Stores all input processes.
     * Tuple Format:
     * (Process ID, Arrival Time, Burst Time)
     */
    vector<tuple<S, T, E, E>> processes;

    /**
     * Stores the final scheduling result.
     */
    vector<tuple<S, T, E, double, double, double>> result;

    /**
     * Prevent duplicate process IDs.
     */
    unordered_set<S> idList;

 public:
    /**
     * @brief Adds a process to the scheduler.
     */
    void addProcess(S id, T arrival, E burst) {
        assert(burst > 0);

        if (idList.find(id) == idList.end()) {
            processes.emplace_back(id, arrival, burst, burst);
            idList.insert(id);
        }
    }

    /**
     * @brief Executes Round Robin Scheduling.
     *
     * @param quantum Time quantum.
     * @returns Final scheduling result.
     */
    vector<tuple<S, T, E, double, double, double>> scheduleForRoundRobin(
        E quantum) {
        assert(quantum > 0);
        result.clear();
        auto currentProcesses = processes;

        if (currentProcesses.empty()) {
            return result;
        }

        sort(currentProcesses.begin(), currentProcesses.end(),
             [](const tuple<S, T, E, E>& a, const tuple<S, T, E, E>& b) {
                 if (get<1>(a) == get<1>(b))
                     return get<0>(a) < get<0>(b);
                 return get<1>(a) < get<1>(b);
             });
        queue<size_t> readyQueue;

        double currentTime = 0;

        size_t index = 0;

        size_t completed = 0;
        if (!currentProcesses.empty()) {
            currentTime = get<1>(currentProcesses[0]);
        }

        while (index < currentProcesses.size() &&
               get<1>(currentProcesses[index]) <= currentTime) {
            readyQueue.push(index);
            index++;
        }
        while (completed < currentProcesses.size()) {
            if (readyQueue.empty()) {
                if (index >= currentProcesses.size()) {
                    break;
                }

                currentTime = get<1>(currentProcesses[index]);

                while (index < currentProcesses.size() &&
                       get<1>(currentProcesses[index]) <= currentTime) {
                    readyQueue.push(index);
                    index++;
                }

                continue;
            }

            size_t current = readyQueue.front();
            readyQueue.pop();

            E& remaining = get<3>(currentProcesses[current]);

            E executeTime = std::min(remaining, quantum);

            remaining -= executeTime;
            currentTime += executeTime;
            // Add newly arrived processes to the ready queue
            while (index < currentProcesses.size() &&
                   get<1>(currentProcesses[index]) <= currentTime) {
                readyQueue.push(index);
                index++;
            }

            // Process finished
            if (remaining == 0) {
                double completion = currentTime;
                double turnaround =
                    completion -
                    static_cast<double>(get<1>(currentProcesses[current]));
                double waiting =
                    turnaround -
                    static_cast<double>(get<2>(currentProcesses[current]));

                result.push_back(
                    make_tuple(get<0>(currentProcesses[current]),  // PID
                               get<1>(currentProcesses[current]),  // Arrival
                               get<2>(currentProcesses[current]),  // Burst
                               completion, turnaround, waiting));

                completed++;
            } else {
                // Process not finished, put it back into the ready queue
                readyQueue.push(current);
            }
        }
        sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });
        return result;
    }
};

static void test() {
    RoundRobin<int, int, int> rr;

    rr.addProcess(1, 0, 5);
    rr.addProcess(2, 1, 4);
    rr.addProcess(3, 2, 2);

    auto result = rr.scheduleForRoundRobin(2);

    assert(result.size() == 3);
    

    assert(get<0>(result[0]) == 1);
    assert(get<3>(result[0]) == 11);
    assert(get<4>(result[0]) == 11);
    assert(get<5>(result[0]) == 6);

    assert(get<0>(result[1]) == 2);
    assert(get<3>(result[1]) == 10);
    assert(get<4>(result[1]) == 9);
    assert(get<5>(result[1]) == 5);

    assert(get<0>(result[2]) == 3);
    assert(get<3>(result[2]) == 6);
    assert(get<4>(result[2]) == 4);
    assert(get<5>(result[2]) == 2);


    cout << "All Round Robin tests passed successfully!" << endl;
}

int main() {
    test();
    return 0;
}