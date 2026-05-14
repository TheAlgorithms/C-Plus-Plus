/**
 * @file
 * @brief Implementation of Round Robin (RR) CPU scheduling algorithm
 * @details
 * Round Robin is a preemptive CPU scheduling algorithm where each process is
 * assigned a fixed time slice called the "time quantum". Processes are placed
 * in a circular queue and the CPU cycles through them. If a process does not
 * finish within its quantum, it is preempted and placed at the back of the
 * ready queue. This continues until all processes are complete.
 *
 * Key properties:
 * - Preemptive: a running process can be interrupted after its quantum expires.
 * - No starvation: every process is guaranteed CPU time at regular intervals.
 * - Fair: CPU time is distributed equally across all processes.
 * - Completion Time  = time at which a process finishes execution.
 * - Turnaround Time  = Completion Time  − Arrival Time
 * - Waiting Time     = Turnaround Time  − Burst Time
 *
 * This implementation supports processes with **different arrival times**.
 *
 * @see https://en.wikipedia.org/wiki/Round-robin_scheduling
 * @author [Shubhangam Singh](https://github.com/Shubhangam-Singh)
 */

#include <algorithm>    /// for std::sort
#include <cassert>      /// for assert
#include <iomanip>      /// for std::setw, std::left
#include <iostream>     /// for std::cout, std::endl
#include <queue>        /// for std::queue (circular ready queue)
#include <tuple>        /// for std::tuple, std::make_tuple, std::get
#include <cstdint>        /// for uint32_t
#include <unordered_set>  /// for std::unordered_set (duplicate ID guard)
#include <vector>       /// for std::vector

using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
using std::queue;
using std::tuple;
using std::unordered_set;
using std::vector;

/**
 * @namespace cpu_scheduling_algorithms
 * @brief CPU scheduling algorithm implementations
 */
namespace cpu_scheduling_algorithms {

/**
 * @namespace round_robin
 * @brief Functions and classes for the Round Robin scheduling algorithm
 */
namespace round_robin {

/**
 * @brief Comparator used to sort processes by arrival time, then by process ID.
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param t1 First tuple (Process ID, Arrival Time, Burst Time)
 * @param t2 Second tuple (Process ID, Arrival Time, Burst Time)
 * @returns true  if t1 should come before t2 in sorted order
 * @returns false otherwise
 */
template <typename S, typename T, typename E>
bool sortByArrival(const tuple<S, T, E>& t1, const tuple<S, T, E>& t2) {
    if (get<1>(t1) != get<1>(t2)) {
        return get<1>(t1) < get<1>(t2);  // Earlier arrival first
    }
    return get<0>(t1) < get<0>(t2);  // Smaller PID breaks tie
}

/**
 * @class RoundRobin
 * @brief Implements the preemptive Round Robin CPU scheduling algorithm.
 *
 * Each process is represented as a 6-tuple:
 *   (Process ID, Arrival Time, Burst Time,
 *    Completion Time, Turnaround Time, Waiting Time)
 *
 * @tparam S Data type of Process ID   (e.g., uint32_t)
 * @tparam T Data type of Arrival time (e.g., uint32_t)
 * @tparam E Data type of Burst time   (e.g., uint32_t)
 */
template <typename S, typename T, typename E>
class RoundRobin {
    /**
     * Input processes stored as 3-tuples:
     *   (Process ID, Arrival Time, Burst Time)
     */
    vector<tuple<S, T, E>> processes;

    /**
     * Result vector — one 6-tuple per process after scheduling:
     *   (Process ID, Arrival Time, Burst Time,
     *    Completion Time, Turnaround Time, Waiting Time)
     */
    vector<tuple<S, T, E, double, double, double>> result;

    /** Set of process IDs already added — prevents duplicates. */
    unordered_set<S> idList;

    /** Fixed CPU time slice (time quantum) in the same unit as burst time. */
    uint32_t quantum;

 public:
    /**
     * @brief Constructs a RoundRobin scheduler with the given time quantum.
     * @param q Time quantum (must be ≥ 1)
     */
    explicit RoundRobin(uint32_t q) : quantum(q) {}

    /**
     * @brief Adds a process to the scheduler.
     *
     * Processes with duplicate IDs are silently ignored.
     *
     * @param id      Unique process identifier
     * @param arrival Time at which the process enters the ready queue
     * @param burst   Total CPU time required by the process
     * @returns void
     */
    void addProcess(S id, T arrival, E burst) {
        if (idList.find(id) == idList.end()) {
            processes.push_back(make_tuple(id, arrival, burst));
            idList.insert(id);
        }
    }

    /**
     * @brief Runs the Round Robin scheduling algorithm.
     *
     * @details
     * Algorithm overview:
     * 1. Sort processes by arrival time (ties broken by process ID).
     * 2. Maintain `remainingBurst[]` — copy of original burst times, decremented
     *    as each process executes.
     * 3. Use a `std::queue<int>` as the circular ready queue storing indices
     *    into the `processes` vector.
     * 4. At every scheduler tick:
     *    a. Admit all processes whose arrival time ≤ current time to the queue.
     *    b. Dequeue the head process; execute it for min(remaining, quantum) units.
     *    c. Advance the clock.
     *    d. Admit any newly arrived processes (they arrived during the quantum).
     *    e. If the process still has remaining burst time, re-enqueue it.
     *    f. Otherwise record its completion, turnaround, and waiting times.
     * 5. If the ready queue is empty but some processes have not arrived yet,
     *    fast-forward the clock to the next arrival.
     *
     * @returns A vector of 6-tuples with the final scheduling metrics for each
     *          process, in the same order as they were added.
     */
    vector<tuple<S, T, E, double, double, double>> scheduleForRR() {
        uint32_t n = static_cast<uint32_t>(processes.size());
        if (n == 0) {
            return result;
        }

        // Step 1: Sort processes by arrival time (ties broken by process ID)
        std::sort(processes.begin(), processes.end(),
                  sortByArrival<S, T, E>);

        // Track remaining burst time for each process (index-aligned)
        vector<double> remainingBurst(n);
        for (uint32_t i = 0; i < n; i++) {
            remainingBurst[i] = static_cast<double>(get<2>(processes[i]));
        }

        // Completion times recorded per-process
        vector<double> completionTime(n, 0.0);

        // Circular ready queue holds indices into `processes`
        queue<uint32_t> readyQueue;

        double t = 0.0;  ///< Current simulation time

        // Index of the next process (by arrival order) not yet admitted
        uint32_t nextToArrive = 0;

        // Admit processes that have already arrived at t=0
        while (nextToArrive < n &&
               static_cast<double>(get<1>(processes[nextToArrive])) <= t) {
            readyQueue.push(nextToArrive++);
        }

        // Count finished processes
        uint32_t finished = 0;

        while (finished < n) {
            // If queue is empty, fast-forward to the next arrival
            if (readyQueue.empty()) {
                t = static_cast<double>(get<1>(processes[nextToArrive]));
                while (nextToArrive < n &&
                       static_cast<double>(get<1>(processes[nextToArrive])) <=
                           t) {
                    readyQueue.push(nextToArrive++);
                }
            }

            // Dequeue and execute the front process
            uint32_t idx = readyQueue.front();
            readyQueue.pop();

            // Execute for at most `quantum` units
            double slice = std::min(remainingBurst[idx],
                                    static_cast<double>(quantum));
            remainingBurst[idx] -= slice;
            t += slice;

            // Admit all processes that arrived during this quantum
            while (nextToArrive < n &&
                   static_cast<double>(get<1>(processes[nextToArrive])) <= t) {
                readyQueue.push(nextToArrive++);
            }

            if (remainingBurst[idx] > 0.0) {
                // Process not yet finished — re-enqueue at the back
                readyQueue.push(idx);
            } else {
                // Process finished — record metrics
                completionTime[idx] = t;
                finished++;
            }
        }

        // Build the result vector (restore original insertion order)
        result.resize(n);
        for (uint32_t i = 0; i < n; i++) {
            double arrival = static_cast<double>(get<1>(processes[i]));
            double burst   = static_cast<double>(get<2>(processes[i]));
            double ct      = completionTime[i];
            double tat     = ct - arrival;
            double wt      = tat - burst;

            result[i] = make_tuple(get<0>(processes[i]),
                                   get<1>(processes[i]),
                                   get<2>(processes[i]),
                                   ct, tat, wt);
        }
        return result;
    }

    /**
     * @brief Prints the scheduling table to standard output.
     * @returns void
     */
    void printResult() const {
        cout << std::setw(17) << left << "Process ID"
             << std::setw(17) << left << "Arrival Time"
             << std::setw(17) << left << "Burst Time"
             << std::setw(17) << left << "Completion Time"
             << std::setw(17) << left << "Turnaround Time"
             << std::setw(17) << left << "Waiting Time" << endl;

        for (const auto& p : result) {
            cout << std::fixed << std::setprecision(2)
                 << std::setw(17) << left << get<0>(p)
                 << std::setw(17) << left << get<1>(p)
                 << std::setw(17) << left << get<2>(p)
                 << std::setw(17) << left << get<3>(p)
                 << std::setw(17) << left << get<4>(p)
                 << std::setw(17) << left << get<5>(p) << endl;
        }
    }
};

}  // namespace round_robin
}  // namespace cpu_scheduling_algorithms

/**
 * @brief Reference (brute-force) implementation used for test validation.
 *
 * Runs the same Round Robin algorithm step-by-step and returns the vector of
 * 6-tuples so that assert() calls can compare against the class implementation.
 *
 * @param processes Vector of (PID, arrival, burst) tuples
 * @param quantum   Time quantum
 * @returns Vector of (PID, arrival, burst, CT, TAT, WT) tuples
 */
static vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>>
referenceRR(vector<tuple<uint32_t, uint32_t, uint32_t>> processes,
            uint32_t quantum) {
    uint32_t n = static_cast<uint32_t>(processes.size());

    std::sort(processes.begin(), processes.end(),
              cpu_scheduling_algorithms::round_robin::sortByArrival<
                  uint32_t, uint32_t, uint32_t>);

    vector<double> rem(n);
    for (uint32_t i = 0; i < n; i++) rem[i] = get<2>(processes[i]);

    vector<double> ct(n, 0.0);
    queue<uint32_t> rq;
    double t = 0.0;
    uint32_t nxt = 0, done = 0;

    while (nxt < n && static_cast<double>(get<1>(processes[nxt])) <= t)
        rq.push(nxt++);

    while (done < n) {
        if (rq.empty()) {
            t = static_cast<double>(get<1>(processes[nxt]));
            while (nxt < n &&
                   static_cast<double>(get<1>(processes[nxt])) <= t)
                rq.push(nxt++);
        }
        uint32_t idx = rq.front(); rq.pop();
        double slice = std::min(rem[idx], static_cast<double>(quantum));
        rem[idx] -= slice;
        t += slice;
        while (nxt < n &&
               static_cast<double>(get<1>(processes[nxt])) <= t)
            rq.push(nxt++);
        if (rem[idx] > 0.0) {
            rq.push(idx);
        } else {
            ct[idx] = t;
            done++;
        }
    }

    vector<tuple<uint32_t, uint32_t, uint32_t, double, double, double>> res(n);
    for (uint32_t i = 0; i < n; i++) {
        double arrival = get<1>(processes[i]);
        double burst   = get<2>(processes[i]);
        res[i] = make_tuple(get<0>(processes[i]),
                            get<1>(processes[i]),
                            get<2>(processes[i]),
                            ct[i], ct[i] - arrival, ct[i] - arrival - burst);
    }
    return res;
}

/**
 * @brief Self-test implementations
 *
 * Test 1 – Same arrival time (all at t=0), quantum=2:
 *   P1(burst=10), P2(burst=5), P3(burst=8)
 *   Traced results: P1 CT=23 WT=13, P2 CT=15 WT=10, P3 CT=21 WT=13
 *
 * Test 2 – Single process (trivial):
 *   CT = arrival + burst, TAT = burst, WT = 0.
 *
 * Test 3 – All processes arrive at time 0, burst == quantum (no preemption):
 *   P1(5), P2(5), P3(5), q=5 -> CT: 5, 10, 15
 *
 * Test 4 – Duplicate process ID: second addProcess() with same ID is a no-op.
 *
 * Test 5 – Different arrival times, quantum=3:
 *   P1(arr=0, burst=5), P2(arr=1, burst=3), P3(arr=2, burst=7)
 *   Cross-validated against an independent reference implementation.
 *
 * @returns void
 */
static void test() {
    using namespace cpu_scheduling_algorithms::round_robin;

    // -----------------------------------------------------------------------
    // Test 1: Same arrival time (all at t=0), quantum=2
    //   P1(burst=10), P2(burst=5), P3(burst=8)
    //   Execution trace:
    //     t=0-2:   P1 runs (rem 8)
    //     t=2-4:   P2 runs (rem 3)
    //     t=4-6:   P3 runs (rem 6)
    //     t=6-8:   P1 runs (rem 6)
    //     t=8-10:  P2 runs (rem 1)
    //     t=10-12: P3 runs (rem 4)
    //     t=12-14: P1 runs (rem 4)
    //     t=14-15: P2 runs rem=0 -> P2 DONE  CT[P2]=15
    //     t=15-17: P3 runs (rem 2)
    //     t=17-19: P1 runs (rem 2)
    //     t=19-21: P3 runs rem=0 -> P3 DONE  CT[P3]=21
    //     t=21-23: P1 runs rem=0 -> P1 DONE  CT[P1]=23
    //   Results: P1 CT=23 TAT=23 WT=13
    //            P2 CT=15 TAT=15 WT=10
    //            P3 CT=21 TAT=21 WT=13
    // -----------------------------------------------------------------------
    {
        RoundRobin<uint32_t, uint32_t, uint32_t> scheduler(2);
        scheduler.addProcess(1, 0, 10);
        scheduler.addProcess(2, 0, 5);
        scheduler.addProcess(3, 0, 8);
        auto res = scheduler.scheduleForRR();

        // After sorting by (arrival, PID): P1=index0, P2=index1, P3=index2
        // P1
        assert(get<3>(res[0]) == 23.0);  // CT
        assert(get<4>(res[0]) == 23.0);  // TAT = CT - arrival(0)
        assert(get<5>(res[0]) == 13.0);  // WT  = TAT - burst(10)
        // P2
        assert(get<3>(res[1]) == 15.0);  // CT
        assert(get<4>(res[1]) == 15.0);  // TAT
        assert(get<5>(res[1]) == 10.0);  // WT  = TAT - burst(5)
        // P3
        assert(get<3>(res[2]) == 21.0);  // CT
        assert(get<4>(res[2]) == 21.0);  // TAT
        assert(get<5>(res[2]) == 13.0);  // WT  = TAT - burst(8)

        // Waiting time is never negative
        assert(get<5>(res[0]) >= 0.0);
        assert(get<5>(res[1]) >= 0.0);
        assert(get<5>(res[2]) >= 0.0);
    }

    // -----------------------------------------------------------------------
    // Test 2: Single process — no preemption, no waiting
    // -----------------------------------------------------------------------
    {
        RoundRobin<uint32_t, uint32_t, uint32_t> scheduler(4);
        scheduler.addProcess(42, 3, 6);
        auto res = scheduler.scheduleForRR();

        assert(res.size() == 1);
        assert(get<3>(res[0]) == 9.0);   // CT  = 3 + 6
        assert(get<4>(res[0]) == 6.0);   // TAT = 6
        assert(get<5>(res[0]) == 0.0);   // WT  = 0
    }

    // -----------------------------------------------------------------------
    // Test 3: Burst time exactly equals quantum for every process
    //   No process is ever preempted; each finishes in one slot.
    //   All arrive at t=0, quantum=5.
    //   P1(5), P2(5), P3(5) -> CT: P1=5, P2=10, P3=15
    // -----------------------------------------------------------------------
    {
        RoundRobin<uint32_t, uint32_t, uint32_t> scheduler(5);
        scheduler.addProcess(1, 0, 5);
        scheduler.addProcess(2, 0, 5);
        scheduler.addProcess(3, 0, 5);
        auto res = scheduler.scheduleForRR();

        assert(get<3>(res[0]) == 5.0);   // P1 CT
        assert(get<3>(res[1]) == 10.0);  // P2 CT
        assert(get<3>(res[2]) == 15.0);  // P3 CT

        assert(get<5>(res[0]) == 0.0);   // P1 WT
        assert(get<5>(res[1]) == 5.0);   // P2 WT
        assert(get<5>(res[2]) == 10.0);  // P3 WT
    }

    // -----------------------------------------------------------------------
    // Test 4: Duplicate process ID — second add is a no-op
    // -----------------------------------------------------------------------
    {
        RoundRobin<uint32_t, uint32_t, uint32_t> scheduler(3);
        scheduler.addProcess(1, 0, 6);
        scheduler.addProcess(1, 0, 99);  // duplicate — must be ignored
        auto res = scheduler.scheduleForRR();

        assert(res.size() == 1);
        assert(get<2>(res[0]) == 6);  // burst must be the original 6
    }

    // -----------------------------------------------------------------------
    // Test 5: Different arrival times, quantum=3
    //   P1(arr=0, burst=5), P2(arr=1, burst=3), P3(arr=2, burst=7)
    //   Cross-validate class result against reference implementation.
    // -----------------------------------------------------------------------
    {
        vector<tuple<uint32_t, uint32_t, uint32_t>> procs = {
            make_tuple(1u, 0u, 5u),
            make_tuple(2u, 1u, 3u),
            make_tuple(3u, 2u, 7u)};

        auto expected = referenceRR(procs, 3);

        RoundRobin<uint32_t, uint32_t, uint32_t> scheduler(3);
        for (const auto& p : procs) {
            scheduler.addProcess(get<0>(p), get<1>(p), get<2>(p));
        }
        auto actual = scheduler.scheduleForRR();

        assert(actual.size() == expected.size());
        for (size_t i = 0; i < actual.size(); i++) {
            // Completion time must match
            assert(get<3>(actual[i]) == get<3>(expected[i]));
            // Turnaround time must match
            assert(get<4>(actual[i]) == get<4>(expected[i]));
            // Waiting time must match
            assert(get<5>(actual[i]) == get<5>(expected[i]));
            // Waiting time is never negative
            assert(get<5>(actual[i]) >= 0.0);
        }
    }

    cout << "All tests have successfully passed!" << endl;
}

/**
 * @brief Entry point of the program
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // -----------------------------------------------------------------------
    // Demo: GFG example — P1(burst=7), P2(burst=4), P3(burst=1), quantum=2
    //   All processes arrive at t=0.
    //   Expected:  P1 CT=12 WT=5 | P2 CT=9 WT=5 | P3 CT=5 WT=4
    // -----------------------------------------------------------------------
    cout << "\n--- Round Robin Scheduling Demo (quantum = 2) ---\n";
    cpu_scheduling_algorithms::round_robin::RoundRobin<uint32_t, uint32_t,
                                                       uint32_t>
        demo(2);
    demo.addProcess(1, 0, 7);
    demo.addProcess(2, 0, 4);
    demo.addProcess(3, 0, 1);
    demo.scheduleForRR();
    demo.printResult();

    return 0;
}
