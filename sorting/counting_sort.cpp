#include <iostream>
#include <vector>

// Returns the maximum element in an array
int getMax(const std::vector<int>& arr) {
    int maxVal = arr[0];
    for (const auto& val : arr)
        if (val > maxVal)
            maxVal = val;
    return maxVal;
}

// Returns the minimum element in an array
int getMin(const std::vector<int>& arr) {
    int minVal = arr[0];
    for (const auto& val : arr)
        if (val < minVal)
            minVal = val;
    return minVal;
}

// Prints the array elements
void printArray(const std::vector<int>& arr) {
    for (const auto& val : arr) 
        std::cout << val << ", ";
    std::cout << std::endl;
}

// Writing The counting sort algorithm
std::vector<int> countingSort(const std::vector<int>& arr) {
    int maxVal = getMax(arr);
    int minVal = getMin(arr);
    
    std::vector<int> count(maxVal - minVal + 1, 0);
    std::vector<int> sortedArr(arr.size());

    for (const auto& val : arr) 
        count[val - minVal]++;

    for (int i = 1; i < count.size(); i++) 
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; i--) {
        sortedArr[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    return sortedArr;
}

// Checks if the array is sorted
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) 
        if (arr[i] < arr[i - 1])
            return false;
    return true;
}

int main() {
    std::vector<int> arr = {47, 65, 20, 66, 25, 53, 64, 69, 72, 22,
                            74, 25, 53, 15, 42, 36, 4,  69, 86, 19};

    std::cout << "Original Array: ";
    printArray(arr);

    std::vector<int> sortedArr = countingSort(arr);

    std::cout << "Sorted Array: ";
    printArray(sortedArr);

//Automation Check
    if (isSorted(sortedArr))
        std::cout << "Array is sorted." << std::endl;
    else
        std::cout << "Array is not sorted." << std::endl;

    return 0;
}
