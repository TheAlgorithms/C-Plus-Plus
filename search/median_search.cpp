#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

std::vector<int> v;
std::vector<int> s1;
std::vector<int> s2;
std::vector<int> s3;

template <class X>
void comp(X x) {
    if (s1.size() >= x && s1.size() + s2.size() < x) {
        std::cout << s2[0] << " is the " << x + 1 << "th element from front";
    } else if (s1.size() > x) {
        std::sort(s1.begin(), s1.end());
        std::cout << s1[x] << " is the " << x + 1 << "th element from front";
    } else if (s1.size() + s2.size() <= x && s3.size() > x) {
        std::sort(s3.begin(), s3.end());
        std::cout << s3[x - s1.size() - s2.size()] << " is the " << x + 1
                  << "th element from front";
    } else {
        std::cout << x + 1 << " is invalid location";
    }
}
int main() {
    for (int i = 0; i < 1000; i++) {
        v.push_back(std::rand() % 1000);
    }
    for (int r : v) {
        std::cout << r << " ";
    }
    int median = std::rand() % 1000;
    std::cout << "\nmedian=" << median << std::endl;
    int avg1, avg2, avg3, sum1 = 0, sum2 = 0, sum3 = 0;
    for (int i = 0; i < 1000; i++) {
        if (v.back() == v[median]) {
            avg1 = sum1 + v.back();
            s2.push_back(v.back());
        } else if (v.back() < v[median]) {
            avg2 = sum2 + v.back();
            s1.push_back(v.back());
        } else {
            avg3 = sum3 + v.back();
            s3.push_back(v.back());
        }
        v.pop_back();
    }
    int x;
    std::cout << "enter the no. to be searched form begining:- ";
    std::cin >> x;
    comp(x - 1);
    return 0;
}
