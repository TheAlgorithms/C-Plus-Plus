//program to check whether a number is an armstrong number or not
#include<iostream>
#include<Math.h>
using namespace std;

int main()
{
	int n, tmp, numPlace=1, k, s=0, unit;
	cout << "Enter a decimal number: ";
	cin >> n;
	if(n<=0)
    {
        cout << "n must > 0";
        return -1;
    }else if(n<10)
    {
		cout << n << " is an armstrong number!";
        return 0;
    }

    tmp = n;
    while(1)
    {
        tmp /= 10;
        if(tmp != 0)
        {
            numPlace++;
        }else
        {
            break;
        }
    }

    tmp = n;
    while(tmp>0)
    {
        unit = tmp % 10;
        s += (int)pow(unit, numPlace);
        tmp /= 10;
    }

  if(s==n)
   cout<<n<<" is an armstrong number";
  else
   cout<<n<<" is not an armstrong number";
}

