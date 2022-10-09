/**
 * @file
 * @brief Implementation of Round Robin CPU scheduling algorithm
 * @details
 * Round-robin is a preemptive CPU scheduling algorithm where each
 * ready task runs turn by turn only in a cyclic queue for a limited
 * time slice. This algorithm also offers starvation free execution
 * of processes.
 * @author [Daemon19](https://github.com/Daemon19)
 */

#include <iomanip>
#include <cassert>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

/**
 * @brief Represent a process to be executed.
 */
struct Process {
    uint32_t id;
    uint32_t arrival_time;
    uint32_t burst_time;
};

/**
 * @brief Represent the result of a process execution.
 */
struct ProcessResult : public Process {
    uint32_t completion_time;
    uint32_t turn_around_time;
    uint32_t waiting_time;

    /**
     * @brief Constructor that calculate member variables based on a
     * process and completion time.
     * 
     * \param process A process that have been executed
     * \param completion_time The process execution finish time
     */
    ProcessResult(const Process& process, uint32_t completion_time)
        : Process(process), completion_time(completion_time) {
        turn_around_time = completion_time - arrival_time;
        waiting_time = turn_around_time - burst_time;
    }
    
    /**
     * @brief Compare each member variable.
     * 
     * \param p ProcessResult to be compared with
     * \return true if the processes IS equal
     * \return false if the processes IS NOT equal
     */
    bool operator==(const ProcessResult& p) const {
        return id == p.id && arrival_time == p.arrival_time &&
               burst_time == p.burst_time &&
               completion_time == p.completion_time &&
               turn_around_time == p.turn_around_time &&
               waiting_time == p.waiting_time;
    }
};

/**
 * @brief Execute processes based on Round-robin algorithm.
 * 
 * \param processes Processes to be executed
 * \param time_slice Time slice for processes execution
 * \return Results of each process execution
 */
std::vector<ProcessResult> RRExecute(const std::vector<Process>& processes,
                                     uint32_t time_slice);

/**
 * @brief Print a table containing process results data.
 * 
 * \return ostream inputted ostream
 */
std::ostream& operator<<(std::ostream& ostream,
                         const std::vector<ProcessResult>& results);

/**
 * @brief Self-test implementations.
 * 
 * \returns void
 */
void Test();


/**
 * @brief Comparator function for sorting processes.
 * 
 * \param p1 Process to be compared
 * \param p2 Process to be compared
 * \return 
 */
bool CompareAT(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

/**
 * @brief Check processes that arrive after the given time_elapsed.
 *
 * If a process arrive after the give time_elapsed, then the process
 * will be pushed into the schedule queue and inserted into the
 * arrived_process set.
 * 
 * \param processes Processes that will be checked for arrival
 * \param arrived_process A set containing processes that has arrived
 * \param schedule Queue containing pair of process and its remaining burst time
 * \param time_elapsed Time that has elapsed after processes execution
 */
void CheckArriveProcess(const std::vector<Process>& processes,
                        std::set<uint32_t>& arrived_process,
                        std::queue<std::pair<Process, uint32_t>>& schedule,
                        uint32_t time_elapsed);

/**
 * @brief Entry point of the program.
 * 
 * \return 0 on exit
 */
int main() {
    Test();
    return 0;
}

void Test() {
    std::vector<Process> processes{
        {0, 70, 3}, {1, 9, 2}, {2, 3, 39}, {3, 5, 29}, {4, 30, 90}};
    const uint32_t kTimeSlice{3};
    std::vector<ProcessResult> results = RRExecute(processes, kTimeSlice);

    std::vector<uint32_t> completion_times({80, 14, 100, 82, 166});
    std::vector<ProcessResult> correct_results;
    for (size_t i = 0; i < processes.size(); i++) {
        correct_results.emplace_back(processes[i], completion_times[i]);
    }

    std::sort(results.begin(), results.end(), CompareAT);
    std::sort(correct_results.begin(), correct_results.end(), CompareAT);

    std::cout << results;
    assert(results == correct_results);
    std::cout << "All test passed";
}

std::vector<ProcessResult> RRExecute(const std::vector<Process>& processes,
                                     uint32_t time_slice) {
    std::vector<Process> sorted_processes = processes;
    std::sort(sorted_processes.begin(), sorted_processes.end(), CompareAT);

    std::queue<std::pair<Process, uint32_t>> schedule;
    std::set<uint32_t> arrived_processes;
    std::vector<ProcessResult> results;
    results.reserve(processes.size());
    uint32_t time_elapsed = sorted_processes[0].arrival_time;

    CheckArriveProcess(sorted_processes, arrived_processes, schedule,
                       time_elapsed);

    while (!schedule.empty()) {
        std::pair<Process, uint32_t> current = schedule.front();
        schedule.pop();

        uint32_t elapsed =
            (current.second > time_slice) ? time_slice : current.second;
		current.second -= elapsed;
		time_elapsed += elapsed;

		CheckArriveProcess(sorted_processes, arrived_processes, schedule,
						   time_elapsed);

        if (current.second > 0) {
			schedule.push(current);
            continue;
        }
        results.emplace_back(current.first, time_elapsed);
    }

    return results;
}

std::ostream& operator<<(std::ostream& ostream,
                         const std::vector<ProcessResult>& results) {
    auto PrintCell = [&](const std::string &str) {
        ostream << std::setw(17) << std::left << str;
    };

    std::vector<ProcessResult> sorted = results;
    std::sort(sorted.begin(), sorted.end(), CompareAT);

    PrintCell("Process ID");
    PrintCell("Arrival Time");
    PrintCell("Burst Time");
    PrintCell("Completion Time");
    PrintCell("Turnaround Time");
    PrintCell("Waiting Time");
    ostream << std::endl;

    for (auto& p : sorted) {
        PrintCell(std::to_string(p.id));
        PrintCell(std::to_string(p.arrival_time));
        PrintCell(std::to_string(p.burst_time));
        PrintCell(std::to_string(p.completion_time));
        PrintCell(std::to_string(p.turn_around_time));
        PrintCell(std::to_string(p.waiting_time));
        ostream << "\n";
    }

    return ostream;
}

void CheckArriveProcess(const std::vector<Process> &processes,
                        std::set<uint32_t>& arrived_process,
                        std::queue<std::pair<Process, uint32_t>>& schedule,
                        uint32_t time_elapsed) {
    for (auto& p : processes) {
        if (p.arrival_time > time_elapsed ||
            arrived_process.find(p.id) != arrived_process.end()) {
            continue;
        }
        schedule.emplace(p, p.burst_time);
        arrived_process.insert(p.id);
    }
}
