#include<bits/stdc++.h>
using namespace std;
void stockspan(int arr[],int n){
    stack<int>s;
    s.push(0);
    cout<<1<<" ";
    for (int i = 1; i < n; i++)
    {
        while (!s.empty() && arr[s.top()]<arr[i])
        {
            s.pop();
        }
        int span=s.empty()==false?i-s.top():i+1;
        cout<<span<<" ";
        s.push(i);
    }
    
}
int main()
{
    int arr[]={73,76,72,69,71,75,74,73};
    int n=sizeof(arr)/sizeof(arr[0]);
    stockspan(arr,n);
return 0;
}
