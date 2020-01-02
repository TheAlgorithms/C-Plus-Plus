// Program to check whether a number is an armstrong number or not
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, k, d, s = 0, rem;
  cout << "Enter a number:";
  cin >> n;
  int n1 = n,count = 0;
  while(n1 != 0){
	  count++;
	  n1 = n1/10;
  }
  d = n;
  while(n != 0){
	  rem = n%10;
	  s += pow(rem,count);
	  n = n/10;
  }
  if(s == d)
	  cout<<"yes, the number is an armstrong number";
  else
	  cout<<"no, the number is not an armstrong number";
  return 0;
}


