#include <iomanip>
#include <string>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

struct Process {
    uint32_t id;
    uint32_t arrival_time;
    uint32_t burst_time;
};

struct ProcessResult : public Process {
    uint32_t completion_time;
    uint32_t turn_around_time;
    uint32_t waiting_time;

    ProcessResult(const Process& process, uint32_t time_elapsed) : Process(process) {
        completion_time = time_elapsed;
        turn_around_time = completion_time - arrival_time;
        waiting_time = turn_around_time - burst_time;
    }
};

std::vector<ProcessResult> RRExecute(const std::vector<Process>& processes,
                                     uint32_t time_slice);

std::ostream& operator<<(std::ostream& ostream,
                         const std::vector<ProcessResult>& results);

int main() {
    std::vector<Process> processes{{0, 3, 3}, {1, 8, 5}, {2, 5, 4}};
    const uint32_t kTimeSlice{2};
    std::vector<ProcessResult> results = RRExecute(processes, kTimeSlice);
    std::cout << results;
    std::getchar();
    return 0;
}

bool CompareAT(const Process& p1, const Process& p2) {
    return p1.arrival_time < p2.arrival_time;
}

void CheckArriveProcess(const std::vector<Process>& processes,
                        std::set<uint32_t>& arrived_process,
                        std::queue<std::pair<Process, uint32_t>>& schedule,
                        uint32_t time_elapsed);

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

    PrintCell("Process ID");
    PrintCell("Arrival Time");
    PrintCell("Burst Time");
    PrintCell("Completion Time");
    PrintCell("Turnaround Time");
    PrintCell("Waiting Time");
    ostream << std::endl;

    for (auto& p : results) {
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
