#include <iostream>   // std::cout
#include <vector>     // std::vector

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
	for (; first != last; ++first) {
		f(*first);
	}
	return f;
}

void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass {  // function object type:
	void operator()(int i) { std::cout << ' ' << i; }
} myobject;

int main() {
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	// Passing general function pointers
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction);
	std::cout << '\n';

	// pass the Functor
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject);
	std::cout << '\n';

	// Pass the lambda function
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(),
		[](const int& n) { std::cout << ' ' << n; });
	std::cout << '\n';

	return 0;
}
