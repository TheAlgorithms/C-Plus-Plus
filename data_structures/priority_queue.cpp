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

#include<iostream> // For standard I/O
#include<cassert> // For testcases check
#include<utility> // For importing swap utility function

// Class 
class PQ{
    private:
        int capacity; // max capacity of PQ
        int *arr; // Pointer to the array of the PQ
        int N; // current size of PQ or total elements currently in PQ

        /* Helper function for the max-heap implementation of PQ
        *  Function would help promte child node to their correct 
        *  position
        */
        void swim(int pos) {
            // Check if parent is smaller than child node
            while(pos > 1 && (arr[pos/2] < arr[pos])) {
                // In such case swap value of child with parent
                std::swap(arr[pos], arr[pos/2]);
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
                std::swap(arr[pos], arr[current]); // If not exchange the value of parent with child
                pos = current; // Exchange parent position to child position in the array
            }
        }
    public:
        PQ(int max=11) {
            /* If capacity is not defined, default size of 11 would be used
            *  capacity=max+1 because we cant access 0th element of PQ, and to 
            *  accomodate (max)th elements we need capacity to be max+1.
            *  Parent is at position k, child at position (k*2,k*2+1), if we
            *  use positon 0 in our queue, its child would be at:
            *  (0*2, 0*2+1) -> (0,0). This is why we start at position 1
            */
            capacity = max+1;
            arr = new int[capacity];
            for(int i=0; i<capacity; i++) arr[i] = 0; // Initializing array with value 0
            N = 0; // Initializing size of PQ 
        }

        // Deallocate memory when PQ is no further in scope
        ~PQ() {
            delete[] arr;
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
                std::cout << "Overflow!" << std::endl;
                return;
            }
            arr[++N] = val;
            swim(N); // Swim up the element to its correct position
        }

        // Dequeue the element with the max priority from PQ
        int poll() {
            // Print underflow message if the PQ has no elements
            if(N == 0){
                std::cout << "Underflow!" << std::endl;
                return -1;
            }
            int max = arr[1]; // By defintion of our max-heap, value at arr[1] pos is the greatest
            std::swap(arr[1], arr[N]);
            sink(1); // Sink the element in order
            arr[N--] = 0; // Nullify the deleted element from the priority queue
            
            return max;
        }    
};

static void test() {
    /* Following tests would check multiple methods that are defined
    *  in PQ, and check if they work correctly
    */
    
    PQ pq; // Initalizing PQ object (By default size = 11)

    // Example testcases to check if PQ is working fine

    if(pq.isEmpty()) {
        std::cout << "Priority queue is empty" << std::endl;
    } else {
        std::cout << "Priority queue is not empty" << std::endl;
    }
    assert(pq.isEmpty() == true); // Test-case #1 
   
    pq.add(15);
    std::cout << "Max element: " << pq.peek() << std::endl;
    assert(pq.peek() == 15); // Test-case #2 

    if(pq.isEmpty()) {
        std::cout << "Priority queue is empty" << std::endl;
    } else {
        std::cout << "Priority queue is not empty" << std::endl;
    }
    assert(pq.isEmpty() == false); // Test-case #3

    int temp = pq.poll(); // Value retrieved from poll operation
    std::cout << "Element removed: " << temp << std::endl;
    assert(temp == 15); // Test-case #4

    pq.add(12);
    pq.add(10);
    pq.add(8);
    std::cout << "Size of PQ: " << pq.size() << std::endl;
    assert(pq.size() == 3); // Test-case #5

    std::cout << "Max element: " << pq.peek() << std::endl;
    assert(pq.peek() == 12); // Test-case #6

    pq.add(17);
    std::cout << "Max element: " << pq.peek() << std::endl;
    assert(pq.peek() == 17); // Test-case #7
}

int main() {
    test(); // Run multiple testcases to test our algorithm
}
