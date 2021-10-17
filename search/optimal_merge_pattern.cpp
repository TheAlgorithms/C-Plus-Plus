/**
Node represents a file with a given size also given nodes are greater than 2 

1. Add all the nodes in a priority queue (Min Heap).{node.weight = file size}
2.Initialize count = 0 // variable to store file computations.
3. Repeat while (size of priority Queue is greater than 1) 
    1. create a new node
    2. new node = pq.poll().weight+pq.poll().weight;//pq denotes priority queue, remove 1st smallest and 2nd smallest element and add their weights to get a new node
    3. count += node.weight
    4. add this new node to priority queue; 
 
4. count is the final answer
 **/

#include<bits/stdc++.h>
using namespace std;
#define int long long
 
signed main() {
    int n;
    cout<<"Enter size of array-"<<endl;
     cin >> n;
 
    vector<int> a(n);
    cout<<"Enter array of "<<n<<" elements"<<endl;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
 
    priority_queue<int, vector<int>, greater<int>> minheap;
    for(int i=0; i<n; i++) {
        minheap.push(a[i]);
    }
 
    int ans = 0;
 
    while(minheap.size() > 1) {
        int e1 = minheap.top();
        minheap.pop();
        int e2 = minheap.top();
        minheap.pop();
 
        ans += e1 + e2;
        minheap.push(e1 + e2);
    }
 cout<<"Minimum Value-  "<<endl;
    cout << ans << endl;
    return 0;
}
