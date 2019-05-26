#include<iostream>

using namespace std;

unsigned int abs(long long& value)
{
    return (value < 0 ) ? value * -1: value;
}

int main()
{
    for(int i = -10; i < 10;i++)
        cout << i << " : " << "abs(" << i << ")" << " = " << abs(i) << endl;
}