/**
 * @file
 * @brief A cpp program for random pivot quick sort algorithm.
 * @details Intro :
 *              - A random pivot quick sort algorithm is pretty much same as quick sort with a difference of having a logic of
 *                  selecting next pivot element from the input array.
 *              - Where in quick sort is fast, but still can give you the time complexity of O(n^2) in worst case.
 *              - To avoid hitting the time complexity of O(n^2), we use the logic of randomize the selection process of pivot
 *                  element.
 *
 *          Logic :
 *              - The logic is pretty simple, the only change is in the partitioning algorithm, which is selecting the
 *                  pivot element.
 *              - Instead of selecting the last or the first element from array for pivot we use a random index to select
 *                  pivot element.
 *              - This avoids hitting the O(n^2) time complexity in practical use cases.
 *
 *
 *
 *       (Partition Logic) :-
 *           -> Partitions are done such as numbers lower than the "pivot" element is arranged on the left side of the "pivot",
 *               and number larger than the "pivot" element are arranged on the right part of the array.
 *
 *       (Algorithm) :-
 *           -> Select the pivot element randomly using getRandomIndex() function from this namespace.
 *           -> Initialize the pInd (partition index) from the start of the array.
 *           -> Loop through the array from start to less than end. (from start to < end).
 *               (Inside the loop) :-
 *                   -> Check if the current element (arr[i]) is less than the pivot element in each iteration.
 *                   -> If current element in the iteration is less than the pivot element,
 *                       then swap the elements at current index (i) and partition index (pInd) and increment the partition index by one.
 *           -> At the end of the loop, swap the pivot element with partition index element.
 *           -> Return the partition index from the function.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 *
 */


#include <iostream>
#include <ctime>
#include <cassert>
#include <algorithm>

namespace randomPivotQuickSort {
    /**
     * A simple function to print the array
     * @tparam arr[] Input array.
     * @param size Size of the array
     * @returns void
     * */
    void showArray(int arr[], int size) {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * Takes the start and end indices of an array and returns a random integer between the range of those two
     * for selecting pivot element.
     *
     * @param start The starting index.
     * @param end The ending index.
     * @returns int A random number between start and end index.
     * */
    int getRandomIndex(int start, int end) {
        srand(time(nullptr)); // Initialize random number generator.
        int randomPivotIndex = start + rand() % (end - start + 1);
        return randomPivotIndex;
    }

    /**
     * Nothing fancy, just a simple function to swap two elements in array.
     * @tparam size size of the array to be passed as argument.
     * @param arr The actual array.
     * @param i An index of array.
     * @param j Another index of the passed array
     * @returns std::array<int, size> Same array with swapped elems.
    */
    void swap(int arr[], int i, int j) {
        // Nothing fancy, just a simple snippet to swap two numbers in an array.
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    /**
     * A partition function which handles the partition logic of quick sort.
     * @tparam size size of the array to be passed as argument.
     * @param start The start index of the passed array
     * @param end The ending index of the passed array
     * @returns std::tuple<int, std::array<int, size>> A tuple of pivot index and pivot sorted array.
    */
    int partition(int arr[], int start, int end) {

        int pivot = arr[end];  // Randomly selected element will be here from caller function (quickSortRP()).
        int pInd = start;

        for (int i = start; i < end; i++) {
            if (arr[i] <= pivot) {
                swap(arr, i, pInd);  // swapping the elements from current index to pInd.
                pInd++;
            }
        }
        swap(arr, pInd, end);  // swapping the pivot element to its sorted position
        return pInd;
    }

    void quickSortRP(int arr[], int start, int end) {
        if (start < end) {

            int randomIndex = getRandomIndex(start, end);  // Use this random index to randomize pivot.

            swap(arr, end, randomIndex); // switching the pivot with right most bound.

            int pivotIndex = partition(arr, start, end);  // getting pivot index and pivot sorted array.

            // Recursively calling
            quickSortRP(arr, start, pivotIndex - 1);
            quickSortRP(arr, pivotIndex + 1, end);
        }
    }
}


/**
 * A function utility to generate unsorted array of given size and range.
 * @tparam size Size of the output array.
 * @param from Stating of the range.
 * @param to Ending of the range.
 * @returns std::array<int, size> Unsorted array of specified size.
 * */
template<size_t size>
int *generateUnsortedArray(int from, int to) {
    srand(time(nullptr));
    int *unsortedArray = new int[size];
    assert(from < to);
    int i = 0;
    while (i < size) {
        int randomNum = from + rand() % (to - from + 1);
        if (randomNum) {
            unsortedArray[i] = randomNum;
            i++;
        }
    }
    return unsortedArray;
}


/**
 * A class, encapsulating the necessary test cases.
 */
class TestCases {
private:
    template<typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

public:
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    void testCase_1() {
        const int inputSize = 1;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 1 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   EDGE CASE : Only contains one element");
        int *unsorted_arr = new int[inputSize];

        int start = 0;
        int end = inputSize - 1; // length - 1

        log("Running algorithm of data of length 50 ...");
        randomPivotQuickSort::quickSortRP(unsorted_arr, start, end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(unsorted_arr, unsorted_arr + end));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    }

    void testCase_2() {
        const int inputSize = 500;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("Description:");
        log("   BIG INPUT : Contains 500 elements and repeated elements");
        log("This is test case 2 for Random Pivot Quick Sort Algorithm : ");
        int *unsorted_arr = generateUnsortedArray<inputSize>(1, 10000);

        int start = 0;
        int end = inputSize - 1; // length - 1

        log("Running algorithm of data of length 500 ...");
        randomPivotQuickSort::quickSortRP(unsorted_arr, start, end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(unsorted_arr, unsorted_arr + end));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    void testCase_3() {
        const int inputSize = 1000;
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 3 for Random Pivot Quick Sort Algorithm : ");
        log("Description:");
        log("   LARGE INPUT : Contains 1000 elements and repeated elements");
        int *unsorted_arr = generateUnsortedArray<inputSize>(1, 10000);

        int start = 0;
        int end = inputSize - 1; // length - 1

        log("Running algorithm...");
        randomPivotQuickSort::quickSortRP(unsorted_arr, start, end);
        log("Algorithm finished!");

        log("Checking assert expression...");
        assert(std::is_sorted(unsorted_arr, unsorted_arr + end));
        log("Assertion check passed!");

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
};

/**
 * A test function which calls various test cases with varying input.
 * @returns void on exit.
 */
void test() {
    TestCases tc = TestCases();
    tc.runTests();
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test(); // Executes various test cases.

    const int inputSize = 10;
    int *arr = generateUnsortedArray<inputSize>(50, 1000);
    std::cout << "Unsorted array is : " << std::endl;
    randomPivotQuickSort::showArray(arr, inputSize);

    randomPivotQuickSort::quickSortRP(
            arr, 0,
            inputSize - 1
    );
    std::cout << "Sorted array is : " << std::endl;
    randomPivotQuickSort::showArray(arr, inputSize);
    return 0;
}


