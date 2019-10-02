#include<iostream>
using namespace std;

int lengthOfLongestSubsetWithZeroSum(int* arr, int n)
{
  int maxlen=0;
  for(int i=0;i<n;i++)
  {
    int sum=0;
    for(int j=i;j<n;j++)
    {
      sum+=arr[j];
      if(sum==0)
        maxlen=max(maxlen,j-i+1);
    }
  }
  return maxlen;
}

int main(){
  int size;
  
  cin >> size;
  int* arr = new int[size];
  for(int i = 0; i < size; i++){
    cin >> arr[i];
  }
  int ans = lengthOfLongestSubsetWithZeroSum(arr,size);
  cout << ans << endl;
  delete arr;
}


