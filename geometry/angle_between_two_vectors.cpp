/*
Angle between vectors

Input:
  The four numbers are the coordinates of two non-zero vectors.
Output:
  One number is the value of the unoriented angle between them with an accuracy of up to 
  the fifth sign after the decimal point from the interval [0, π].
*/

#include<bits/stdc++.h>
using namespace std;

double dist(int x,int y)
{
       return sqrt((double)(x*x+y*y));
}
int main()
{
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    double a=x1*x2+y1*y2;
    double b=dist(x1,y1)*dist(x2,y2);
    printf("%.12f",acos(a/b));
    return 0;
}
