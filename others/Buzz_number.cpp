//A buzz number is a number that is either divisble by 7 or has last digit as 7.
#include <iostream>
using namespace std;
int main()
{
  int n, t;
  cin >> t;
  while (t--)
  {
    cin >> n;
    if ((n % 7 == 0) || (n % 10 == 7))
      cout << n << " is a buzz number" << endl;
    else
      cout << n << " is not a buzz number" << endl;
  }
  return 0;
}
