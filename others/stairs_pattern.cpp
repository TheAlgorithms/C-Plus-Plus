/*
This program is use to print the following pattern
   **
   **
  ****
  ****
 ******
 ******
********
********
where number of pairs line is given by user 
*/
#include <iostream>  
using namespace std;
int main()
{
	int l, st = 2, x, r, z, n, sp;
	cout << "enter Index ";
	cin >> x;
	z = x;
	for (r = 1; r <= x; r++)
	{
		z = z - 1;
		for (n = 1; n <= 2; n++)
		{
			for (sp = 1; sp <= z; sp++)
			{
				cout << " ";
			}
			for (l = 1; l <= st; l++)
			{
				cout << "*";
			}
			cout << endl;
		}
		st = st + 2;
	}
}
