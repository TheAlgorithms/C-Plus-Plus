#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    queue<int> Q;
    //Insert in queue
    for(int i=1;i<10;i++)
        Q.push(i);

    //Pop from queue
    while(!Q.empty()){
        cout<<Q.front()<<" ";
        Q.pop();
    }
}
