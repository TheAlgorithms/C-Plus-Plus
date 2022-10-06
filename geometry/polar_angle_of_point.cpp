/*
Polar angle of a point
  Input:
  Two numeric coordinates of a point that are not the same as the origin of the coordinate.
  
  Output:
  One number is the value of the polar angle in radians from the interval [0, 2π).
*/

#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
 
 
#define PI 3.141592
using namespace std;
double ans(int x,int y)
{
    double al=atan2(y, x);
    if (al<0){al+=2*PI;}
    return al;
}
 
 
int main()
{
    int x,y;
    cin>>x>>y;
    printf("%.12f",ans(x,y));
    return 0;
}
