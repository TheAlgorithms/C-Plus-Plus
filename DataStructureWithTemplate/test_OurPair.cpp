#include <iostream>
#include "OurPair.hpp"
#include <string>
#include <vector>
using namespace std;
int main(){
    OurPair<int, int> pairInt1(2,3);
    OurPair<int, int> pairInt2(2,3);
    OurPair<int, int> pairInt3(4,5);
    OurPair<double, double> pairDouble(2.3,4.5);
    OurPair<int,double> intDouble(55,78.9);
    OurPair<double, char> doubleChar(4.4,'A');
    OurPair<string, int> strInt("hello",4);
    bool res1 = (pairInt1 == pairInt2); 
    bool res2 = (pairInt1 < pairInt3); 
    print(pairInt1);
    print(pairDouble);
    print(intDouble);
    print(doubleChar);
    print(strInt);
    
}