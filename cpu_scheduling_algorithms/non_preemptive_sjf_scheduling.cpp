/**
 * @file
 * @brief Implementation of the non-preemptive Shortest Job First (SJF) CPU
 * scheduling algorithm
 * @details
 * Shortest job first (SJF), also known as shortest job next (SJN), is a
 * scheduling policy that selects for execution the *already arrived*
 * process with the smallest burst (execution) time. This is the
 * non-preemptive variant: once a process starts running it is not
 * interrupted, even if a shorter job arrives while it is executing.
 * <a href="https://www.guru99.com/shortest-job-first-sjf-scheduling.html">
 * detailed description on SJF scheduling </a>
 *
 * A correct implementation must never schedule a process that has not yet
 * arrived, even if it has the smallest burst time of all the processes
 * submitted to the scheduler. At every decision point, only processes
 * that have arrived by the current simulated time are eligible to run; if
 * none have arrived, the CPU sits idle until the next arrival.
 *
 * @author [Lakshmi Srikumar](https://github.com/LakshmiSrikumar) (original
 * skeleton)
 */

#include <algorithm>      /// for std::sort
#include <cassert>        /// for assert
#include <iomanip>        /// for formatting the output
#include <iostream>       /// for IO operations
#include <queue>          /// for std::priority_queue
#include <random>         /// for std::mt19937 based random number generation
#include <tuple>          /// for std::tuple
#include <unordered_set>  /// for std::unordered_set
#include <vector>         /// for std::vector

/**
 * @namespace scheduling
 * @brief CPU scheduling algorithms
 */
namespace scheduling {
/**
 * @namespace non_preemptive_sjf
 * @brief Functions for the non-preemptive Shortest Job First algorithm
 */
namespace non_preemptive_sjf {

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
 * Result tuple layout, used throughout this file:
 * 1st element: Process ID
 * 2nd element: Arrival Time
 * 3rd element: Burst time
 * 4th element: Completion time
 * 5th element: Turnaround time
 * 6th element: Waiting time
 */
template <typename S, typename T, typename E>
using process_result_t = tuple<S, T, E, double, double, double>;

/**
 * @brief Orders raw (id, arrival, burst) tuples by arrival time, tie-broken
 * by process ID.
 * @details This is used purely to determine the ORDER in which processes
 * become available to the scheduler. It does not decide execution order.
 */
template <typename S, typename T, typename E>
struct ArrivalOrder {
    bool operator()(const tuple<S, T, E>& a, const tuple<S, T, E>& b) const {
        if (get<1>(a) != get<1>(b)) {
            return get<1>(a) < get<1>(b);
        }
        return get<0>(a) < get<0>(b);
    }
};

/**
 * @brief Min-heap comparator for the "ready queue" of already-arrived
 * processes: smallest burst time first, ties broken by earliest arrival,
 * then smallest process ID.
 * @details std::priority_queue is a max-heap with respect to the supplied
 * comparator, so to make the *smallest* burst time appear at top() this
 * comparator must report the *larger*-burst tuple as having lower priority.
 */
template <typename S, typename T, typename E>
struct ReadyQueueOrder {
    bool operator()(const process_result_t<S, T, E>& a,
                    const process_result_t<S, T, E>& b) const {
        if (get<2>(a) != get<2>(b)) {
            return get<2>(a) > get<2>(b);
        }
        if (get<1>(a) != get<1>(b)) {
            return get<1>(a) > get<1>(b);
        }
        return get<0>(a) > get<0>(b);
    }
};

/**
 * @class SJF
 * @brief Class which implements the non-preemptive SJF scheduling algorithm
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 */
template <typename S, typename T, typename E>
class SJF {
    /// Raw (id, arrival, burst) triples exactly as submitted.
    vector<tuple<S, T, E>> processes{};

    /// Final scheduled results, in the order processes were executed.
    vector<process_result_t<S, T, E>> result{};

    /// Tracks process IDs already added, to reject duplicates.
    unordered_set<S> idList{};

 public:
    /**
     * @brief Registers a process with the scheduler if its ID hasn't been
     * used already.
     * @param id Process ID
     * @param arrival Arrival time of the process
     * @param burst Burst time of the process
     * @returns void
     */
    void addProcess(S id, T arrival, E burst) {
        if (idList.find(id) == idList.end()) {
            processes.emplace_back(id, arrival, burst);
            idList.insert(id);
        }
    }

    /**
     * @brief Runs non-preemptive SJF scheduling over every registered
     * process.
     * @details We keep two collections:
     *  - `byArrival`: every process, sorted by arrival time, that has NOT
     *     yet been admitted to the ready queue.
     *  - `ready`: a min-heap (by burst time) of every process that HAS
     *     arrived but not yet run.
     *
     * At each step we admit every process whose arrival time is at most
     * the current simulated time into `ready`. If `ready` is still empty
     * (nothing has arrived), the CPU is idle, so we fast-forward the clock
     * to the next arrival. Otherwise we run whichever admitted process has
     * the smallest burst time. This guarantees a process can never be
     * scheduled before it arrives, regardless of how short its burst is.
     * @returns Results in execution order.
     */
    vector<process_result_t<S, T, E>> scheduleForSJF() {
        result.clear();
        if (processes.empty()) {
            return result;
        }

        vector<tuple<S, T, E>> byArrival = processes;
        std::sort(byArrival.begin(), byArrival.end(), ArrivalOrder<S, T, E>());

        priority_queue<process_result_t<S, T, E>,
                       vector<process_result_t<S, T, E>>,
                       ReadyQueueOrder<S, T, E>>
            ready;

        const size_t n = byArrival.size();
        size_t nextToArrive = 0;
        double timeElapsed = 0;

        while (result.size() < n) {
            // Admit every process that has arrived by now.
            while (nextToArrive < n &&
                   get<1>(byArrival[nextToArrive]) <= timeElapsed) {
                const auto& p = byArrival[nextToArrive];
                ready.push(
                    make_tuple(get<0>(p), get<1>(p), get<2>(p), 0.0, 0.0, 0.0));
                ++nextToArrive;
            }

            // CPU is idle: nothing has arrived yet, so jump the clock
            // forward to the next arrival instead of guessing.
            if (ready.empty()) {
                timeElapsed = get<1>(byArrival[nextToArrive]);
                continue;
            }

            // Run the shortest job among those that have already arrived.
            process_result_t<S, T, E> cur = ready.top();
            ready.pop();

            timeElapsed += get<2>(cur);               // Add burst time
            get<3>(cur) = timeElapsed;                // Completion time
            get<4>(cur) = get<3>(cur) - get<1>(cur);  // Turnaround time
            get<5>(cur) = get<4>(cur) - get<2>(cur);  // Waiting time

            // Turnaround time >= Burst time
            assert(get<4>(cur) >= get<2>(cur));
            // Waiting time is never negative
            assert(get<5>(cur) >= 0);

            result.push_back(cur);
        }

        return result;
    }

    /**
     * @brief Utility function for printing the status of each process
     * @param toPrint the processes to print
     * @returns void
     */
    void printResult(const vector<process_result_t<S, T, E>>& toPrint) const {
        cout << std::setw(17) << left << "Process ID" << std::setw(17) << left
             << "Arrival Time" << std::setw(17) << left << "Burst Time"
             << std::setw(17) << left << "Completion Time" << std::setw(17)
             << left << "Turnaround Time" << std::setw(17) << left
             << "Waiting Time" << endl;

        for (const auto& process : toPrint) {
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
 * @brief Independent O(n^2) reference implementation, used only to check
 * SJF::scheduleForSJF() against in tests.
 * @details At every scheduling step, scans every not-yet-completed process,
 * considers only the ones that have already arrived by the current
 * simulated time, and greedily picks the smallest burst time (ties broken
 * by arrival, then ID) -- deliberately written differently from the
 * priority-queue approach above so the two can catch each other's bugs.
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param input A vector of (id, arrival, burst) tuples
 * @returns Results in execution order.
 */
template <typename S, typename T, typename E>
vector<process_result_t<S, T, E>> get_final_status(
    vector<tuple<S, T, E>> input) {
    const size_t n = input.size();
    vector<bool> done(n, false);
    vector<process_result_t<S, T, E>> result;
    result.reserve(n);

    double timeElapsed = 0;

    for (size_t scheduled = 0; scheduled < n; ++scheduled) {
        int best = -1;
        for (size_t i = 0; i < n; ++i) {
            if (done[i] || get<1>(input[i]) > timeElapsed) {
                continue;
            }
            if (best == -1 || get<2>(input[i]) < get<2>(input[best]) ||
                (get<2>(input[i]) == get<2>(input[best]) &&
                 get<1>(input[i]) < get<1>(input[best])) ||
                (get<2>(input[i]) == get<2>(input[best]) &&
                 get<1>(input[i]) == get<1>(input[best]) &&
                 get<0>(input[i]) < get<0>(input[best]))) {
                best = static_cast<int>(i);
            }
        }

        if (best == -1) {
            // Nothing eligible has arrived yet; jump to the earliest
            // remaining arrival and retry this same slot.
            double nextArrival = -1;
            for (size_t i = 0; i < n; ++i) {
                if (!done[i] &&
                    (nextArrival < 0 || get<1>(input[i]) < nextArrival)) {
                    nextArrival = get<1>(input[i]);
                }
            }
            timeElapsed = nextArrival;
            --scheduled;
            continue;
        }

        done[best] = true;
        timeElapsed += get<2>(input[best]);
        double completion = timeElapsed;
        double turnaround = completion - get<1>(input[best]);
        double waiting = turnaround - get<2>(input[best]);
        result.push_back(make_tuple(get<0>(input[best]), get<1>(input[best]),
                                    get<2>(input[best]), completion, turnaround,
                                    waiting));
    }
    return result;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // Regression case: this is the exact scenario the previous
    // priority-queue-by-burst-only implementation got wrong. Process A
    // arrives first with the CPU idle and must run immediately, even
    // though B (arriving later) has a shorter burst time.
    {
        SJF<int, int, int> q;
        q.addProcess(0, 0, 10);  // A: arrives at 0, burst 10
        q.addProcess(1, 1, 1);   // B: arrives at 1, burst 1

        auto res = q.scheduleForSJF();

        assert(get<0>(res[0]) == 0);   // A must run first
        assert(get<3>(res[0]) == 10);  // A completes at t=10
        assert(get<5>(res[0]) == 0);   // A never waits

        assert(get<0>(res[1]) == 1);   // B runs second
        assert(get<3>(res[1]) == 11);  // B completes at t=11
        assert(get<5>(res[1]) == 9);   // B waits 9 units for the CPU
    }

    // Randomized cross-check against the independent O(n^2) oracle.
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> countDist(1, 12);
    std::uniform_int_distribution<int> timeDist(1, 20);

    for (int trial = 0; trial < 500; ++trial) {
        int n = countDist(eng);
        SJF<int, int, int> readyQueue;
        vector<tuple<int, int, int>> input(n);

        for (int i = 0; i < n; ++i) {
            input[i] = make_tuple(i, timeDist(eng), timeDist(eng));
            readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]),
                                  get<2>(input[i]));
        }

        auto expected = get_final_status<int, int, int>(input);
        auto actual = readyQueue.scheduleForSJF();
        assert(expected == actual);
    }

    cout << "All the tests have successfully passed!" << endl;
}

}  // namespace non_preemptive_sjf
}  // namespace scheduling

/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    scheduling::non_preemptive_sjf::test();
    return 0;
}