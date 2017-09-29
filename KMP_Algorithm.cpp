// http://www.spoj.pl/problems/NHAY/
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

void kmp(const string &needle, const string &haystack) {
  int m = needle.size();
  vector<int> border(m + 1);
  border[0] = -1;
  for (int i = 0; i < m; ++i) {
    border[i+1] = border[i];
    while (border[i+1] > -1 and needle[border[i+1]] != needle[i]) {
      border[i+1] = border[border[i+1]];
    }
    border[i+1]++;
  }

  int n = haystack.size();
  int seen = 0;
  for (int i = 0; i < n; ++i){
    while (seen > -1 and needle[seen] != haystack[i]) {
      seen = border[seen];
    }
    if (++seen == m) {
      printf("%d\n", i - m + 1);
    seen = border[m]; // There are no more characters in needle, so with the next input character let's try with the border of the whole needle.
    }
  }
}

int main(){
  int m;
  bool first = true;
  while (cin >> m) {
    if (!first) puts("");
    first = false;

    string needle; getline(cin, needle);
    getline(cin, needle);
    string haystack;
    getline(cin, haystack);
    kmp(needle, haystack);
  }
  return 0;
}