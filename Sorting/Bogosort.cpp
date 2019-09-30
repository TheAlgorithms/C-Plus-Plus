#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

template <typename Iterator, typename Predicate>
void bogo_sort(Iterator begin, Iterator end, Predicate p) {
    std::random_device rd;
    while (!std::is_sorted(begin, end, p)) {
        std::shuffle(begin, end, std::default_random_engine(rd()));
    }
}

template <typename Iterator>
void bogo_sort(Iterator begin, Iterator end) {
    bogo_sort(begin, end, std::less<typename std::iterator_traits<Iterator>::value_type>());
}

int main() {
    std::string str = "Hello World";
    bogo_sort(std::begin(str), std::end(str), std::less<char>());
    copy(std::begin(str), std::end(str), std::ostream_iterator<char>(std::cout, " "));
    std::cout << "\n";
    // Output -> " H W d e l l l o o r"
}
