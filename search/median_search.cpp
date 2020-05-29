/**
 * \file
 * \brief [Median search](https://en.wikipedia.org/wiki/Median_search) algorithm
 * \warning This core is erroneous and gives invorrect answers. Tested using
 * cases from [here](https://brilliant.org/wiki/median-finding-algorithm/)
 * \ingroup median search
 * \{
 */
#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @todo add documentation
 */
template <class X>
void comp(X x, std::vector<int> &s1, std::vector<int> &s2,
          std::vector<int> &s3) {
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

#define MAX_NUM 20  ///< maximum number of values to sort from

/**
 * Main function
 */
int main() {
    std::vector<int> v{25, 21, 98, 100, 76, 22, 43, 60, 89, 87};
    std::vector<int> s1;
    std::vector<int> s2;
    std::vector<int> s3;

    // creates an array of random numbers
    // for (int i = 0; i < MAX_NUM; i++) {
    //     int r = std::rand() % 1000;
    //     v.push_back(r);
    //     std::cout << r << " ";
    // }
    for (int r : v) std::cout << r << " ";

    int median = std::rand() % 1000;  // initialize to a random numnber

    std::cout << "\nmedian=" << median << std::endl;
    int avg1, avg2, avg3, sum1 = 0, sum2 = 0, sum3 = 0;

    for (int i = 0; i < v.size(); i++) {  // iterate through all numbers
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
    comp(x - 1, s1, s2, s3);

    return 0;
}
/// }
