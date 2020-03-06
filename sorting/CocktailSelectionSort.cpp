//Returns Sorted elements after performing Cocktail Selection Sort
//It is a Sorting algorithm which chooses the minimum and maximum element in an array simultaneously,
//and swaps it with the lowest and highest available position iteratively or recursively

#include <iostream>
using namespace std;

//Iterative Version

void CocktailSelectionSort(vector<int> &vec, int low, int high)
{
  while (low <= high)
  {
    int minimum = vec[low];
    int minimumindex = low;
    int maximum = vec[high];
    int maximumindex = high;

    for (int i = low; i <= high; i++)
    {
      if (vec[i] >= maximum)
      {
        maximum = vec[i];
        maximumindex = i;
      }
      if (vec[i] <= minimum)
      {
        minimum = vec[i];
        minimumindex = i;
      }
    }
    if (low != maximumindex || high != minimumindex)
    {
      swap(vec[low], vec[minimumindex]);
      swap(vec[high], vec[maximumindex]);
    }
    else
    {
      swap(vec[low], vec[high]);
    }

    low++;
    high--;
  }
}

//Recursive Version

void CocktailSelectionSort(vector<int> &vec, int low, int high)
{

  if (low >= high)
    return;

  int minimum = vec[low];
  int minimumindex = low;
  int maximum = vec[high];
  int maximumindex = high;

  for (int i = low; i <= high; i++)
  {
    if (vec[i] >= maximum)
    {
      maximum = vec[i];
      maximumindex = i;
    }
    if (vec[i] <= minimum)
    {
      minimum = vec[i];
      minimumindex = i;
    }
  }
  if (low != maximumindex || high != minimumindex)
  {
    swap(vec[low], vec[minimumindex]);
    swap(vec[high], vec[maximumindex]);
  }
  else
  {
    swap(vec[low], vec[high]);
  }

  CocktailSelectionSort(vec, low + 1, high - 1);
}

//main function, select any one of iterative or recursive version

int main()
{

  int n;
  cout << "Enter number of elements\n";
  cin >> n;
  std::vector<int> v(n);
  cout << "Enter all the elements\n";
  for (int i = 0; i < n; ++i)
  {
    cin >> v[i];
  }

  CocktailSelectionSort(v, 0, n - 1);
  cout << "Sorted elements are\n";
  for (int i = 0; i < n; ++i)
  {
    cout << v[i] << " ";
  }

  return 0;
}
