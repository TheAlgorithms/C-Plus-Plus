#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

void print(vector<int> v, std::string s)
{
  std::cout << s << ":";
  for (auto x : v)
  {
    std::cout << x << " ";
  }
  std::cout << "\n";
}
vector<int> dp_sequence(int n)
{
  vector<int> dp = {0};
  vector<int> sequence;
  vector<int> operations = {1};
  if (n == 1)
  {
    sequence.push_back(1);
    return sequence;
  }
  for (int i = 2; i <= n; i++)
  {
    int res1 = 999999;
    int res2 = 999999;
    int res3 = 999999;
    res1 = dp[i - 2];
    if (i % 2 == 0)
    {
      res2 = dp[(i / 2) - 1];
    }
    if (i % 3 == 0)
    {
      res3 = dp[(i / 3) - 1];
    }
    if (res3 <= res2 && res3 <= res1)
    {
      operations.push_back(3);
      dp.push_back(res3 + 1);
    }
    else if (res2 <= res1 && res2 <= res3)
    {
      operations.push_back(2);
      dp.push_back(res2 + 1);
    }
    else if (res1 <= res2 && res1 <= res3)
    {
      operations.push_back(1);
      dp.push_back(res1 + 1);
    }
  }

  // sequence.push_back(start);
  int i = n;
  while (i >= 1)
  {
    sequence.push_back(i);
    if (operations[i - 1] == 1)
    {
      i -= 1;
    }
    else if (operations[i - 1] == 2)
    {
      i /= 2;
    }
    else
    {
      i /= 3;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}
vector<int> optimal_sequence(int n)
{
  std::vector<int> sequence;
  while (n >= 1)
  {
    sequence.push_back(n);
    if (n % 3 == 0)
    {
      n /= 3;
    }
    else if (n % 2 == 0)
    {
      n /= 2;
    }
    else
    {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main()
{
  int n;
  std::cin >> n;
  vector<int> sequence = dp_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i)
  {
    std::cout << sequence[i] << " ";
  }
}
