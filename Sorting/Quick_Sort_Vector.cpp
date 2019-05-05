#include <iostream>		// std::cout
#include <vector>
#include <iterator>		// std::distance, std::next
#include <algorithm>	// std::iter_swap
#include <random>		// for random number generation
#include <functional>	// std::bind

// If you want to check out each partition in gdb, you can modify the signature to this:
// void QuickSort(std::vector<typename Iter::value_type>& vec, Iter left, Iter right)
// and make sure to modify the every invocation argument
template<typename Iter>
void QuickSort(Iter left, Iter right) {

	auto size = std::distance(left, right);
	if (size <= 1) {
		return;
	}

	auto pivot = std::next(right, -1);
	auto wall = left;		// right boundary of the sequence containing smaller numbers
	auto curr = left;		// indicates the current iterator position

	// partition starts here
	while (curr != right) {
		if (*curr < *pivot) {
			std::iter_swap(wall, curr);
			wall++;
		}
		curr++;
	}

	std::iter_swap(pivot, wall);
	QuickSort(left, wall);
	QuickSort(wall + 1, right);
}

void RandomIntGenerate(std::vector<int>& vec, int lowerBound, int upperBound) {

	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
	auto dice = std::bind(distribution, generator);
	for (auto& i : vec) {
		i = dice();
	}
}

int main() {

	std::vector<int> input(50);
	RandomIntGenerate(input, 1, 500);
	QuickSort(input.begin(), input.end());
	for (auto num : input) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
	return EXIT_SUCCESS;
}