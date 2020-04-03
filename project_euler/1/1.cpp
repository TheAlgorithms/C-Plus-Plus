#include<iostream>
#include<math.h>

using namespace std;

void _3or5(int num)
{   
    int sum=0;       // You can change the data type here if this program is needed further :)   
    for(int i=3;i<num;++i)
    {
        if(i%15 == 0)
        {   
            sum += i;
        }
        else if(i%3 == 0)
        {   
            sum += i;
        }
        else if(i%5 == 0)
        {
            sum += i;
        }
    }
    cout<<sum;
}

int main()
{
    int n=1000; // we are given to find the number 1000 in the problem
    _3or5(n);
    return 0;
}
