#include <iostream>
using namespace std;

void toh(int n, char a, char b, char c)
{
  if(n > 1)
  {
    toh(n-1, a, c, b);
    cout << "Move disk " << n << " from rod " << a <<
                                " to rod " << b << "\n";
    toh(n-1, c, b, a);
  }
  if(n == 1)
  cout << "Move disk 1 from rod " << a <<
                          " to rod " << b<<"\n";
}

int main()
{
  int n;
  cout<<"Enter the Number of rings: ";cin>>n;
  toh(n, 'A', 'B', 'C');
}
