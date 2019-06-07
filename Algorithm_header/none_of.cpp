#include <algorithm>  // std::none_of
#include <array>      // std::array
#include <iostream>   // std::cout

template <class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
	while (first != last) {
		if (pred(*first)) return false;
		++first;
	}
	return true;
}



int main() {
	std::array<int, 8> foo = { 1, 2, 4, 8, 16, 32, 64, 128 };

	if (std::none_of(foo.begin(), foo.end(), [](int i) { return i < 0; }))
		std::cout << "There is no element that is negative.\n";

	return 0;
}
