/// Copyright 2020 @author Albirair
#include "./binary_search.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
int main(int argc, char ** argv) {
    using std::size_t, std::cout, std::cin;
    std::default_random_engine e;
    size_t n;
    do {
        cout << "enter a nonzero number of elements\n";
        cin >> n;
    } while (!n);
    std::vector<int> v(n);
    int val;
    for (size_t i(0); i != n; ++i)
        v[i] = e() % 100;
    std::sort(v.begin(), v.end());
    for (size_t i(0); i != n; ++i)
        cout << "v[" << i << "] = " << v[i] << '\n';
    cout << "enter the value to search for:\t";
    cin >> val;
    auto r(binary_search(v.begin(), n, val));
    if (r.first)
        cout << val << " is at " << r.second - v.begin();
    else
        cout << val << " doesn't exist";
    return 0;
}
