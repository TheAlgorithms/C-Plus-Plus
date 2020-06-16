#include<iostream>
#include<cmath>
#include<deque>
#include<stack>
#include<vector>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include <cstdio>
using std::cin;
using std::cout;
using std::vector;
using std::endl;
vector<int>v;
vector<int>s1;
vector<int>s2;
vector<int>s3;
template <class X>

void comp(X x) {
  if (s1.size()+s2.size()+s3.size() > x && s1.size()+s2.size() <= x) {
    sort(s3.begin(), s3.end());
    cout << s3[x-s2.size()-s1.size()] << " is the " << x+1;
    if (x < 1) {
      cout << "st";
    } else if (x < 2) {
      cout << "nd";
    } else if (x < 3) {
      cout << "rd";
    } else {
      cout << "th";
    }
    cout << " element from the front.\n";
  } else if (s1.size()+s2.size() > x && s1.size() <= x) {
    sort(s2.begin(), s2.end());
    cout << s2[x-s1.size()] << " is the " << x+1;
    if (x < 1) {
      cout << "st";
    } else if (x < 2) {
      cout << "nd";
    } else if (x < 3) {
      cout << "rd";
    } else {
      cout << "th";
    }
    cout << " element from the front.\n";
  } else if (s1.size() > x) {
    sort(s1.begin(), s1.end());
    cout << s1[x] << " is the " << x+1;
    if (x < 1) {
      cout << "st";
    } else if (x < 2) {
      cout << "nd";
    } else if (x < 3) {
      cout << "rd";
    } else {
      cout << "th";
    }
    cout << " element from the front.\n";
  } else {
    cout << x+1 << " is an invalid location.\n";
  }
}

int main() {
  unsigned int seed = 1;
  int set_num;
  cout << "How many elements should be in the set? ";
  cin >> set_num;
  for (int i=0; i < set_num; i++) {
    v.push_back(rand_r(&seed)%1000);
  }
  for (int r : v) {
    cout << r << " ";
  }
  int median = rand_r(&seed)%1000;
  cout << "\nmedian = " << median << endl;
  for (int i=0; i < set_num; i++) {
    if (v.back() == median) {
      s2.push_back(v.back());
    } else if (v.back() < median) {
      s1.push_back(v.back());
    } else {
      s3.push_back(v.back());
    }
    v.pop_back();
  }
  int x;
  cout << "enter the no. to be searched from beginning: ";
  cin >> x;
  comp(x-1);
  return 0;
}
