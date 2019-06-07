#include <iostream>   // std::cout
#include <vector>     // std::vector

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& val) {
	while (first != last) {
		*first = val;
		++first;
	}
}

int main() {
	// myvector: 0 0 0 0 0 0 0 0
	std::vector<int> myvector(8);

	// myvector: 5 5 5 5 0 0 0 0
	std::fill(myvector.begin(), myvector.begin() + 4, 5);

	// myvector: 5 5 5 8 8 8 0 0
	std::fill(myvector.begin() + 3, myvector.end() - 2, 8);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end();
		++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
