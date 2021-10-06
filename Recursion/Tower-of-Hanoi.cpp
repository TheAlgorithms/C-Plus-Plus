#include <iostream>
using namespace std;

void toh(int n, char a, char b, char c)
{
  if(n > 1)
  {
    // Move n-1 Disks from first rod to third rod using second.
    toh(n-1, a, c, b);

    //Move the last Disk from first rod to second rod.
    cout << "Move disk " << n << " from rod " << a <<
                                " to rod " << b << "\n";

    //Move all n-1 Disks from third to second using first.
    toh(n-1, c, b, a);
  }

  if(n == 1)
    cout << "Move disk 1 from rod " << a <<
                            " to rod " << b<<"\n";
}

int main()
{
  int n;
  cout<<"\n\nYOU WILL ENTER THE DISKS AND THE ALGORITHM WILL FIND OUT A WAY \nTO PLACE ALL DISKS FROM FIRST ROD TO SECOND ROD USING THE THIRD ROD\n";
  cout<<"\n\nEnter the Number of Disks: ";cin>>n;
  toh(n, 'A', 'B', 'C');
}
