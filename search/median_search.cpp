#include<iostream>
#include<math.h>
#include<deque>
#include<stack>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
vector<int>v;
vector<int>s1;
vector<int>s2;
vector<int>s3;
template <class X>
void comp(X x)
{
    if(s1.size()>=x && s1.size()+s2.size()<x)
    {
        cout<<s2[0]<<" is the "<<x+1<<"th element from front";
    }
    else if(s1.size()>x)
    {
        sort(s1.begin(),s1.end());
        cout<<s1[x]<<" is the "<<x+1<<"th element from front";
    }
    else if(s1.size()+s2.size()<=x && s3.size()>x)
    {
        sort(s3.begin(),s3.end());
        cout<<s3[x-s1.size()-s2.size()]<<" is the "<<x+1<<"th element from front";
    }
    else
    {
        cout<<x+1<<" is invalid location";
    }
}
int main()
{
    for(int i=0;i<1000;i++)
    {
        v.push_back(rand()%1000);
    }
    for(int r:v)
    {
        cout<<r<<" ";
    }
    int median=rand()%1000;
    cout<<"\nmedian="<<median<<endl;
    int avg1,avg2,avg3,sum1=0,sum2=0,sum3=0;
    for(int i=0;i<1000;i++)
    {
        if(v.back()==v[median])
        {
            avg1=sum1+v.back();
            s2.push_back(v.back());
        }
        else if(v.back()<v[median])
        {
            avg2=sum2+v.back();
            s1.push_back(v.back());
        }
        else
        {
            avg3=sum3+v.back();
            s3.push_back(v.back());
        }
        v.pop_back();
    }
    int x;
    cout<<"enter the no. to be searched form begining:- ";
    cin>>x;
    comp(x-1);
    return 0;
}
