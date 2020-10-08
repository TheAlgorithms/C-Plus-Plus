// Knowing all sorting techniques are important.And knowing inbulit sort is important too for solving complex programs.
// Though inbulit sort which is included in  ALGORITHMS  header file sort in  increasing order.You can change the order by just
// passing compare function as a parameter in sort function.
// Inbulit sort function take 2 parameters:sort[a,a+n) =>where,a i.e first value is included and end point a+n is not included.
//Inside comparator function it's written as:if(a[j]<a[j+1]){Swap} and we are just overwriting this function saying =
// if(comp(a[j],a[j+1])) to compare it.
#include<iostream>
#include<algorithms>
using namespace std;

bool myCompare(int a,int b){
    //for changing  order in decreasing order.
    //if you want it to follow increasing order change it to a<b;
    return a>b;
}

int main(){
    int a[]={2,3,1,4,5};
    int n=sizeof(a)/sizeof(int);
    sort(a,a+n,myCompare);
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}