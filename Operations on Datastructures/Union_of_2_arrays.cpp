#include <iostream>
int main()
{
  int m, n, i = 0, j = 0;
  std::cout << "Enter size of both arrays:";
  std::cin >> m >> n;
  int a[m];
  int b[n];
  std::cout << "Enter elements of array 1:";
  for (i = 0; i < m; i++)
    std::cin >> a[i];
  std::cout << "Enter elements of array 2:";
  for (i = 0; i < n; i++)
    std::cin >> b[i];
  i = 0;
  j = 0;
  while ((i < m) && (j < n))
  {
    if (a[i] < b[j])
      std::cout << a[i++] << " ";
    else if (a[i] > b[j])
      std::cout << b[j++] << " ";
    else
    {
      std::cout << a[i++];
      j++;
    }
  }
  while (i < m)
    std::cout << a[i++] << " ";
  while (j < n)
    std::cout << b[j++] << " ";
  return 0;
}
