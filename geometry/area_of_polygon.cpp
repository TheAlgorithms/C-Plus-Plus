/*
The area of a polygon
Input:
  The first line contains one number N (3 <= N <= 100 000). The reference is to be reliedly
  bypass clockwise or counterclockwise.
  All coordinates are integers, modulo not exceeding 10^4.
Output:
  One number is the area of the reduced polygon.
*/

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, x[100050], y[100050], a=0, b=0;
    cin>>n;
  
    for(int i=0;i<n;i++)
    {
            cin>>x[i]>>y[i];
    }
    x[n]=x[0];
    y[n]=y[0];
     
    for(int i=0;i<n;i++)
    {
            a+=(x[i]*y[i+1]);
            b+=(y[i]*x[i+1]);
    }
    double ans=(double)abs(b-a)/2;
    printf("%.5f",ans);
    return 0;
}
