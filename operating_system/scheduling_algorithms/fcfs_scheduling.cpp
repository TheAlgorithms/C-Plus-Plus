#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <cstdio>
using namespace std;

/** 
 * @brief Comparator class for Priority queue
 *  S: Data type of Process id
 *  T: Data type of Arrival time
 *  E: Data type of Burst time 
*/ 
template<typename S, typename T, typename E>
class Compare{
    public:
    /**
     * @param t1 = first tuple
     * @param t2 = second tuple 
     * @brief checks whether to swap two tuples or not
    */
    bool operator () (tuple<S, T, E, double, double, double>& t1, tuple<S, T, E, double, double, double>& t2){
        if(get<1>(t2) < get<1>(t1)){
            return true;
        }
        else if(get<1>(t2) == get<1>(t1)){
            return get<0>(t2) < get<0>(t1);
        }
        return false;
    }
};

/**
 * @brief Class which implements the FCFS scheduling algorithm
 *  S: Data type of Process id
 *  T: Data type of Arrival time
 *  E: Data type of Burst time 
*/ 
template<typename S, typename T, typename E>
class FCFS{
    /**
     * Priority queue of schedules(stored as tuples) of processes.
     * In each tuple
     * 1st element: Process id
     * 2nd element: Arrival Time
     * 3rd element: Burst time
     * 4th element: Completion time
     * 5th element: Turnaround time
     * 6th element: Waiting time
    */
    priority_queue<tuple<S, T, E, double, double, double>, vector<tuple<S, T, E, double, double, double>>, Compare<S, T, E>> schedule;

    // Stores final status of all the processes after completing execution.
    vector<tuple<S, T, E, double, double, double>> result; 
    
    // Stores process ids. Used for confirming absence of a process while adding it.
    unordered_set<S> idList;
    public:
    /**
     * @brief add the process to the ready queue if it isn't already there
     * @param id: Process id
     * @param arrival: Arrival time of the process
     * @param burst: Burst time of the process
     * 
    */
    void addProcess(S id, T arrival, E burst){
        // Add if process with process id not found in idList.
        if(idList.find(id) == idList.end()) {
            tuple<S, T, E, double, double, double> t = make_tuple(id, arrival, burst, 0, 0, 0);
            schedule.push(t);
            idList.insert(id);
        }
        
    }

    /**
     * @brief Algorithm for scheduling CPU processes according to the First Come First Serve(FCFS) scheduling algorithm.
     * 
     * @description FCFS is a non -preemptive algorithm in which the process which arrives first gets executed first. If two or 
     * more processes arrive together then the process with smaller process id runs first (each process has a unique proces id).
     * 
     * I used a min priority queue of tuples to accomplish this task. The processes are ordered by their arrival times. If arrival
     * times of some processes are equal, then they are ordered by their process id.
    */ 
    void scheduleForFcfs(){
        // Variable to keep track of time elepsed so far
        double timeElapsed = 0;

        while(!schedule.empty()){
            tuple<S, T, E, double, double, double> cur = schedule.top();
            
            // If the next process arrived at time t2, the last process completed its execution at time t1, and t2 > t1.
            if(get<1>(cur) > timeElapsed){
                timeElapsed += get<1>(cur) - timeElapsed;
            }

            // Add Burst time to time elapsed
            timeElapsed += get<2>(cur);
            
            get<3>(cur) = timeElapsed;
            
            // Turnaround time = Completion time - Arrival time
            get<4>(cur) = get<3>(cur) - get<1>(cur);

            //Waiting time = Turnaround time - Burst time
            get<5>(cur) = get<4>(cur) - get<2>(cur);

            result.push_back(cur);
            schedule.pop();
        }
        printResult();
    }

    // Utility function for printing the status of each process after execution
    void printResult(){
        cout << "Status of all the proceses post completion is as follows:" << endl;

        printf("%-17s%-17s%-17s%-17s%-17s%-17s\n", "Process Id", "Arrival Time", "Burst Time", 
                    "Completion Time", "Turnaround Time", "Waiting Time"
                );
        for(size_t i{}; i < result.size(); i++){
            printf("%-17d%-17d%-17d%-17.2lf%-17.2lf%-17.2lf\n", get<0>(result[i]), get<1>(result[i]), get<2>(result[i]), 
                get<3>(result[i]), get<4>(result[i]), get<5>(result[i])
                );
        }
    }
    

};

int main(){
    FCFS<int ,int, int> readyQueue;

    //Sample test case
    int n = 3;
    tuple<int, int, int> input[n] = {
        make_tuple(1, 0, 30),
        make_tuple(2, 0, 5),
        make_tuple(3, 0, 5)
    };

    for(int i{}; i < n; i++){
        int id, arrival, burst;
        readyQueue.addProcess(get<0>(input[i]), get<1>(input[i]), get<2>(input[i]));
    }

    readyQueue.scheduleForFcfs();
    return 0;
}