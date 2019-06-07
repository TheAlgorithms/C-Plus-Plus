#include <algorithm>  // std::any_of
#include <array>      // std::array
#include <iostream>   // std::cout

template <class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
	while (first != last) {
		if (pred(*first)) return true;
		++first;
	}
	return false;
}

int main() {
	std::array<int, 7> foo = { 0, 1, -1, 3, -3, 5, -5 };

	if (std::any_of(foo.begin(), foo.end(), [](int i) { return i < 0; }))
		std::cout << "There is a negative number in the range..\n";

	return 0;
}
