#include <iostream>
int main()
{
  int i, j, m, n;
  std::cout << "Enter size of array 1:";
  std::cin >> m;
  std::cout << "Enter size of array 2:";
  std::cin >> n;
  int a[m];
  int b[n];
  std::cout << "Enter elements of array 1:";
  for (i = 0; i < m; i++)
    std::cin >> a[i];
  for (i = 0; i < n; i++)
    std::cin >> b[i];
  i = 0;
  j = 0;
  while ((i < m) && (j < n))
  {
    if (a[i] < b[j])
      i++;
    else if (a[i] > b[j])
      j++;
    else
    {
      std::cout << a[i++] << " ";
      j++;
    }
  }
  return 0;
}
