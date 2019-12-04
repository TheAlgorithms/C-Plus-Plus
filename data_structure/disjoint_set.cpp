#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class DisjointSet { //to represent disjoint set
   unordered_map<int, int> parent;
   public:
   void makeSet(vector<int> const &wholeset){
   //perform makeset operation
      for (int i : wholeset) // create n disjoint sets (one for each item)
      parent[i] = i;
   }
   int Find(int l) { // Find the root of the set in which element l belongs
      if (parent[l] == l) // if l is root
         return l;
      return Find(parent[l]); // recurs for parent till we find root
   }
   void Union(int m, int n) { // perform Union of two subsets m and n  
      int x = Find(m);
      int y = Find(n);
      parent[x] = y;
   }
};
void print(vector<int> const &universe, DisjointSet &dis) {
   for (int i : universe)
   cout << dis.Find(i) << " ";
   cout << '\n';
}
int main() {
   vector<int> wholeset = { 6,7,1,2,3,10,15,5 }; // items of whole set
   DisjointSet dis; //initialize DisjointSet class
   dis.makeSet(wholeset); // create individual set of the items of wholeset
   dis.Union(7, 6); // 7,6 are in same set
   dis.Union(7,10);
   print(wholeset, dis);
   if (dis.Find(7) == dis.Find(10)) // if they are belong to same set or not.
      cout<<"Yes"<<endl;
   else
      cout<<"No"<<endl;
   if (dis.Find(3) == dis.Find(4))
      cout<<"Yes"<<endl;
   else
      cout<<"No"<<endl;
   return 0;
}
