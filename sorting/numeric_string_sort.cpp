// Using general algorithms to sort a collection of strings results in
// alphanumeric sort. If it is a numeric string, it leads to unnatural sorting

// eg, an array of strings 1,10,100,2,20,200,3,30,300
// would be sorted in that same order by using conventional sorting,
// even though we know the correct sorting order is 1,2,3,10,20,30,100,200,300

// This Programme uses a comparator to sort the array in Numerical order instead
// of Alphanumeric order

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool NumericSort(std::string a, std::string b) {
    while (a[0] == '0') {
        a.erase(a.begin());
    }
    while (b[0] == '0') {
        b.erase(b.begin());
    }
    int n = a.length();
    int m = b.length();
    if (n == m)
        return a < b;
    return n < m;
}

int main() {
    int n;
    std::cout << "Enter number of elements to be sorted Numerically\n";
    std::cin >> n;

    std::vector<std::string> v(n);
    std::cout << "Enter the string of Numbers\n";
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }

    sort(v.begin(), v.end());
    std::cout << "Elements sorted normally \n";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";

    std::sort(v.begin(), v.end(), NumericSort);
    std::cout << "Elements sorted Numerically \n";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }

    return 0;
}
