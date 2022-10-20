#include <iostream>
using namespace std;
 
int NonReapeating(vector<int> arr, int n)
{
    int ans = arr[0];
    for (int i = 1; i < n; i++)
        ans ^= arr[i];
 
    return ans;
}
 
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &it: arr){
      cin >> it;
    }
    cout << "Non reapeating element is "
         << NonReapeating(arr, n);
    return 0;
}
