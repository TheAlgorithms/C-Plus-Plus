// C++ program to sort an array using bucket sort
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

// Function to sort arr[] of size n using bucket sort
template <typename T, std::size_t N>
void bucketSort(std::array<T, N>& arr) {
    auto arr_size = arr.size();
    // 1) Create n empty buckets
    auto buckets = std::make_unique<std::vector<float>[]>(arr_size);

    // 2) Put array elements in different buckets
    for (auto const& elem : arr) {
        std::size_t index = arr_size * elem;
        buckets[index].emplace_back(elem);
    }

    // 3) Sort individual buckets
    for (std::size_t i = 0; i < arr_size; i++)
        std::sort(buckets[i].begin(), buckets[i].end());

    // 4) Concatenate all buckets into arr[]
    for (std::size_t i{}, index{}; i < arr_size; ++i)
        for (std::size_t j{}; j < buckets[i].size(); ++j, ++index)
            arr[index] = buckets[i][j];
}

template <typename T, std::size_t N>
auto print(std::array<T, N> arr) {
    std::cout << "Sorted array is \n";

    for (auto const& elem : arr) std::cout << elem << ' ';
    std::cout << std::endl;
}

/* Driver program to test above function */
int main() {
    std::array<float, 6> arr{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    bucketSort(arr);
    print(arr);

    return 0;
}
