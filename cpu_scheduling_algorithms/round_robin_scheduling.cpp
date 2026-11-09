/**
 * @file
 * @brief Implementation of [Round Robin (RR) CPU Scheduling
 * Algorithm](https://en.wikipedia.org/wiki/Round-robin_scheduling)
 * @details
 * Round Robin (RR) is a classic preemptive CPU scheduling algorithm designed
 * specifically for time-sharing systems. Each ready process is assigned a fixed
 * time slice called a **time quantum** in cyclic order.
 *
 * Algorithm workflow:
 * 1. Ready processes are queued in FIFO order based on their arrival times.
 * 2. The CPU allocates up to one time quantum to the process at the head of the
 * queue.
 * 3. If the process finishes execution within the time quantum, it is marked
 * complete and its completion, turnaround, and waiting times are recorded.
 * 4. If the process requires more time than the quantum, it is preempted and
 * pushed back to the tail of the ready queue after newly arrived processes.
 * 5. If the ready queue is empty while processes remain unarrived, the CPU
 * advances its clock to the next arrival time (accounting for CPU idle time).
 * 6. The cycle repeats until all processes complete.
 *
 * Performance Metrics Computed:
 * - **Completion Time (CT):** Timestamp when the process finishes execution.
 * - **Turnaround Time (TAT):** Total time taken from arrival to completion (TAT
 * = CT - AT).
 * - **Waiting Time (WT):** Total time spent waiting in the ready queue (WT =
 * TAT - BT).
 * - **Response Time (RT):** Time from arrival to first execution on the CPU (RT
 * = FirstCPU - AT).
 * - **Gantt Chart:** Chronological timeline slices representing CPU execution
 * history.
 *
 * Complexity:
 * - Time Complexity: \\(O(N \\log N + N \\cdot
 * \\frac{\\max(BT)}{\\text{quantum}})\\) where \\(N\\) is the number of
 * processes.
 * - Auxiliary Space Complexity: \\(O(N)\\) for ready queue and scheduling
 * status tracking.
 *
 * @author [Pruthvi Jadhav](https://github.com/pruthvi828)
 */

#include <algorithm>      /// for std::sort
#include <cassert>        /// for assert testing
#include <cmath>          /// for std::fabs
#include <cstdint>        /// for uint32_t, int64_t
#include <iomanip>        /// for std::setw, std::setprecision, std::fixed
#include <iostream>       /// for IO operations
#include <numeric>        /// for std::accumulate
#include <queue>          /// for std::queue
#include <unordered_set>  /// for std::unordered_set
#include <vector>         /// for std::vector

/**
 * @namespace cpu_scheduling_algorithms
 * @brief CPU Scheduling Algorithms
 */
namespace cpu_scheduling_algorithms {

/**
 * @namespace round_robin
 * @brief Functions and classes for Round Robin CPU scheduling
 */
namespace round_robin {

/**
 * @struct Process
 * @brief Represents a process with its metadata and computed scheduling metrics
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival Time
 * @tparam E Data type of Burst Time
 */
template <typename S = uint32_t, typename T = uint32_t, typename E = uint32_t>
struct Process {
    S id{};                       ///< Unique process identifier
    T arrival_time{};             ///< Timestamp when process arrives
    E burst_time{};               ///< Total CPU burst time needed
    E remaining_time{};           ///< Remaining CPU burst time
    double completion_time{0.0};  ///< Timestamp when process finishes
    double turnaround_time{0.0};  ///< Turnaround Time = Completion - Arrival
    double waiting_time{0.0};     ///< Waiting Time = Turnaround - Burst
    double response_time{0.0};    ///< Response Time = First Execution - Arrival
    int64_t first_execution_time{
        -1};  ///< Timestamp of first execution (-1 if never run)
};

/**
 * @struct GanttSlice
 * @brief Represents an individual execution window on the CPU timeline
 * @tparam S Data type of Process ID
 */
template <typename S = uint32_t>
struct GanttSlice {
    S process_id{};       ///< Process ID executed during this window
    double start_time{};  ///< Window start timestamp
    double end_time{};    ///< Window end timestamp
};

/**
 * @class RoundRobinScheduler
 * @brief Implementation of preemptive Round Robin scheduling engine
 * @tparam S Data type of Process ID
 * @tparam T Data type of Arrival Time
 * @tparam E Data type of Burst Time
 */
template <typename S = uint32_t, typename T = uint32_t, typename E = uint32_t>
class RoundRobinScheduler {
 private:
    std::vector<Process<S, T, E>> processes_;  ///< Registered processes
    std::unordered_set<S> registered_ids_;     ///< Set of unique process IDs
    std::vector<GanttSlice<S>> gantt_chart_;   ///< Generated Gantt chart slices
    bool is_scheduled_{false};  ///< Tracks whether scheduling has run

 public:
    /**
     * @brief Adds a new process to the scheduler
     * @param id Unique process identifier
     * @param arrival_time Timestamp when process arrives
     * @param burst_time Total CPU execution time required
     * @return true if process was successfully added
     * @return false if duplicate process ID or burst_time is 0
     */
    bool addProcess(S id, T arrival_time, E burst_time) {
        if (burst_time == 0 ||
            registered_ids_.find(id) != registered_ids_.end()) {
            return false;
        }

        Process<S, T, E> proc;
        proc.id = id;
        proc.arrival_time = arrival_time;
        proc.burst_time = burst_time;
        proc.remaining_time = burst_time;

        processes_.push_back(proc);
        registered_ids_.insert(id);
        is_scheduled_ = false;
        return true;
    }

    /**
     * @brief Clears all processes and resets scheduler state
     */
    void clear() {
        processes_.clear();
        registered_ids_.clear();
        gantt_chart_.clear();
        is_scheduled_ = false;
    }

    /**
     * @brief Executes the Round Robin scheduling algorithm
     * @param quantum Fixed time slice allocated to each process per round
     * @return std::vector<Process<S, T, E>> The scheduled processes with
     * complete metrics
     */
    std::vector<Process<S, T, E>> schedule(E quantum) {
        assert(quantum > 0 && "Time quantum must be strictly greater than 0");

        if (processes_.empty()) {
            is_scheduled_ = true;
            return processes_;
        }

        gantt_chart_.clear();

        // Sort processes initially by arrival time, using ID as tie-breaker
        std::sort(processes_.begin(), processes_.end(),
                  [](const Process<S, T, E>& a, const Process<S, T, E>& b) {
                      if (a.arrival_time != b.arrival_time) {
                          return a.arrival_time < b.arrival_time;
                      }
                      return a.id < b.id;
                  });

        const size_t total_processes = processes_.size();
        for (auto& p : processes_) {
            p.remaining_time = p.burst_time;
            p.first_execution_time = -1;
            p.completion_time = 0.0;
            p.turnaround_time = 0.0;
            p.waiting_time = 0.0;
            p.response_time = 0.0;
        }

        std::queue<size_t> ready_queue;
        double current_time = 0.0;
        size_t next_arrival_index = 0;
        size_t completed_count = 0;

        // Advance initial time to first arriving process if necessary
        if (next_arrival_index<total_processes&& static_cast<double>(
                processes_[next_arrival_index].arrival_time)>
                current_time) {
            current_time = static_cast<double>(
                processes_[next_arrival_index].arrival_time);
        }

        // Push all processes that have arrived at or before initial
        // current_time
        while (
            next_arrival_index < total_processes &&
            static_cast<double>(processes_[next_arrival_index].arrival_time) <=
                current_time) {
            ready_queue.push(next_arrival_index);
            next_arrival_index++;
        }

        while (completed_count < total_processes) {
            if (ready_queue.empty()) {
                // CPU idle: jump clock to the arrival time of the next
                // available process
                if (next_arrival_index < total_processes) {
                    current_time = static_cast<double>(
                        processes_[next_arrival_index].arrival_time);
                    while (next_arrival_index < total_processes &&
                           static_cast<double>(
                               processes_[next_arrival_index].arrival_time) <=
                               current_time) {
                        ready_queue.push(next_arrival_index);
                        next_arrival_index++;
                    }
                }
                continue;
            }

            size_t idx = ready_queue.front();
            ready_queue.pop();
            Process<S, T, E>& curr = processes_[idx];

            // Record response time on first CPU dispatch
            if (curr.first_execution_time == -1) {
                curr.first_execution_time = static_cast<int64_t>(current_time);
                curr.response_time =
                    current_time - static_cast<double>(curr.arrival_time);
            }

            E execution_slice = std::min(quantum, curr.remaining_time);
            double slice_start = current_time;
            current_time += static_cast<double>(execution_slice);
            curr.remaining_time -= execution_slice;

            // Log Gantt chart slice
            gantt_chart_.push_back({curr.id, slice_start, current_time});

            // Enqueue all processes that arrived while this process was
            // executing
            while (next_arrival_index < total_processes &&
                   static_cast<double>(
                       processes_[next_arrival_index].arrival_time) <=
                       current_time) {
                ready_queue.push(next_arrival_index);
                next_arrival_index++;
            }

            if (curr.remaining_time > 0) {
                // Preempt and requeue at the tail
                ready_queue.push(idx);
            } else {
                // Process finished execution
                curr.completion_time = current_time;
                curr.turnaround_time = curr.completion_time -
                                       static_cast<double>(curr.arrival_time);
                curr.waiting_time =
                    curr.turnaround_time - static_cast<double>(curr.burst_time);

                // Algorithmic Invariants
                assert(curr.turnaround_time >=
                       static_cast<double>(curr.burst_time));
                assert(curr.waiting_time >= 0.0);
                assert(curr.response_time >= 0.0);
                assert(
                    curr.completion_time >=
                    static_cast<double>(curr.arrival_time + curr.burst_time));

                completed_count++;
            }
        }

        is_scheduled_ = true;
        return processes_;
    }

    /**
     * @brief Computes average waiting time across all scheduled processes
     * @return double Average waiting time
     */
    double getAverageWaitingTime() const {
        assert(is_scheduled_ && !processes_.empty());
        double total_waiting = 0.0;
        for (const auto& p : processes_) {
            total_waiting += p.waiting_time;
        }
        return total_waiting / static_cast<double>(processes_.size());
    }

    /**
     * @brief Computes average turnaround time across all scheduled processes
     * @return double Average turnaround time
     */
    double getAverageTurnaroundTime() const {
        assert(is_scheduled_ && !processes_.empty());
        double total_tat = 0.0;
        for (const auto& p : processes_) {
            total_tat += p.turnaround_time;
        }
        return total_tat / static_cast<double>(processes_.size());
    }

    /**
     * @brief Computes average response time across all scheduled processes
     * @return double Average response time
     */
    double getAverageResponseTime() const {
        assert(is_scheduled_ && !processes_.empty());
        double total_response = 0.0;
        for (const auto& p : processes_) {
            total_response += p.response_time;
        }
        return total_response / static_cast<double>(processes_.size());
    }

    /**
     * @brief Retrieves the generated Gantt chart execution timeline
     * @return const std::vector<GanttSlice<S>>& Timeline of execution slices
     */
    const std::vector<GanttSlice<S>>& getGanttChart() const {
        return gantt_chart_;
    }

    /**
     * @brief Returns the list of processes and their computed metrics
     * @return const std::vector<Process<S, T, E>>& Process list
     */
    const std::vector<Process<S, T, E>>& getProcesses() const {
        return processes_;
    }

    /**
     * @brief Displays formatted tabular schedule report and Gantt timeline
     */
    void printSchedule() const {
        assert(is_scheduled_);

        std::cout << "\n=========================================="
                  << "==========================================\n";
        std::cout << std::setw(12) << std::left << "Process ID" << std::setw(15)
                  << std::left << "Arrival Time" << std::setw(14) << std::left
                  << "Burst Time" << std::setw(18) << std::left
                  << "Completion Time" << std::setw(18) << std::left
                  << "Turnaround Time" << std::setw(15) << std::left
                  << "Waiting Time" << std::setw(15) << std::left
                  << "Response Time" << "\n";
        std::cout << "------------------------------------------"
                  << "------------------------------------------\n";

        for (const auto& p : processes_) {
            std::cout << std::setw(12) << std::left << p.id << std::setw(15)
                      << std::left << p.arrival_time << std::setw(14)
                      << std::left << p.burst_time << std::setprecision(2)
                      << std::fixed << std::setw(18) << std::left
                      << p.completion_time << std::setw(18) << std::left
                      << p.turnaround_time << std::setw(15) << std::left
                      << p.waiting_time << std::setw(15) << std::left
                      << p.response_time << "\n";
        }

        std::cout << "------------------------------------------"
                  << "------------------------------------------\n";
        std::cout << "Average Waiting Time    : " << std::fixed
                  << std::setprecision(2) << getAverageWaitingTime() << "\n";
        std::cout << "Average Turnaround Time : " << std::fixed
                  << std::setprecision(2) << getAverageTurnaroundTime() << "\n";
        std::cout << "Average Response Time   : " << std::fixed
                  << std::setprecision(2) << getAverageResponseTime() << "\n\n";

        std::cout << "Gantt Chart Timeline:\n";
        for (const auto& slice : gantt_chart_) {
            std::cout << "[" << std::setprecision(0) << std::fixed
                      << slice.start_time << " - " << slice.end_time << ": P"
                      << slice.process_id << "] ";
        }
        std::cout << "\n=========================================="
                  << "==========================================\n\n";
    }
};

}  // namespace round_robin
}  // namespace cpu_scheduling_algorithms

/**
 * @brief Helper assertion comparing double equality with tolerance
 * @param a First value
 * @param b Second value
 * @param epsilon Allowed difference tolerance (default 1e-4)
 * @return true if values are within epsilon tolerance
 */
static inline bool is_approx_equal(double a, double b, double epsilon = 1e-4) {
    return std::fabs(a - b) < epsilon;
}

/**
 * @brief Self-test implementations verifying correctness across standard
 * textbook, edge, and boundary cases.
 */
static void test() {
    using cpu_scheduling_algorithms::round_robin::RoundRobinScheduler;

    // -------------------------------------------------------------
    // Test Case 1: Canonical Silberschatz OS Concepts Textbook Example
    // P1: AT=0, BT=24; P2: AT=0, BT=3; P3: AT=0, BT=3; Quantum = 4
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        scheduler.addProcess(1, 0, 24);
        scheduler.addProcess(2, 0, 3);
        scheduler.addProcess(3, 0, 3);

        auto results = scheduler.schedule(4);
        assert(results.size() == 3);

        // Map by ID for deterministic verification
        for (const auto& p : results) {
            if (p.id == 1) {
                assert(p.completion_time == 30.0);
                assert(p.turnaround_time == 30.0);
                assert(p.waiting_time == 6.0);
                assert(p.response_time == 0.0);
            } else if (p.id == 2) {
                assert(p.completion_time == 7.0);
                assert(p.turnaround_time == 7.0);
                assert(p.waiting_time == 4.0);
                assert(p.response_time == 4.0);
            } else if (p.id == 3) {
                assert(p.completion_time == 10.0);
                assert(p.turnaround_time == 10.0);
                assert(p.waiting_time == 7.0);
                assert(p.response_time == 7.0);
            }
        }

        assert(is_approx_equal(scheduler.getAverageWaitingTime(), 17.0 / 3.0));
        assert(
            is_approx_equal(scheduler.getAverageTurnaroundTime(), 47.0 / 3.0));
        std::cout << "[PASS] Test 1: Canonical Silberschatz Textbook "
                     "Verification Passed.\n";
    }

    // -------------------------------------------------------------
    // Test Case 2: Staggered Arrival Times
    // P1: AT=0, BT=5; P2: AT=1, BT=4; P3: AT=2, BT=2; P4: AT=4, BT=1; Quantum =
    // 2
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        scheduler.addProcess(1, 0, 5);
        scheduler.addProcess(2, 1, 4);
        scheduler.addProcess(3, 2, 2);
        scheduler.addProcess(4, 4, 1);

        auto results = scheduler.schedule(2);
        assert(results.size() == 4);

        for (const auto& p : results) {
            if (p.id == 1) {
                assert(p.completion_time == 12.0);
                assert(p.turnaround_time == 12.0);
                assert(p.waiting_time == 7.0);
                assert(p.response_time == 0.0);
            } else if (p.id == 2) {
                assert(p.completion_time == 11.0);
                assert(p.turnaround_time == 10.0);
                assert(p.waiting_time == 6.0);
                assert(p.response_time == 1.0);
            } else if (p.id == 3) {
                assert(p.completion_time == 6.0);
                assert(p.turnaround_time == 4.0);
                assert(p.waiting_time == 2.0);
                assert(p.response_time == 2.0);
            } else if (p.id == 4) {
                assert(p.completion_time == 9.0);
                assert(p.turnaround_time == 5.0);
                assert(p.waiting_time == 4.0);
                assert(p.response_time == 4.0);
            }
        }

        assert(is_approx_equal(scheduler.getAverageWaitingTime(), 19.0 / 4.0));
        assert(
            is_approx_equal(scheduler.getAverageTurnaroundTime(), 31.0 / 4.0));
        std::cout << "[PASS] Test 2: Staggered Arrival Times Passed.\n";
    }

    // -------------------------------------------------------------
    // Test Case 3: CPU Idle Periods (Gaps in Arrival Times)
    // P1: AT=0, BT=3; P2: AT=10, BT=4; Quantum = 2
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        scheduler.addProcess(1, 0, 3);
        scheduler.addProcess(2, 10, 4);

        auto results = scheduler.schedule(2);
        assert(results.size() == 2);

        for (const auto& p : results) {
            if (p.id == 1) {
                assert(p.completion_time == 3.0);
                assert(p.turnaround_time == 3.0);
                assert(p.waiting_time == 0.0);
                assert(p.response_time == 0.0);
            } else if (p.id == 2) {
                assert(p.completion_time == 14.0);
                assert(p.turnaround_time == 4.0);
                assert(p.waiting_time == 0.0);
                assert(p.response_time == 0.0);
            }
        }

        assert(is_approx_equal(scheduler.getAverageWaitingTime(), 0.0));
        assert(is_approx_equal(scheduler.getAverageTurnaroundTime(), 3.5));
        std::cout << "[PASS] Test 3: CPU Idle Gaps Passed.\n";
    }

    // -------------------------------------------------------------
    // Test Case 4: Single Process Boundary Case
    // P1: AT=0, BT=10; Quantum = 3
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        scheduler.addProcess(101, 0, 10);

        auto results = scheduler.schedule(3);
        assert(results.size() == 1);
        assert(results[0].completion_time == 10.0);
        assert(results[0].turnaround_time == 10.0);
        assert(results[0].waiting_time == 0.0);
        assert(results[0].response_time == 0.0);
        std::cout << "[PASS] Test 4: Single Process Boundary Passed.\n";
    }

    // -------------------------------------------------------------
    // Test Case 5: Quantum larger than all burst times (degenerates to FCFS)
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        scheduler.addProcess(1, 0, 4);
        scheduler.addProcess(2, 2, 6);
        scheduler.addProcess(3, 3, 2);

        auto results = scheduler.schedule(100);
        assert(results.size() == 3);

        // Under huge quantum, P1 runs 0-4, P2 runs 4-10, P3 runs 10-12
        for (const auto& p : results) {
            if (p.id == 1) {
                assert(p.completion_time == 4.0);
                assert(p.turnaround_time == 4.0);
                assert(p.waiting_time == 0.0);
            } else if (p.id == 2) {
                assert(p.completion_time == 10.0);
                assert(p.turnaround_time == 8.0);
                assert(p.waiting_time == 2.0);
            } else if (p.id == 3) {
                assert(p.completion_time == 12.0);
                assert(p.turnaround_time == 9.0);
                assert(p.waiting_time == 7.0);
            }
        }
        std::cout
            << "[PASS] Test 5: Large Quantum Degeneracy to FCFS Passed.\n";
    }

    // -------------------------------------------------------------
    // Test Case 6: Duplicate and Invalid Process Input Validation
    // -------------------------------------------------------------
    {
        RoundRobinScheduler<uint32_t, uint32_t, uint32_t> scheduler;
        assert(scheduler.addProcess(1, 0, 5) == true);
        assert(scheduler.addProcess(1, 2, 3) ==
               false);  // Duplicate ID rejected
        assert(scheduler.addProcess(2, 0, 0) ==
               false);  // 0 Burst time rejected
        std::cout << "[PASS] Test 6: Input Validation Passed.\n";
    }
}

/**
 * @brief Main function demonstrating scheduler usage with formatted output
 * @return 0 on successful execution
 */
int main() {
    test();

    std::cout << "\nDemonstrating Round Robin CPU Scheduler Example Run:\n";
    cpu_scheduling_algorithms::round_robin::RoundRobinScheduler<
        uint32_t, uint32_t, uint32_t>
        scheduler;
    scheduler.addProcess(1, 0, 5);
    scheduler.addProcess(2, 1, 4);
    scheduler.addProcess(3, 2, 2);
    scheduler.addProcess(4, 4, 1);

    scheduler.schedule(2);
    scheduler.printSchedule();

    std::cout
        << "All Round Robin CPU scheduling self-tests passed successfully!\n";
    return 0;
}
