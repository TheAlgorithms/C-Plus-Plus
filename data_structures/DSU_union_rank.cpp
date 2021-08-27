#include <bits/stdc++.h>

using namespace std;

#define vi vector<int> 
class DSU{
    private:
        // p: keeps track of parent of i
        // depth: tracks the depth of i
        // setSize: size of each chunk(set)
        vi p,depth,setSize;
    public:
        //parameter : int n -> maximum number of items
        DSU(int n){
            p.assign(n,0);
            //initially all of them their own parents
            depth.assign(n,0);
            setSize.assign(n,0);
            for(int i=0;i<n;i++){
                p[i] = i;
                depth[i] = 0;
                setSize[i] = 1;
            }
        }
        int findSet(int i){
            //union rank i - > p[i]
            while(i!=p[i]){
                i = p[i];
            }
            return i;
        }
        //union of 2 sets
        void unionSet(int i,int j){
            //check if both belongs to same set or not
            if(isSame(i,j)){
                return;
            }
            //we find representative of the i and j
            int x = findSet(i);
            int y = findSet(j);

            //always keeping the min as x
            //in order to create a shallow tree
            if(depth[x]>depth[y]){
                swap(x,y);
            }
            //making the shallower tree' root parent of the deeper root
            p[x] = y;

            //if same depth then increase one's depth
            if(depth[x] == depth[y]){
                depth[y]++;
            }
            //total size of the resultant set
            setSize[y]+=setSize[x];
        }
        // checks if both belongs to same set
        bool isSame(int i,int j){
            if(findSet(i) == findSet(j)){
                return true;
            }
            return false;
        }
        
};

int main(){
    //number of items
    int n;cin>>n;

    DSU d(n+1);
    //perform operations here
    d.unionSet(2,4);
    d.unionSet(3,4);
    cout <<  d.findSet(2) <<endl;
}