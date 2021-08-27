#include <bits/stdc++.h>

using namespace std;

#define vi vector<int> 
class DSU{
    private:
        vi p,depth,setSize;
    public:
        DSU(int n){
            p.assign(n,0);
            depth.assign(n,0);
            setSize.assign(n,0);
            for(int i=0;i<n;i++){
                p[i] = i;
                depth[i] = 0;
                setSize[i] = 1;
            }
        }
        int findSet(int i){
            while(i!=p[i]){
                i = p[i];
            }
            return i;
        }
        void unionSet(int i,int j){
            if(isSame(i,j)){
                return;
            }
            int x = findSet(i);
            int y = findSet(j);

            if(depth[x]>depth[y]){
                swap(x,y);
            }
            p[x] = y;
            if(depth[x] == depth[y]){
                depth[y]++;
            }
            setSize[y]+=setSize[x];
        }
        bool isSame(int i,int j){
            if(findSet(i) == findSet(j)){
                return true;
            }
            return false;
        }
        
};

int main(){
    int n;cin>>n;

    DSU d(n+1);
    d.unionSet(2,4);
    d.unionSet(3,4);
    cout <<  d.findSet(2) <<endl;
}