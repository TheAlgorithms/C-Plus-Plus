/**
 * @file
 * @brief [dsu(Disjoint sets)](https://en.wikipedia.org/wiki/Disjoint-set-data_structure)
 * @details
 * dsu : It is a very powerful data structure which keeps track of different 
 * clusters(sets) of elements, these sets are disjoint(doesnot have a common element).
 * Disjoint sets uses cases : for finding connected components in a graph,
 * used in Kruskal's algorithm for finding Minimum Spanning tree.
 * Operations that can be performed:
 * 1) UnionSet(i,j): add(element i and j to the set)
 * 2) findSet(i): returns the representative of the set to which i belogngs to.
 * 3) getParents(i): prints the parent of i and so on and so forth.
 * Below is the class-based approach which uses the heuristic of union-ranks.
 * Using union-rank in findSet(i),we are able to get to the representative of i
 * in slightly delayed O(logN) time but it allows us to keep tracks of the parent of i.
 * @author [AayushVyasKIIT](https://github.com/AayushVyasKIIT)
 * @see dsu_path_compression.cpp
 */

#include <iostream> /// for IO operations
#include <vector>  /// for std::vector


using std::cout;
using std::endl;
using std::vector;

/**
 * @brief Disjoint sets union data structure, class based representation.
 * @param n number of elements
 */
class dsu{
    private:
        vector<int> p; ///<keeps track of the parent of ith element
        vector<int> depth; ///<tracks the depth(rank) of i in the tree
        vector<int> setSize;///<size of each chunk(set)
    public:
        /**
         * @brief constructor for initialising all data members 
         * @param n number of elements
         */
        explicit dsu(int n){
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
        /**
         * @brief Method to find the representative of the set to which i belongs to, T(n) = O(logN)
         * @param i element of some set
         * @returns representative of the set to which i belongs to
         */
        int findSet(int i){
            /// using union-rank
            while(i!=p[i]){
                i = p[i];
            }
            return i;
        }
        /**
         * @brief Method that combines two disjoint sets to which i and j belongs to and make 
         * a single set having a common representative.
         * @param i element of some set
         * @param j element of some set
         * @returns void
         */
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
        /**
         * @brief A utility function which check whether i and j belongs to same set or not
         * @param i element of some set
         * @param j element of some set
         * @returns `true` if element i and j are in same set
         * @returns `false` if element i and j are not in same set
         */
        bool isSame(int i,int j){
            if(findSet(i) == findSet(j)){
                return true;
            }
            return false;
        }
        /**
         * @brief Method to print all the parents of i, or the path from i to representative.
         * @param i element of some set
         * @returns void
         */
        void getParents(int i){
            while(p[i]!=i){
                cout << i << " ->";
                i = p[i];
            }
            cout << p[i] << endl;
        }
        
};

/**
 * @brief Main function
 * @returns 0 on exit 
 */
int main(){
    int n = 10; ///<number of elements
    dsu d(n+1); ///< object of class disjoint sets
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