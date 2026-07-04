/**
 * @file
 * @brief Implementation of the Round Robin (RR) CPU scheduling algorithm
 * @details
 * Round Robin is a preemptive CPU scheduling algorithm. Every process in
 * the ready queue is given a fixed unit of CPU time called a "time
 * quantum". If a process does not finish within its quantum it is
 * preempted and placed at the back of the ready queue; processes that
 * arrive while another process is running are admitted to the ready
 * queue before the preempted process is placed back at the end (the
 * standard convention used by most textbooks and OS courses).
 * <a href="https://www.guru99.com/round-robin-scheduling.html">
 * detailed description on Round Robin scheduling</a>
 *
 * @author [Round Robin skeleton written for this conversation]
 */

#include <algorithm>      /// for std::sort
#include <cassert>        /// for assert
#include <cstdint>        /// for uint32_t
#include <deque>          /// for std::deque (the ready queue)
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
     * @namespace round_robin
     * @brief Functions for the Round Robin algorithm
     */
    namespace round_robin {

        using std::cout;
        using std::deque;
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
         * 3rd element: Burst time (the ORIGINAL, total burst time -- not the
         *              time remaining at any intermediate point)
         * 4th element: Completion time
         * 5th element: Turnaround time
         * 6th element: Waiting time
         */
        template <typename S, typename T, typename E>
        using process_result_t = tuple<S, T, E, double, double, double>;

        /**
         * @brief Orders raw (id, arrival, burst) tuples by arrival time, tie-broken
         * by process ID.
         * @details This single ordering is used everywhere admission decisions are
         * made (both in the scheduler and in the independent test oracle below) so
         * that simultaneous arrivals are always admitted in the same, consistent
         * order.
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
         * @class RoundRobin
         * @brief Class which implements the Round Robin scheduling algorithm
         * @tparam S Data type of Process ID
         * @tparam T Data type of Arrival time
         * @tparam E Data type of Burst time
         */
        template <typename S, typename T, typename E>
        class RoundRobin {
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
             * @brief Runs Round Robin scheduling with the given time quantum over
             * every registered process.
             * @details Processes are admitted to a FIFO ready queue strictly in
             * arrival order (ties broken by process ID). Whenever the running
             * process is preempted (its quantum expires before it finishes), any
             * process that arrived during that quantum is enqueued first, and the
             * preempted process is placed at the back of the queue afterwards --
             * this is what makes the scheduler "fair" instead of letting a
             * process that keeps getting preempted immediately cut back in line
             * ahead of everyone who arrived while it was running.
             * @param quantum The fixed time slice given to each process per turn.
             * Must be strictly greater than zero.
             * @returns Results in the order processes finished executing.
             */
            vector<process_result_t<S, T, E>> scheduleForRR(E quantum) {
                assert(quantum > 0);

                vector<process_result_t<S, T, E>> result;
                if (processes.empty()) {
                    return result;
                }

                vector<tuple<S, T, E>> byArrival = processes;
                std::sort(byArrival.begin(), byArrival.end(), ArrivalOrder<S, T, E>());

                const size_t n = byArrival.size();
                vector<E> remaining(n);
                for (size_t i = 0; i < n; ++i) {
                    remaining[i] = get<2>(byArrival[i]);
                }

                deque<size_t> ready;
                size_t nextToArrive = 0;
                double currentTime = 0;
                size_t completedCount = 0;

                // Admits every not-yet-admitted process whose arrival time is at
                // most `currentTime`, in (arrival, id) order.
                auto admitArrived = [&]() {
                    while (nextToArrive < n &&
                        get<1>(byArrival[nextToArrive]) <= currentTime) {
                        ready.push_back(nextToArrive);
                        ++nextToArrive;
                    }
                    };

                admitArrived();

                while (completedCount < n) {
                    if (ready.empty()) {
                        // CPU idle: nothing has arrived yet, jump the clock
                        // forward to the next arrival instead of guessing.
                        assert(nextToArrive < n);
                        currentTime = get<1>(byArrival[nextToArrive]);
                        admitArrived();
                        continue;
                    }

                    size_t idx = ready.front();
                    ready.pop_front();

                    E execTime = remaining[idx] < quantum ? remaining[idx] : quantum;
                    currentTime += execTime;
                    remaining[idx] -= execTime;

                    // Anyone who arrived during this time slice is admitted
                    // BEFORE the process we just ran gets a chance to re-queue.
                    admitArrived();

                    if (remaining[idx] == 0) {
                        const auto& p = byArrival[idx];
                        double completion = currentTime;
                        double turnaround = completion - get<1>(p);
                        double waiting = turnaround - get<2>(p);

                        assert(turnaround >= get<2>(p));  // turnaround >= burst
                        assert(waiting >= 0);              // waiting is never negative

                        result.push_back(make_tuple(get<0>(p), get<1>(p), get<2>(p),
                            completion, turnaround, waiting));
                        ++completedCount;
                    }
                    else {
                        ready.push_back(idx);
                    }
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
                    cout << std::setprecision(2) << std::fixed << std::setw(17)
                        << left << get<0>(process) << std::setw(17) << left
                        << get<1>(process) << std::setw(17) << left
                        << get<2>(process) << std::setw(17) << left
                        << get<3>(process) << std::setw(17) << left
                        << get<4>(process) << std::setw(17) << left
                        << get<5>(process) << endl;
                }
            }
        };

        /**
         * @brief Independent unit-tick reference implementation, used only to
         * check RoundRobin::scheduleForRR() against in tests.
         * @details Instead of jumping the clock forward by a whole quantum at a
         * time, this oracle advances time one unit at a time and re-evaluates
         * arrivals and quantum expiry after every single tick. It is far less
         * efficient, but its correctness is easy to see by inspection, which
         * makes it a trustworthy check for the optimized implementation above.
         * @tparam S Data type of Process ID
         * @tparam T Data type of Arrival time
         * @tparam E Data type of Burst time
         * @param input A vector of (id, arrival, burst) tuples
         * @param quantum The fixed time slice given to each process per turn
         * @returns Results in the order processes finished executing.
         */
        template <typename S, typename T, typename E>
        vector<process_result_t<S, T, E>> get_final_status(
            vector<tuple<S, T, E>> input, E quantum) {
            vector<tuple<S, T, E>> byArrival = input;
            std::sort(byArrival.begin(), byArrival.end(), ArrivalOrder<S, T, E>());

            const size_t n = byArrival.size();
            vector<E> remaining(n);
            for (size_t i = 0; i < n; ++i) {
                remaining[i] = get<2>(byArrival[i]);
            }

            vector<process_result_t<S, T, E>> result;
            if (n == 0) {
                return result;
            }

            deque<size_t> ready;
            size_t nextToArrive = 0;
            double time = 0;
            size_t completedCount = 0;
            int running = -1;
            E ticksUsed = 0;

            auto admitArrived = [&]() {
                while (nextToArrive < n && get<1>(byArrival[nextToArrive]) <= time) {
                    ready.push_back(nextToArrive);
                    ++nextToArrive;
                }
                };

            admitArrived();

            while (completedCount < n) {
                if (running == -1) {
                    if (ready.empty()) {
                        // CPU idle for this tick.
                        ++time;
                        admitArrived();
                        continue;
                    }
                    running = static_cast<int>(ready.front());
                    ready.pop_front();
                    ticksUsed = 0;
                }

                // Execute one tick of the running process.
                --remaining[running];
                ++ticksUsed;
                ++time;

                admitArrived();

                if (remaining[running] == 0) {
                    const auto& p = byArrival[running];
                    double completion = time;
                    double turnaround = completion - get<1>(p);
                    double waiting = turnaround - get<2>(p);
                    result.push_back(make_tuple(get<0>(p), get<1>(p), get<2>(p),
                        completion, turnaround, waiting));
                    ++completedCount;
                    running = -1;
                }
                else if (ticksUsed == quantum) {
                    ready.push_back(static_cast<size_t>(running));
                    running = -1;
                }
            }

            return result;
        }

        /**
         * @brief Self-test implementations
         * @returns void
         */
        static void test() {
            // Regression case: classic textbook example.
            // P0 arrives at 0 with burst 5, P1 arrives at 1 with burst 3,
            // P2 arrives at 2 with burst 1, quantum = 2.
            // Expected trace (well-known result for this exact example):
            //   0-2: P0 (rem 3)          | ready after: P1, P2, P0
            //   2-4: P1 (rem 1)          | ready after: P2, P0, P1
            //   4-5: P2 (rem 0) -> done at t=5
            //   5-7: P0 (rem 1)          | ready after: P1, P0
            //   7-8: P1 (rem 0) -> done at t=8
            //   8-9: P0 (rem 0) -> done at t=9
            {
                RoundRobin<int, int, int> rr;
                rr.addProcess(0, 0, 5);
                rr.addProcess(1, 1, 3);
                rr.addProcess(2, 2, 1);
                auto res = rr.scheduleForRR(2);

                assert(res.size() == 3);
                // Completion order: P2, then P1, then P0.
                assert(get<0>(res[0]) == 2);
                assert(get<3>(res[0]) == 5);

                assert(get<0>(res[1]) == 1);
                assert(get<3>(res[1]) == 8);

                assert(get<0>(res[2]) == 0);
                assert(get<3>(res[2]) == 9);
            }

            // A process that never gets preempted (burst <= quantum) should
            // behave exactly like FCFS with respect to that single process.
            {
                RoundRobin<int, int, int> rr;
                rr.addProcess(0, 0, 4);
                auto res = rr.scheduleForRR(10);
                assert(res.size() == 1);
                assert(get<3>(res[0]) == 4);
                assert(get<5>(res[0]) == 0);  // no waiting, nothing else queued
            }

            // Randomized cross-check against the independent unit-tick oracle,
            // across a range of quanta.
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_int_distribution<int> countDist(1, 10);
            std::uniform_int_distribution<int> timeDist(1, 15);
            std::uniform_int_distribution<int> quantumDist(1, 6);

            for (int trial = 0; trial < 500; ++trial) {
                int n = countDist(eng);
                int quantum = quantumDist(eng);

                RoundRobin<int, int, int> rr;
                vector<tuple<int, int, int>> input(n);

                for (int i = 0; i < n; ++i) {
                    input[i] = make_tuple(i, timeDist(eng), timeDist(eng));
                    rr.addProcess(get<0>(input[i]), get<1>(input[i]),
                        get<2>(input[i]));
                }

                auto expected = get_final_status<int, int, int>(input, quantum);
                auto actual = rr.scheduleForRR(quantum);
                assert(expected == actual);
            }

            cout << "All the tests have successfully passed!" << endl;
        }

    }  // namespace round_robin
}  // namespace scheduling

/**
 * @brief Main function
 * @returns 0 on successful exit
 */
int main() {
    scheduling::round_robin::test();
    return 0;
}