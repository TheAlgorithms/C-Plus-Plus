/* Given array with each element occuring twice and one unique element. Find unique element. */
/* Using Bit Manipulation */

#include<iostream>

int main() {
  int n , ans = 0;
  std::cout<< "Enter number of elements :";
  std::cin>>n;
  for ( int i = 0 ; i < n ; ++i ) {
    int no;
    // Performing xor of a number with itself gives 0
    // Performing xor of a number with 0 gives the number
    ans = ans ^ no;
  }
  std::cout << "Unique element is:" << ans;
  return 0;
}
