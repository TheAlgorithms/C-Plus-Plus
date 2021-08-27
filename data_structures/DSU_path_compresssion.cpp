#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

class DSU{
    private:
        vi p,depth,setSize,maxElement,minElement;
    public:
        DSU(int n){
            p.assign(n,0);
            //initially all of them are their parents.
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
            //path compression
            return (p[i] = findSet(p[i]));
        }
        //union of 2 sets
        void UnionSet(int i,int j){
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
            
            if(depth[x] == depth[y]){
                depth[y]++;
            }
            //total size of the resultant set.  
            setSize[y] += setSize[x];
            maxElement[y] = max(maxElement[x],maxElement[y]);
            minElement[y] = min(minElement[x],minElement[y]);
        }
        //checks if both sets equal

        bool isSame(int i,int j){
            if(findSet(i) == findSet(j)){
                return true;
            }
            return false;
        }
        void get(int i){
            cout << get_min(i) << " " << get_max(i) << " " <<size(i) << endl; 
        }
        //number of elements of each set
        int size(int i){
            return setSize[findSet(i)];
        }
        int get_max(int i){
            return maxElement[findSet(i)];
        }
        int get_min(int i){
            return minElement[findSet(i)];
        }

};

int main(){
    std::ios_base::sync_with_stdio(0);std::cin.tie(0);std::cout.tie(0);
    int n,q;cin>>n;cin>>q;

    DSU d(n+1);

    while(q--){
        string op;cin>>op;
        if(op == "union"){
            int i,j;
            cin >> i >> j;
            d.UnionSet(i,j);
        }else{
            int i;
            cin >> i;
            d.get(i);
        }
    }
    
    
}
