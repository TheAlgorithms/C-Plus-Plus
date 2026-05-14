/**
 * @file
 * @brief Implementation of Priority CPU scheduling algorithms
 * @details
 * Priority Scheduling selects the next process to run based on a numeric
 * priority value. In this implementation a **lower priority number means
 * higher urgency** (priority 1 runs before priority 2), matching the standard
 * UNIX/Linux convention.
 *
 * Two variants are provided inside the same file:
 *
 * **Non-Preemptive Priority Scheduling**
 * Once a process starts executing it runs to completion. When the CPU becomes
 * free, the highest-priority process among all currently arrived processes is
 * selected. Ties are broken first by arrival time, then by process ID.
 *
 * **Preemptive Priority Scheduling**
 * The CPU can be taken away from the running process if a newly arriving
 * process has a strictly higher priority (lower number). The preempted process
 * returns to the ready queue with its remaining burst time.
 *
 * Metrics computed:
 * - Completion Time (CT)  = time at which a process finishes
 * - Turnaround Time (TAT) = CT - Arrival Time
 * - Waiting Time (WT)     = TAT - Burst Time
 *
 * @see https://en.wikipedia.org/wiki/Scheduling_(computing)#Priority_scheduling
 * @author [Shubhangam Singh](https://github.com/Shubhangam-Singh)
 */

#include <algorithm>    /// for std::sort
#include <cassert>      /// for assert
#include <cstdint>      /// for uint32_t
#include <iomanip>      /// for std::setw, std::left
#include <iostream>     /// for std::cout, std::endl
#include <limits>       /// for std::numeric_limits
#include <tuple>        /// for std::tuple, std::make_tuple, std::get
#include <unordered_set>  /// for std::unordered_set
#include <vector>       /// for std::vector
#include <queue>        /// for std::priority_queue

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
 * @namespace cpu_scheduling_algorithms
 * @brief CPU scheduling algorithm implementations
 */
namespace cpu_scheduling_algorithms {

/**
 * @namespace priority_scheduling
 * @brief Functions and classes for Priority CPU scheduling algorithms
 */
namespace priority_scheduling {

/**
 * @brief Comparator to sort input processes by arrival time; ties broken by
 *        priority (lower = higher urgency), then by process ID.
 * @tparam S Process ID type
 * @tparam T Arrival time type
 * @tparam E Burst time type
 * @tparam P Priority type
 * @param a First process tuple (PID, arrival, burst, priority)
 * @param b Second process tuple
 * @returns true if @p a should come before @p b
 * @returns false otherwise
 */
template <typename S, typename T, typename E, typename P>
bool sortByArrival(const tuple<S, T, E, P>& a, const tuple<S, T, E, P>& b) {
    if (get<1>(a) != get<1>(b)) {
        return get<1>(a) < get<1>(b);   // earlier arrival first
    }
    if (get<3>(a) != get<3>(b)) {
        return get<3>(a) < get<3>(b);   // lower priority number (higher urgency)
    }
    return get<0>(a) < get<0>(b);       // smaller PID
}

/**
 * @class NonPreemptivePriority
 * @brief Implements Non-Preemptive Priority CPU scheduling.
 *
 * Once a process starts it runs to completion. When the CPU becomes free, the
 * highest-priority process (lowest priority number) among all arrived processes
 * is selected. Ties are broken by arrival time, then process ID.
 *
 * Each process is a 4-tuple: (PID, Arrival Time, Burst Time, Priority)
 * Each result is a 7-tuple:
 *   (PID, Arrival, Burst, Priority, Completion Time, Turnaround Time, Waiting
 * Time)
 *
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @tparam P Data type of Priority (lower number = higher urgency)
 */
template <typename S, typename T, typename E, typename P>
class NonPreemptivePriority {
    /** Input: (PID, arrival, burst, priority) */
    vector<tuple<S, T, E, P>> processes;

    /** Result: (PID, arrival, burst, priority, CT, TAT, WT) */
    vector<tuple<S, T, E, P, double, double, double>> result;

    /** Guard against duplicate process IDs */
    unordered_set<S> idList;

 public:
    /**
     * @brief Adds a process to the scheduler.
     * @param id      Unique process identifier
     * @param arrival Arrival time
     * @param burst   Total CPU burst time required
     * @param priority Priority value (lower number = higher urgency)
     * @returns void
     */
    void addProcess(S id, T arrival, E burst, P priority) {
        if (idList.find(id) == idList.end()) {
            processes.emplace_back(id, arrival, burst, priority);
            idList.insert(id);
        }
    }

    /**
     * @brief Runs the Non-Preemptive Priority scheduling algorithm.
     *
     * @details Algorithm:
     * 1. Sort processes by arrival time (ties: priority, then PID).
     * 2. Maintain a min-heap ready queue ordered by (priority, arrival, index).
     * 3. When the CPU is free, fast-forward to the next arriving process if the
     *    queue is empty, then pick the head of the heap.
     * 4. Run the selected process to completion; record CT, TAT, WT.
     * 5. After it finishes, admit all newly arrived processes to the heap and
     *    repeat.
     *
     * @returns Vector of 7-tuples with scheduling metrics (sorted by arrival).
     */
    vector<tuple<S, T, E, P, double, double, double>> scheduleForNPP() {
        uint32_t n = static_cast<uint32_t>(processes.size());
        if (n == 0) {
            return result;
        }

        std::sort(processes.begin(), processes.end(), sortByArrival<S, T, E, P>);

        // Ready queue: (priority, arrival, sorted-index) — min-heap
        using Entry = tuple<P, T, uint32_t>;
        auto cmp = [](const Entry& a, const Entry& b) {
            if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
            if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
            return get<2>(a) > get<2>(b);
        };
        priority_queue<Entry, vector<Entry>, decltype(cmp)> rq(cmp);

        result.resize(n);
        double t = 0.0;
        uint32_t nextToArrive = 0;
        uint32_t done = 0;

        while (done < n) {
            // Admit all processes that have arrived by time t
            while (nextToArrive < n &&
                   static_cast<double>(get<1>(processes[nextToArrive])) <= t) {
                rq.emplace(get<3>(processes[nextToArrive]),
                           get<1>(processes[nextToArrive]), nextToArrive);
                nextToArrive++;
            }

            // If nothing is ready, fast-forward to the next arrival
            if (rq.empty()) {
                t = static_cast<double>(get<1>(processes[nextToArrive]));
                continue;
            }

            // Pick the highest-priority arrived process
            auto [pri, arr, idx] = rq.top();
            rq.pop();

            double arrival = static_cast<double>(get<1>(processes[idx]));
            double burst   = static_cast<double>(get<2>(processes[idx]));

            t += burst;  // non-preemptive: run to completion
            double ct  = t;
            double tat = ct - arrival;
            double wt  = tat - burst;

            result[idx] = make_tuple(get<0>(processes[idx]),
                                     get<1>(processes[idx]),
                                     get<2>(processes[idx]),
                                     get<3>(processes[idx]),
                                     ct, tat, wt);
            done++;
        }
        return result;
    }

    /**
     * @brief Prints the scheduling table to standard output.
     * @returns void
     */
    void printResult() const {
        cout << std::setw(14) << left << "Process ID"
             << std::setw(14) << left << "Arrival"
             << std::setw(14) << left << "Burst"
             << std::setw(14) << left << "Priority"
             << std::setw(18) << left << "Completion Time"
             << std::setw(18) << left << "Turnaround Time"
             << std::setw(14) << left << "Waiting Time" << endl;
        for (const auto& p : result) {
            cout << std::fixed << std::setprecision(2)
                 << std::setw(14) << left << get<0>(p)
                 << std::setw(14) << left << get<1>(p)
                 << std::setw(14) << left << get<2>(p)
                 << std::setw(14) << left << get<3>(p)
                 << std::setw(18) << left << get<4>(p)
                 << std::setw(18) << left << get<5>(p)
                 << std::setw(14) << left << get<6>(p) << endl;
        }
    }
};

// ---------------------------------------------------------------------------

/**
 * @class PreemptivePriority
 * @brief Implements Preemptive Priority CPU scheduling.
 *
 * When a new process arrives with a strictly higher priority (lower number)
 * than the currently running process, the CPU is immediately taken away and
 * given to the new process. The preempted process re-enters the ready queue
 * with its remaining burst time.
 *
 * Uses an event-driven simulation: events are process arrivals and process
 * completions, so the clock jumps directly between events without simulating
 * every unit of time.
 *
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @tparam P Data type of Priority (lower number = higher urgency)
 */
template <typename S, typename T, typename E, typename P>
class PreemptivePriority {
    /** Input: (PID, arrival, burst, priority) */
    vector<tuple<S, T, E, P>> processes;

    /** Result: (PID, arrival, burst, priority, CT, TAT, WT) */
    vector<tuple<S, T, E, P, double, double, double>> result;

    /** Guard against duplicate process IDs */
    unordered_set<S> idList;

 public:
    /**
     * @brief Adds a process to the scheduler.
     * @param id      Unique process identifier
     * @param arrival Arrival time
     * @param burst   Total CPU burst time required
     * @param priority Priority value (lower number = higher urgency)
     * @returns void
     */
    void addProcess(S id, T arrival, E burst, P priority) {
        if (idList.find(id) == idList.end()) {
            processes.emplace_back(id, arrival, burst, priority);
            idList.insert(id);
        }
    }

    /**
     * @brief Runs the Preemptive Priority scheduling algorithm.
     *
     * @details Event-driven algorithm:
     * 1. Sort processes by arrival time.
     * 2. Maintain `rem[]` = remaining burst times, and a min-heap ready queue.
     * 3. At each iteration:
     *    a. Admit all processes whose arrival <= current time t.
     *    b. If CPU is idle and queue is empty, advance t to the next arrival.
     *    c. Check if a higher-priority process in the queue should preempt the
     *       current one. If so, push the current process back and switch.
     *    d. Compute the next event: min(next arrival time, finish time of
     *       current process). Run until that event; advance t.
     *    e. If the current process finishes, record its CT, TAT, WT.
     *
     * @returns Vector of 7-tuples with scheduling metrics (sorted by arrival).
     */
    vector<tuple<S, T, E, P, double, double, double>> scheduleForPP() {
        uint32_t n = static_cast<uint32_t>(processes.size());
        if (n == 0) {
            return result;
        }

        std::sort(processes.begin(), processes.end(), sortByArrival<S, T, E, P>);

        vector<double> rem(n);
        for (uint32_t i = 0; i < n; i++) {
            rem[i] = static_cast<double>(get<2>(processes[i]));
        }
        vector<double> ct(n, 0.0);

        // Ready queue: (priority, arrival, sorted-index)
        using Entry = tuple<P, T, uint32_t>;
        auto cmp = [](const Entry& a, const Entry& b) {
            if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
            if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
            return get<2>(a) > get<2>(b);
        };
        priority_queue<Entry, vector<Entry>, decltype(cmp)> rq(cmp);

        const double INF = std::numeric_limits<double>::infinity();
        double t = 0.0;
        uint32_t nextToArrive = 0;
        uint32_t done = 0;
        int32_t current = -1;  ///< index of currently running process (-1 = idle)

        while (done < n) {
            // 1. Admit all arrived processes
            while (nextToArrive < n &&
                   static_cast<double>(get<1>(processes[nextToArrive])) <= t) {
                rq.emplace(get<3>(processes[nextToArrive]),
                           get<1>(processes[nextToArrive]), nextToArrive);
                nextToArrive++;
            }

            // 2. If idle and nothing ready, fast-forward to next arrival
            if (current == -1 && rq.empty()) {
                t = static_cast<double>(get<1>(processes[nextToArrive]));
                continue;
            }

            // 3. Check for preemption or initial assignment
            if (!rq.empty()) {
                P topPri = get<0>(rq.top());
                P curPri = (current == -1)
                               ? std::numeric_limits<P>::max()
                               : get<3>(processes[current]);
                if (topPri < curPri) {
                    // Higher-priority process available — preempt or assign
                    if (current != -1) {
                        // Push current back with updated remaining burst
                        // (We track rem[] separately, so just push the entry)
                        rq.emplace(get<3>(processes[current]),
                                   get<1>(processes[current]),
                                   static_cast<uint32_t>(current));
                    }
                    auto [p, a, idx] = rq.top();
                    rq.pop();
                    current = static_cast<int32_t>(idx);
                }
            }

            // 4. Determine next event time
            double nextArrivalTime = (nextToArrive < n)
                                         ? static_cast<double>(
                                               get<1>(processes[nextToArrive]))
                                         : INF;
            double nextFinishTime = t + rem[current];
            double nextEvent = std::min(nextArrivalTime, nextFinishTime);

            // 5. Advance clock and reduce remaining burst
            double elapsed = nextEvent - t;
            rem[current] -= elapsed;
            t = nextEvent;

            // 6. Check if current process has finished
            if (rem[current] <= 0.0) {
                ct[current] = t;
                done++;
                current = -1;
            }
        }

        // Build result vector (preserves sorted-by-arrival order)
        result.resize(n);
        for (uint32_t i = 0; i < n; i++) {
            double arrival = static_cast<double>(get<1>(processes[i]));
            double burst   = static_cast<double>(get<2>(processes[i]));
            double tat     = ct[i] - arrival;
            double wt      = tat - burst;
            result[i] = make_tuple(get<0>(processes[i]), get<1>(processes[i]),
                                   get<2>(processes[i]), get<3>(processes[i]),
                                   ct[i], tat, wt);
        }
        return result;
    }

    /**
     * @brief Prints the scheduling table to standard output.
     * @returns void
     */
    void printResult() const {
        cout << std::setw(14) << left << "Process ID"
             << std::setw(14) << left << "Arrival"
             << std::setw(14) << left << "Burst"
             << std::setw(14) << left << "Priority"
             << std::setw(18) << left << "Completion Time"
             << std::setw(18) << left << "Turnaround Time"
             << std::setw(14) << left << "Waiting Time" << endl;
        for (const auto& p : result) {
            cout << std::fixed << std::setprecision(2)
                 << std::setw(14) << left << get<0>(p)
                 << std::setw(14) << left << get<1>(p)
                 << std::setw(14) << left << get<2>(p)
                 << std::setw(14) << left << get<3>(p)
                 << std::setw(18) << left << get<4>(p)
                 << std::setw(18) << left << get<5>(p)
                 << std::setw(14) << left << get<6>(p) << endl;
        }
    }
};

}  // namespace priority_scheduling
}  // namespace cpu_scheduling_algorithms

// ---------------------------------------------------------------------------
// Self-tests
// ---------------------------------------------------------------------------

/**
 * @brief Self-test implementations
 *
 * Test 1 – Non-preemptive, GFG example (different arrival times):
 *   P1(arr=0, burst=4, pri=2), P2(arr=1, burst=2, pri=1), P3(arr=2,burst=6,pri=3)
 *   Expected: P1 CT=4 WT=0, P2 CT=6 WT=3, P3 CT=12 WT=4
 *
 * Test 2 – Non-preemptive, single process:
 *   CT = arrival + burst, TAT = burst, WT = 0
 *
 * Test 3 – Non-preemptive, duplicate PID guard.
 *
 * Test 4 – Preemptive, different arrival times (from GFG screenshot):
 *   P1(arr=0,burst=6,pri=2), P2(arr=1,burst=4,pri=1), P3(arr=2,burst=5,pri=3)
 *   Expected: P1 CT=10 WT=4, P2 CT=5 WT=0, P3 CT=15 WT=8
 *
 * Test 5 – Preemptive, same arrival times:
 *   P1(arr=0,burst=7,pri=2), P2(arr=0,burst=4,pri=3), P3(arr=0,burst=6,pri=1)
 *   P3(pri=1) runs first → CT=6; P1(pri=2) next → CT=13; P2(pri=3) last → CT=17
 *
 * Test 6 – Preemptive, single process: WT = 0.
 *
 * @returns void
 */
static void test() {
    using namespace cpu_scheduling_algorithms::priority_scheduling;

    // -------------------------------------------------------------------
    // Test 1: Non-preemptive, GFG example
    // Trace: t=0 P1 starts (only arrived process); P1 finishes at t=4.
    //        t=4 rq={P2(pri1),P3(pri3)} → P2 runs; P2 finishes at t=6.
    //        t=6 rq={P3} → P3 runs; P3 finishes at t=12.
    // -------------------------------------------------------------------
    {
        NonPreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(1, 0, 4, 2);
        sched.addProcess(2, 1, 2, 1);
        sched.addProcess(3, 2, 6, 3);
        auto res = sched.scheduleForNPP();

        // Sorted by arrival: P1=idx0, P2=idx1, P3=idx2
        assert(get<4>(res[0]) == 4.0);   // P1 CT
        assert(get<5>(res[0]) == 4.0);   // P1 TAT
        assert(get<6>(res[0]) == 0.0);   // P1 WT

        assert(get<4>(res[1]) == 6.0);   // P2 CT
        assert(get<5>(res[1]) == 5.0);   // P2 TAT
        assert(get<6>(res[1]) == 3.0);   // P2 WT

        assert(get<4>(res[2]) == 12.0);  // P3 CT
        assert(get<5>(res[2]) == 10.0);  // P3 TAT
        assert(get<6>(res[2]) == 4.0);   // P3 WT

        // Waiting time is never negative
        for (const auto& p : res) assert(get<6>(p) >= 0.0);
    }

    // -------------------------------------------------------------------
    // Test 2: Non-preemptive, single process
    // -------------------------------------------------------------------
    {
        NonPreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(7, 5, 3, 1);
        auto res = sched.scheduleForNPP();

        assert(res.size() == 1);
        assert(get<4>(res[0]) == 8.0);  // CT  = 5 + 3
        assert(get<5>(res[0]) == 3.0);  // TAT = 3
        assert(get<6>(res[0]) == 0.0);  // WT  = 0
    }

    // -------------------------------------------------------------------
    // Test 3: Non-preemptive, duplicate PID — second add is a no-op
    // -------------------------------------------------------------------
    {
        NonPreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(1, 0, 5, 1);
        sched.addProcess(1, 0, 99, 1);  // duplicate
        auto res = sched.scheduleForNPP();

        assert(res.size() == 1);
        assert(get<2>(res[0]) == 5);  // original burst preserved
    }

    // -------------------------------------------------------------------
    // Test 4: Preemptive, different arrival times (GFG screenshot)
    // Trace:
    //   t=0: P1 admitted, runs. rem[P1]=6
    //   t=1: P2 arrives (pri=1) < P1(pri=2) → preempt. P2 runs.
    //   t=2: P3 arrives (pri=3) > P2(pri=1) → no preemption. P2 keeps running.
    //   t=5: P2 finishes (CT=5). rq={P1(rem5),P3}. P1(pri=2) < P3(pri=3) → P1 runs.
    //   t=10: P1 finishes (CT=10). P3 runs.
    //   t=15: P3 finishes (CT=15).
    // -------------------------------------------------------------------
    {
        PreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(1, 0, 6, 2);
        sched.addProcess(2, 1, 4, 1);
        sched.addProcess(3, 2, 5, 3);
        auto res = sched.scheduleForPP();

        // Sorted by arrival: P1=idx0, P2=idx1, P3=idx2
        assert(get<4>(res[0]) == 10.0);  // P1 CT
        assert(get<6>(res[0]) == 4.0);   // P1 WT

        assert(get<4>(res[1]) == 5.0);   // P2 CT
        assert(get<6>(res[1]) == 0.0);   // P2 WT

        assert(get<4>(res[2]) == 15.0);  // P3 CT
        assert(get<6>(res[2]) == 8.0);   // P3 WT

        for (const auto& p : res) assert(get<6>(p) >= 0.0);
    }

    // -------------------------------------------------------------------
    // Test 5: Preemptive, same arrival time
    // P3(pri=1) highest → runs 0-6 (CT=6).
    // P1(pri=2) next   → runs 6-13 (CT=13).
    // P2(pri=3) last   → runs 13-17 (CT=17).
    // -------------------------------------------------------------------
    {
        PreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(1, 0, 7, 2);
        sched.addProcess(2, 0, 4, 3);
        sched.addProcess(3, 0, 6, 1);
        auto res = sched.scheduleForPP();

        // Sorted by (arrival, priority, PID): P3(pri1)=idx0, P1(pri2)=idx1, P2(pri3)=idx2
        assert(get<4>(res[0]) == 6.0);   // P3 CT
        assert(get<6>(res[0]) == 0.0);   // P3 WT

        assert(get<4>(res[1]) == 13.0);  // P1 CT
        assert(get<6>(res[1]) == 6.0);   // P1 WT

        assert(get<4>(res[2]) == 17.0);  // P2 CT
        assert(get<6>(res[2]) == 13.0);  // P2 WT
    }

    // -------------------------------------------------------------------
    // Test 6: Preemptive, single process — no waiting, no preemption
    // -------------------------------------------------------------------
    {
        PreemptivePriority<uint32_t, uint32_t, uint32_t, uint32_t> sched;
        sched.addProcess(5, 3, 8, 1);
        auto res = sched.scheduleForPP();

        assert(res.size() == 1);
        assert(get<4>(res[0]) == 11.0);  // CT = 3 + 8
        assert(get<5>(res[0]) == 8.0);   // TAT = 8
        assert(get<6>(res[0]) == 0.0);   // WT  = 0
    }

    cout << "All tests have successfully passed!" << endl;
}

/**
 * @brief Entry point of the program
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // -------------------------------------------------------------------
    // Demo 1: Non-preemptive Priority Scheduling (GFG example)
    //   P1(arr=0,burst=4,pri=2), P2(arr=1,burst=2,pri=1), P3(arr=2,burst=6,pri=3)
    // -------------------------------------------------------------------
    cout << "\n--- Non-Preemptive Priority Scheduling Demo ---\n";
    cpu_scheduling_algorithms::priority_scheduling::NonPreemptivePriority<
        uint32_t, uint32_t, uint32_t, uint32_t>
        npp;
    npp.addProcess(1, 0, 4, 2);
    npp.addProcess(2, 1, 2, 1);
    npp.addProcess(3, 2, 6, 3);
    npp.scheduleForNPP();
    npp.printResult();

    // -------------------------------------------------------------------
    // Demo 2: Preemptive Priority Scheduling (different arrival times)
    //   P1(arr=0,burst=6,pri=2), P2(arr=1,burst=4,pri=1), P3(arr=2,burst=5,pri=3)
    // -------------------------------------------------------------------
    cout << "\n--- Preemptive Priority Scheduling Demo ---\n";
    cpu_scheduling_algorithms::priority_scheduling::PreemptivePriority<
        uint32_t, uint32_t, uint32_t, uint32_t>
        pp;
    pp.addProcess(1, 0, 6, 2);
    pp.addProcess(2, 1, 4, 1);
    pp.addProcess(3, 2, 5, 3);
    pp.scheduleForPP();
    pp.printResult();

    return 0;
}
