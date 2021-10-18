/**
                                        Hacktoberfest2021
Node represents a file with a given size also given nodes are greater than 2 

1. Add all the nodes in a priority queue (Min Heap).{node.weight = file size}
2.Initialize count = 0 // variable to store file computations.
3. Repeat while (size of priority Queue is greater than 1) 
    1. create a new node
    2. new node = pq.poll().weight+pq.poll().weight;//pq denotes priority queue, remove 1st smallest and 2nd smallest element and add their weights to get a new node
    3. count += node.weight
    4. add this new node to priority queue; 
 
4. count is the final answer
 **/

#include<iostream>
#include <queue>
#include <vector>

using namespace std;
 
// Function to find minimum computation
int minComputation(int size, int files[])
{
 
    // Create a min heap
    priority_queue<int, vector<int>, greater<int> > pq;
 
    for (int i = 0; i < size; i++) {
 
        // Add sizes to priorityQueue
        pq.push(files[i]);
    }
 
    // Variable to count total Computation
    int count = 0;
 
    while (pq.size() > 1) {
 
        // pop two smallest size element
        // from the min heap
        int first_smallest = pq.top();
        pq.pop();
        int second_smallest = pq.top();
        pq.pop();
 
        int temp = first_smallest + second_smallest;
 
        // Add the current computations
        // with the previous one's
        count += temp;
 
        // Add new combined file size
        // to priority queue or min heap
        pq.push(temp);
    }
    return count;
}
 
// Driver code
int main()
{
 
    // No of files
    int n = 6;
 
    // 6 files with their sizes
    int files[] = { 2, 3, 4, 5, 6, 7 };
 
    // Total no of computations
    // do be done final answer
    cout << "Minimum Computations = "
         << minComputation(n, files);
 
    return 0;
}
