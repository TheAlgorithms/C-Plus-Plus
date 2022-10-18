#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <vector>

void Test();
std::vector<int> SleepSort(const std::vector<int> &nums);
void SleepAndEmplace(int value, std::mutex &mutex, std::vector<int> &out);
std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec);

int main() {
    Test();
    return 0;
}

void Test() {
    std::vector<int> nums(5);
    std::iota(nums.begin(), nums.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nums.begin(), nums.end(), g);

    std::vector<int> sorted_nums(SleepSort(nums));

    std::vector<int> correct_nums(nums);
    std::sort(correct_nums.begin(), correct_nums.end());

    std::cout << "Original numbers: ";
    std::cout << nums;
    std::cout << "Sleep sorted numbers: ";
    std::cout << sorted_nums;
    std::cout << "Correct numbers: ";
    std::cout << correct_nums;

    assert(sorted_nums == correct_nums);
}

std::vector<int> SleepSort(const std::vector<int> &nums) {
    std::vector<int> result;
    result.reserve(nums.size());

    std::vector<std::thread> threads;
    threads.reserve(nums.size());

    std::mutex mutex;

    for (auto &i : nums) {
        threads.emplace_back(SleepAndEmplace, i, std::ref(mutex),
                             std::ref(result));
    }

    for (auto &t : threads) {
        t.join();
    }

    return result;
}

void SleepAndEmplace(int value, std::mutex &mutex, std::vector<int> &out) {
    std::this_thread::sleep_for(std::chrono::milliseconds(value));
    std::lock_guard<std::mutex> guard(mutex);
    out.emplace_back(value);
}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec) {
    for (auto &i : vec) {
        os << i << " ";
    }
    os << "\n";
    return os;
}