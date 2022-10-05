/**
 * @file
 * @brief Implemetation of Max Priority Queue uning max-heap
 * More about it: https://en.wikipedia.org/wiki/Priority_queue
 * @details
 * In computer science, a priority queue is an abstract data-type similar to a 
 * regular queue or stack data structure in which each element additionally has a 
 * priority associated with it. In a priority queue, an element with high priority 
 * is served before an element with low priority.
 * Though being a relatively new data structure it has its use cases in lots of fields:
 * Data compression[Huffman codes], Graph Searching[Dijkstra's Algorithm], 
 * Artificial Intelligence[A* seach], etc.
 * Insertion - O(log(N))
 * Deletion - O(log(N))
 * Max - O(1)
 * All the method names have been directly taken from PQ implementation of Java
 * @author [Puneet Tripathi](https://github.com/PuneetTri)
 */

#include<iostream>
using namespace std;

// Class 
class PQ{
    private:
        int capacity; // max capacity of PQ
        int *arr = NULL; // Pointer to the array of the PQ
        int N; // current size of PQ or total elements currently in PQ
        
        // Helper function to swap elements
        void swap(int *a, int *b) {
            int temp = *a;
            *a = *b;
            *b = temp;
        }

        /* Helper function for the max-heap implementation of PQ
        *  Function would help promte child node to their correct 
        *  position
        */
        void swim(int pos) {
            // Check if parent is smaller than child node
            while(pos > 1 && (arr[pos/2] < arr[pos])) {
                // In such case swap value of child with parent
                swap(&arr[pos], &arr[pos/2]);
                pos = pos/2; // Jump to position of parent node
            }
            // Promotion of child node will go on until it becomes smaller than the parent
        }

        /* Helper function for the max-heap implementation of PQ
        *  Function would help demote parent node to their correct 
        *  position
        */
        void sink(int pos) {
            // Check if node's position is that of parent node
            while(2*pos <= N) {
                int current = 2*pos; // Jump to the positon of child node
                // Compare both the children for the greater one
                if(current < N && arr[current] < arr[current+1]) current++;
                // If the parent node is greater, sink operation is complete. Break the loop
                if(arr[pos] >= arr[current]) break; 
                swap(&arr[pos], &arr[current]); // If not exchange the value of parent with child
                pos = current; // Exchange parent position to child position in the array
            }
        }
    public:
        PQ() {
            /* If capacity is not defined, default size of 11 would be used
            *  capacity=12 because we cant access 0th element of PQ, and to 
            *  accomodate 11 elements we need capacity to be 12.
            *  Parent is at position k, child at position (k*2,k*2+1), if we
            *  use positon 0 in our queue, its child would be at:
            *  (0*2, 0*2+1) -> (0,0). This is why we start at position 1
            */
            capacity = 12; 
            arr = new int[capacity];
            for(int i=0; i<capacity; i++) arr[i] = 0; // Initializing array with value 0
            N = 0; // Initializing size of PQ 
        }
        PQ(int max) {
            capacity = max+1;
            arr = new int[capacity];
            for(int i=0; i<capacity; i++) arr[i] = 0; // Initializing array with value 0
            N = 0; // Initializing size of PQ 
        }
        
        // Method to check whether PQ is empty or not
        bool isEmpty() {
            return N == 0;
        }

        // Method to return max element stored in PQ
        int peek() {
            return arr[1]; // arr[1] is the max value element by definition of max-heap
        }

        // Method to return size of PQ
        int size() {
            return N; // return current size of PQ
        }

        // Enqueue to the PQ
        void add(int val) {
            // Print overflow message if the capacity is full
            if(N == capacity){
                cout << "Overflow!" << endl;
                return;
            }
            arr[++N] = val;
            swim(N); // Swim up the element to its correct position
        }

        // Dequeue the element with the max priority from PQ
        int poll() {
            // Print underflow message if the PQ has no elements
            if(N == 0){
                cout << "Underflow!" << endl;
                return -1;
            }
            int max = arr[1]; // By defintion of our max-heap, value at arr[1] pos is the greatest
            swap(&arr[1], &arr[N]);
            sink(1); // Sink the element in order
            arr[N--] = 0; // Nullify the deleted element from the priority queue
            
            return max;
        }    
};

int main() {
    PQ pq(20); // Initalizing PQ object

    // Example testcases to check if PQ is working fine
    if(pq.isEmpty()) {
        cout << "Priority queue is empty" << endl;
    } else {
        cout << "Priority queue is not empty" << endl;
    }
    pq.add(15);
    cout << "Max element: " << pq.peek() << endl;
    if(pq.isEmpty()) {
        cout << "Priority queue is empty" << endl;
    } else {
        cout << "Priority queue is not empty" << endl;
    }
    cout << "Element removed: " << pq.poll() << endl;
    pq.add(12);
    pq.add(10);
    pq.add(8);
    cout << "Size of PQ: " << pq.size() << endl;
    cout << "Max element: " << pq.peek() << endl;
    pq.add(17);
    cout << "Max element: " << pq.peek() << endl;
}
