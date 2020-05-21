#include<iostream>
using namespace std;
string add_strings(string a, string b)
{
string space = " ";
string newString = a+space+b;

return newString;
}
int main() {
string string1 = "hello";
string string2 = "world";
string newString = add_strings(string1, string2);
cout << newString;
return 0;
}
