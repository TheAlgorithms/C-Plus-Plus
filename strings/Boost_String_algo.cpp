#include <bits/stdc++.h>
#include <iostream>
  
using namespace std;
using namespace boost::algorithm;
  
int main()
{
    string str("Hello");
    string upper_s;
    string lower_s;
  
    cout << "Actual string: "
         << str << endl;
  
    to_upper(str);
    cout << "Actual string converted to uppercase: "
         << str << endl;
  
    to_lower(str);
    cout << "Actual string converted to lowercase: "
         << str << endl;
  
    str = "Hello";
    upper_s = to_upper_copy(str);
    lower_s = to_lower_copy(str);
  
    cout << "Converted Uppercase string: "
         << upper_s << endl;
    cout << "Converted Lowercase string: "
         << lower_s << endl;
  
    return 0;
}