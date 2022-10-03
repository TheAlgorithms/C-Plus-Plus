// in questions involving count number of pairs of i,j such that j>i and nums[i] & nums[j] satisfy some condition then we can implement a function in the combining part of merge sort and get our answer.
// plus kahi 2^31 ki wajah se overflow ki condition aa rhi ho to
// for comparison long long x=har ke pehle (long long) likh ke operations karo and it would work

// basic template just do things according to two pointer in merge function
//and as also the arrays are sorted possibilites of binary search also opens giving rights to 
//log(n)^2 solutions also which might pass

//https://leetcode.com/problems/reverse-pairs/
class Solution
{
public:
  int mergesort(int l, int mid, int r, vector<int> &nums)
  {
    vector<int> temp(r - l + 1, 0);
    int temp_ct = 0;
    int i = l;
    int j = mid + 1;
    int cnt = 0;
    while (i <= mid && j <= r)
    {
      long long x = (2LL * (long long)nums[j]);
      long long y = nums[i];
      if (y > x)
      {
        temp_ct += (mid - i + 1);
        j++;
      }
      else
        i++;
    }
    i = l;
    j = mid + 1;
    while (i <= mid && j <= r)
    {
      if (nums[i] >= nums[j])
      {
        temp[cnt] = nums[j];
        j++;
        cnt++;
      }
      else
      {
        temp[cnt] = nums[i];
        i++;
        cnt++;
      }
    }
    while (i <= mid)
    {
      temp[cnt] = nums[i];
      i++;
      cnt++;
    }
    while (j <= r)
    {
      temp[cnt] = nums[j];
      j++;
      cnt++;
    }
    for (int i = l; i <= r; i++)
      nums[i] = temp[i - l];
    return temp_ct;
  }
  int merge(int l, int r, vector<int> &nums)
  {
    int x = 0, y = 0, z = 0;
    if (r > l)
    {
      int mid = (l + r) / 2;
      x = merge(l, mid, nums);
      y = merge(mid + 1, r, nums);
      z = mergesort(l, mid, r, nums);
    }
    return x + y + z;
  }
  int reversePairs(vector<int> &nums)
  {
    int n = nums.size();
    int sum = merge(0, n - 1, nums);
    return sum;
  }
};