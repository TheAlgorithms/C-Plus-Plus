#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

//Disjoint set union 
class DSU{
    private:
        // p: keeps track of parent of i
        // depth: tracks the depth of i
        // setSize: size of each chunk(set)
        // maxElement : max of each set, using maxElement[representative]
        // minElement : min of each set, using minElement[representative]
        vi p,depth,setSize,maxElement,minElement;
    public:
        // parameter : int n -> maximum number of items
        DSU(int n){
            p.assign(n,0);
            //initially all of them are their own parents.
            for(int i=0;i<n;i++){
                p[i] = i;
            }
            //initially all have depth =0
            depth.assign(n,0);
            maxElement.assign(n,0);
            minElement.assign(n,0);
            for(int i=0;i<n;i++){
                depth[i] = 0;
                maxElement[i] = i;
                minElement[i] = i;
            }
            setSize.assign(n,0);
            //initially set size will be 1
            for(int i=0;i<n;i++){
                setSize[i]=1;
            }
        }

        //returns the leader/representative of the set
        int findSet(int i){
            if(p[i]==i){
                return i;
            }
            //path compression i -> root(representative)
            return (p[i] = findSet(p[i]));
        }
        //union of 2 sets
        void UnionSet(int i,int j){
            //check if both belongs to same set or not
            if(isSame(i,j)){
                return;
            }

            //we find the representative of the i and j
            int x = findSet(i);
            int y = findSet(j);

            //always keeping the min as x
            //shallow tree
            if(depth[x]>depth[y]){
                swap(x,y);
            }
            //making the shallower root's parent the deeper root
            p[x] = y;
            
            //if same depth then increase one's depth
            if(depth[x] == depth[y]){
                depth[y]++;
            }
            //total size of the resultant set.  
            setSize[y] += setSize[x];
            //changing the maximum elements
            maxElement[y] = max(maxElement[x],maxElement[y]);
            minElement[y] = min(minElement[x],minElement[y]);
        }
        //checks if both belongs to same set
        bool isSame(int i,int j){
            if(findSet(i) == findSet(j)){
                return true;
            }
            return false;
        }
        //returns min max size of i's set
        void get(int i){
            cout << get_min(i) << " " << get_max(i) << " " <<size(i) << endl; 
        }
        //number of elements of each set
        int size(int i){
            return setSize[findSet(i)];
        }
        //returns max of the set whose part is i
        int get_max(int i){
            return maxElement[findSet(i)];
        }
        //returns min of the set whose part is i
        int get_min(int i){
            return minElement[findSet(i)];
        }

};
/*
test case#1:
        5 11
        union 1 2
        get 3
        get 2
        union 2 3
        get 2
        union 1 3
        get 5
        union 4 5
        get 5
        union 4 1
        get 5
*/
/*
output case#1:
        3 3 1
        1 2 2
        1 3 3
        5 5 1
        4 5 2
        1 5 5
*/
int main(){
    std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int n,q;cin>>n;cin>>q;
    //n: number of items
    //q: number of queries to be made
    DSU d(n+1);

    while(q--){
        string op;cin>>op;
        if(op == "union"){
            int i,j;
            cin >> i >> j;
            d.UnionSet(i,j); //performs union operation on i and j
        }else{
            int i;
            cin >> i;
            d.get(i); //print min max and size of set.
        }
    }
    
    
}
