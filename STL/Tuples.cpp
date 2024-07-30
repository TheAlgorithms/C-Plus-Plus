#include <tuple>
#include <iostream>
using namespace std;

int main()
{
    // tuple t{42, 'a', 4.2}; // Another C++17 feature: class template argument deduction
    tuple<int, char, float> t = {42, 'a', 4.2};

    apply([](auto &&...args)
          { ((cout << args << endl), ...); },
          t);
}