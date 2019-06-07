#include <array>      // std::array
#include <iostream>   // std::cout

template <class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
	while (first != last) {
		if (!pred(*first)) return false;
		++first;
	}
	return true;
}



int main() {
	std::array<int, 8> foo = { 3, 5, 7, 11, 13, 17, 19, 23 };

	if (std::all_of(foo.begin(), foo.end(), [](int i) { return i % 2; }))
		std::cout << "All elements are odd\n";

	return 0;
}
