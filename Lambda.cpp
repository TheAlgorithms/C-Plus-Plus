// lambda function in c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a = 10;
    int b = 20;
    auto sum = [a, b] () { return a + b; }; // lambda function
    cout << sum() << endl;
    return 0;
}
