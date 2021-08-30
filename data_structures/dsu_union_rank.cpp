#include <iostream>
#include <vector>


using std::cout;
using std::endl;
using std::vector;

class DSU{
    private:
        // p: keeps track of parent of i
        // depth: tracks the depth of i
        // setSize: size of each chunk(set)
        vector<int> p,depth,setSize;
    public:
        //parameter : int n -> maximum number of items
        explicit DSU(int n){
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
                std::swap(x,y);
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
        void getParents(int i){
            while(p[i]!=i){
                cout << i << " ->";
                i = p[i];
            }
            cout << p[i] << endl;
        }
        
};

int main(){
    int n = 10; 
    //n: number of items
    DSU d(n+1);
    d.unionSet(2,1); //performs union operation on 1 and 2
    d.unionSet(1,4);
    d.unionSet(8,1);
    
    d.unionSet(3,5);
    d.unionSet(5,6);
    d.unionSet(5,7);

    d.unionSet(9,10);
    d.unionSet(2,10);

    //keeping track of the changes using parent pointers
    d.getParents(7);
    d.getParents(2);


    return 0;
}