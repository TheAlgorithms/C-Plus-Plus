#include <bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    stack<int> S;
    //Insert in stack
    for(int i=1;i<10;i++)
        S.push(i);

    //Pop from stack
    while(!S.empty()){
        cout<<S.top()<<" ";
        S.pop();
    }
}
