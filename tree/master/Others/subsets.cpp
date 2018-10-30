#include<iostream>
#include<vector>
using namespace std;
vector<int> subset;
vector<vector<int> > allsubsets;


void bit_search(vector<int> &a,int n){
  for(int i=0;i<(1<<n);i++){
    vector<int> subset;
    for(int j=0;j<n;j++){
      if(i&(1<<j)) subset.push_back(a[j]);
    }
    allsubsets.push_back(subset);
  }
}

int main(){
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0;i<n;i++){
    cin >> a[i];
  }
  cout << "Iterative bit-search:\n";
  bit_search(a,n);
  for(auto i=allsubsets.begin();i!=allsubsets.end();i++){
    cout << "{ ";
    for(int j=0;j<(*i).size();j++){
      cout << (*i)[j] << ' ';
    }
    cout << "}\n";
  }
  return 0;
}
