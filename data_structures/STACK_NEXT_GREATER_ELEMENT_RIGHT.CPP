
#include <iostream>
#include<stack>

using namespace std;

int main()
{
    stack<int> st;
    int arr[]={1,4,2,3,4,2,4};
    int n=sizeof(arr)/sizeof(arr[0]);
    int i=n-2;
    int ans[n];
    ans[n-1]=-1;
    st.push(arr[n-1]);
    while(i>=0)
    {
        if(st.top()>arr[i])
        ans[i]=st.top();
        
        else{
            while(!st.empty() && st.top()<=arr[i])
            st.pop();
            if(st.empty())
            ans[i]=-1;
            else ans[i]=st.top();
        }
        st.push(arr[i]);
        i--;
    }
    
    for(int i=0;i<n;i++)
    cout<<ans[i]<<" ";
    

    return 0;
}