#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int process_id;
    int priority;
    int arrival_time; // You might need to simulate or calculate these values.
    int burst_time;   // Simulated value as actual CPU usage time is not directly available.
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

std::vector<Process> get_running_processes() {
    std::vector<Process> processes;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to create tool help snapshot." << std::endl;
        return processes;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        std::cerr << "Error: Unable to get first process." << std::endl;
        return processes;
    }

    int arrival_time = 0; // You can set this to a value based on your scheduling simulation.

    do {
        Process proc;
        proc.process_id = pe32.th32ProcessID;
        proc.priority = pe32.pcPriClassBase; // Basic priority class
        proc.arrival_time = arrival_time++;
        proc.burst_time = 10; // Arbitrary value; real CPU usage requires performance counters.
        proc.remaining_time = proc.burst_time;
        proc.completion_time = 0;

        processes.push_back(proc);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return processes;
}

void calculate_non_preemptive_priority(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        // Find the process with the highest priority that has arrived
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].completion_time == 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            current_time += processes[idx].burst_time;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }
        else {
            current_time++;
        }
    }
}

void calculate_preemptive_priority(std::vector<Process>& processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        // Find the process with the highest priority that has arrived and still has burst time left
        int idx = -1;
        int highest_priority = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].remaining_time--;
            current_time++;

            // If the process is completed
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                completed++;
            }
        }
        else {
            current_time++;
        }
    }
}

void print_process_table(const std::vector<Process>& processes) {
    std::cout << "\nProcess ID\tPriority\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& process : processes) {
        std::cout << process.process_id << "\t\t" << process.priority << "\t\t"
            << process.arrival_time << "\t\t" << process.burst_time << "\t\t"
            << process.completion_time << "\t\t" << process.turnaround_time << "\t\t"
            << process.waiting_time << "\n";
    }
}

int main() {
    std::vector<Process> processes = get_running_processes();

    if (processes.empty()) {
        std::cout << "No processes found." << std::endl;
        return 1;
    }

    // Choose scheduling type and run scheduling algorithm as in previous code.
    int choice;
    std::cout << "Choose scheduling type (1: Non-Preemptive, 2: Preemptive): ";
    std::cin >> choice;

    if (choice == 1) {
        calculate_non_preemptive_priority(processes);
    }
    else if (choice == 2) {
        calculate_preemptive_priority(processes);
    }
    else {
        std::cout << "Invalid choice. Exiting.\n";
        return 1;
    }

    print_process_table(processes);

    return 0;
}
