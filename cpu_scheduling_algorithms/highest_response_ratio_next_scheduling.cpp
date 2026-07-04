/**
 * @file
 * @brief Implementation of the Highest Response Ratio Next (HRRN) CPU
 * scheduling algorithm
 * @details
 * HRRN is a non-preemptive CPU scheduling algorithm that, at every
 * decision point, picks the process (among those that have already
 * arrived) with the highest "response ratio":
 *
 *      response_ratio = (waiting_time + burst_time) / burst_time
 *
 * where `waiting_time` is how long the process has been sitting in the
 * ready queue so far (current_time - arrival_time). HRRN is often
 * described as "SJF with aging": a process with a small burst time still
 * tends to win, but the longer any process waits the higher its ratio
 * climbs, so long jobs are never starved forever the way they can be
 * under plain SJF.
 *
 * Because the ratio depends on the current simulated time, it cannot be
 * precomputed once and dropped into a static priority queue the way SJF's
 * burst time can -- the ratio of every waiting process changes on every
 * tick. The implementation below therefore recomputes ratios for the
 * ready set at each decision point (this is the standard way HRRN is
 * implemented).
 * <a href="https://www.guru99.com/highest-response-ratio-next-scheduling.html">
 * detailed description on HRRN scheduling</a>
 *
 * @author [HRRN skeleton written for this conversation]
 */

#include <algorithm>      /// for std::sort
#include <cassert>        /// for assert
#include <cstdint>        /// for uint32_t
#include <iomanip>        /// for formatting the output
#include <iostream>       /// for IO operations
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
 * @namespace hrrn
 * @brief Functions for the Highest Response Ratio Next algorithm
 */
namespace hrrn {

using std::cout;
using std::endl;
using std::get;
using std::left;
using std::make_tuple;
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
 * @details Used only to decide the order in which processes become
 * available to the scheduler -- it has nothing to do with execution order,
 * which HRRN decides dynamically via response ratio.
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
 * @brief Computes the HRRN response ratio for a process, given the current
 * simulated time.
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param currentTime How much simulated time has elapsed so far
 * @param arrival The process's arrival time
 * @param burst The process's (total) burst time
 * @returns (waiting_time + burst_time) / burst_time as a double
 */
template <typename T, typename E>
double responseRatio(double currentTime, T arrival, E burst) {
    double waitingSoFar = currentTime - static_cast<double>(arrival);
    return (waitingSoFar + static_cast<double>(burst)) /
           static_cast<double>(burst);
}

/**
 * @class HRRN
 * @brief Class which implements the Highest Response Ratio Next scheduling
 * algorithm
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 */
template <typename S, typename T, typename E>
class HRRN {
    /// Raw (id, arrival, burst) triples exactly as submitted.
    vector<tuple<S, T, E>> processes{};

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
     * @brief Runs HRRN scheduling over every registered process.
     * @details We keep a `byArrival` list (sorted by arrival, tie -> id)
     * of processes not yet admitted, and a `ready` vector of processes
     * that HAVE arrived but not yet run. At every decision point we admit
     * everyone whose arrival time is at most the current simulated time,
     * then scan the ready set and run whichever process currently has the
     * highest response ratio (ties broken by earliest arrival, then
     * smallest ID). Once a process starts, it runs to completion --
     * HRRN, like SJF, is non-preemptive.
     * @returns Results in the order processes were executed.
     */
    vector<process_result_t<S, T, E>> scheduleForHRRN() {
        vector<process_result_t<S, T, E>> result;
        if (processes.empty()) {
            return result;
        }

        vector<tuple<S, T, E>> byArrival = processes;
        std::sort(byArrival.begin(), byArrival.end(), ArrivalOrder<S, T, E>());

        const size_t n = byArrival.size();
        vector<size_t> ready;  // indices into byArrival, arrived but not run
        size_t nextToArrive = 0;
        double currentTime = 0;

        auto admitArrived = [&]() {
            while (nextToArrive < n &&
                   get<1>(byArrival[nextToArrive]) <= currentTime) {
                ready.push_back(nextToArrive);
                ++nextToArrive;
            }
        };

        admitArrived();

        while (result.size() < n) {
            if (ready.empty()) {
                // CPU idle: nothing has arrived yet, jump the clock
                // forward to the next arrival instead of guessing.
                assert(nextToArrive < n);
                currentTime = get<1>(byArrival[nextToArrive]);
                admitArrived();
                continue;
            }

            // Find the ready process with the highest response ratio.
            size_t bestPos = 0;
            double bestRatio =
                responseRatio(currentTime, get<1>(byArrival[ready[0]]),
                              get<2>(byArrival[ready[0]]));

            for (size_t k = 1; k < ready.size(); ++k) {
                size_t idx = ready[k];
                double ratio =
                    responseRatio(currentTime, get<1>(byArrival[idx]),
                                  get<2>(byArrival[idx]));
                const auto& cur = byArrival[idx];
                const auto& best = byArrival[ready[bestPos]];

                bool better =
                    ratio > bestRatio ||
                    (ratio == bestRatio && get<1>(cur) < get<1>(best)) ||
                    (ratio == bestRatio && get<1>(cur) == get<1>(best) &&
                     get<0>(cur) < get<0>(best));

                if (better) {
                    bestRatio = ratio;
                    bestPos = k;
                }
            }

            size_t chosen = ready[bestPos];
            ready.erase(ready.begin() + static_cast<long>(bestPos));

            const auto& p = byArrival[chosen];
            currentTime += get<2>(p);

            // Anyone who arrived while `p` was running is now available
            // for the NEXT decision point.
            admitArrived();

            double completion = currentTime;
            double turnaround = completion - get<1>(p);
            double waiting = turnaround - get<2>(p);

            assert(turnaround >= get<2>(p));  // turnaround >= burst
            assert(waiting >= 0);             // waiting is never negative

            result.push_back(make_tuple(get<0>(p), get<1>(p), get<2>(p),
                                        completion, turnaround, waiting));
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
 * @brief Independent reference implementation, used only to check
 * HRRN::scheduleForHRRN() against in tests.
 * @details Deliberately structured differently from the class above: it
 * keeps a single `done` flag per process and, at every step, scans ALL
 * processes (not just an incrementally-admitted subset) to find the
 * highest-ratio process whose arrival time is already <= currentTime.
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival time
 * @tparam E Data type of Burst time
 * @param input A vector of (id, arrival, burst) tuples
 * @returns Results in the order processes were executed.
 */
template <typename S, typename T, typename E>
vector<process_result_t<S, T, E>> get_final_status(
    vector<tuple<S, T, E>> input) {
    const size_t n = input.size();
    vector<bool> done(n, false);
    vector<process_result_t<S, T, E>> result;
    result.reserve(n);

    double currentTime = 0;

    for (size_t scheduled = 0; scheduled < n; ++scheduled) {
        int best = -1;
        double bestRatio = 0.0;

        for (size_t i = 0; i < n; ++i) {
            if (done[i] || get<1>(input[i]) > currentTime) {
                continue;
            }
            double ratio =
                responseRatio(currentTime, get<1>(input[i]), get<2>(input[i]));

            if (best == -1 || ratio > bestRatio ||
                (ratio == bestRatio &&
                 get<1>(input[i]) < get<1>(input[best])) ||
                (ratio == bestRatio &&
                 get<1>(input[i]) == get<1>(input[best]) &&
                 get<0>(input[i]) < get<0>(input[best]))) {
                best = static_cast<int>(i);
                bestRatio = ratio;
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
            currentTime = nextArrival;
            --scheduled;
            continue;
        }

        done[best] = true;
        currentTime += get<2>(input[best]);
        double completion = currentTime;
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
    // Regression case: a classic textbook example with known results.
    //   P0: arrival 0, burst 9
    //   P1: arrival 1, burst 5
    //   P2: arrival 2, burst 3
    //   P3: arrival 3, burst 4
    // Only P0 has arrived at t=0, so it runs first (completes at t=9).
    // At t=9 the ratios are P1=2.6, P2=3.33, P3=2.5 -> P2 runs next
    // (completes at t=12). At t=12 the ratios are P1=3.2, P3=3.25 -> P3
    // runs next (completes at t=16), and P1 runs last (completes at t=21).
    // Expected waiting times: P0=0, P2=7, P3=9, P1=15.
    {
        HRRN<int, int, int> h;
        h.addProcess(0, 0, 9);
        h.addProcess(1, 1, 5);
        h.addProcess(2, 2, 3);
        h.addProcess(3, 3, 4);

        auto res = h.scheduleForHRRN();
        assert(res.size() == 4);

        assert(get<0>(res[0]) == 0);
        assert(get<3>(res[0]) == 9);
        assert(get<5>(res[0]) == 0);

        assert(get<0>(res[1]) == 2);
        assert(get<3>(res[1]) == 12);
        assert(get<5>(res[1]) == 7);

        assert(get<0>(res[2]) == 3);
        assert(get<3>(res[2]) == 16);
        assert(get<5>(res[2]) == 9);

        assert(get<0>(res[3]) == 1);
        assert(get<3>(res[3]) == 21);
        assert(get<5>(res[3]) == 15);
    }

    // A single process should just run immediately with zero waiting.
    {
        HRRN<int, int, int> h;
        h.addProcess(0, 5, 7);
        auto res = h.scheduleForHRRN();
        assert(res.size() == 1);
        assert(get<3>(res[0]) == 12);
        assert(get<5>(res[0]) == 0);
    }

    // Randomized cross-check against the independent oracle.
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> countDist(1, 10);
    std::uniform_int_distribution<int> timeDist(1, 15);

    for (int trial = 0; trial < 500; ++trial) {
        int n = countDist(eng);
        HRRN<int, int, int> readyQueue;
        vector<tuple<int, int, int>> input(n);

        for (int i = 0; i < n; ++i) {
            input[i] = make_tuple(i, timeDist(eng), timeDist(eng));
            readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]),
                                  get<2>(input[i]));
        }

        auto expected = get_final_status<int, int, int>(input);
        auto actual = readyQueue.scheduleForHRRN();
        assert(expected == actual);
    }

    cout << "All the tests have successfully passed!" << endl;
}

}  // namespace hrrn
}  // namespace scheduling

/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    scheduling::hrrn::test();
    return 0;
}