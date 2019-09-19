#include <iostream>
#include "ClassWithSingleType.hpp"
#include <string>

using namespace std;
int main(){
    SingleType<int> myInt(3);
    SingleType<double> myDouble(2.9);
    SingleType<char> myChar('A');
    SingleType<string> myString("hello");

    print(myInt);
    print(myDouble);
    print(myChar);
    print(myString);
}
