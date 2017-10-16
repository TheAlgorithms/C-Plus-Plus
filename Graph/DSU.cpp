class DSU{
public:
    int find(int* parent,int val) {
        if(parent[val]!=val)
            parent[val]=find(parent,parent[val]);//find the leader of the group of this node
        return parent[val];
    }
    
    void unionSet(int* parent,int a,int b) {
        int ap = find(parent,a);
        int bp = find(parent,b);
        if(ap!=bp)
            parent[bp]=ap; //make 'a's parent as the leader of b's group as well.
    }
    int unionSameNodes(vector<vector<int>>& M) {
        int n = M.size();
        int parent[n]; //stores parent for each node
        for(int i=0;i<n;i++) parent[i]=i; //initially every node is individual
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(M[i][j] && parent[i]!=parent[j]) {
                    unionSet(parent,i,j); // if there is an edge, but parents are different that means these
					  // two nodes(and hence the tress asociated with them) can be clubbed
                }
            }
        }
	//this now counts number of components.
        int count=0;
        for(int i=0;i<n;i++) {
           if(parent[i]==i) count++;
        }
        return count;
    }
};