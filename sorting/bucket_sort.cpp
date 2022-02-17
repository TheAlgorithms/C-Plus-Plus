// C++ program to sort an array using bucket sort
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

// Function to sort arr[] of size n using bucket sort
template <typename T, std::size_t N>
void bucketSort(std::array<T, N>& arr) {
    auto arr_size = arr.size();
    // 1) Create n empty buckets
    std::vector<float> *bucket = new std::vector<float>[arr_size];

    // 2) Put array elements in different buckets
    for (std::size_t i = 0; i < arr_size; i++) {
        int bi = arr_size * arr[i];  // Index in bucket
        bucket[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (std::size_t i = 0; i < arr_size; i++) std::sort(bucket[i].begin(), bucket[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (std::size_t i = 0; i < arr_size; i++)
        for (std::size_t j = 0; j < bucket[i].size(); j++) arr[index++] = bucket[i][j];
    delete[] bucket;
}

/* Driver program to test above funtion */
int main() {
    std::array<float, 6> arr{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < n; i++) std::cout << arr[i] << " ";
    return 0;
}
