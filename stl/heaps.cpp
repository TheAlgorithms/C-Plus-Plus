#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    priority_queue<int> maxHeap;

    //Insert in a maxHeap
    maxHeap.push(1);
    maxHeap.push(3);
    maxHeap.push(10);
    maxHeap.push(5);

    //Accessing largest element in a maxHeap
    cout<<maxHeap.top()<<endl;

    //Popping out elements from the maxHeap
    maxHeap.pop();
    cout<<maxHeap.top()<<endl;

}
