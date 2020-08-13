
/** Author: Aniruthan R
 * @email: aniruth11052000@gmail.com
 * @CodeChef: aneee004
 * @CodeForces: aneee
 * 
*/

#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include<list>
#include<math.h>
#include<assert.h>
#include<algorithm>
#include<numeric>
using namespace std;

/* ----------------------------------README -------------------------------------- */

/* Heavy-Light Decomposition is a technique on trees, that supports the following:
 * 1: Update node s, with a value v
 * 2: Return the (sum) of all node values on the simple path from a to b
 * (sum) can also be replced with XOR, OR, AND, min, or max
 *
 * The update is done in O(log n) time, and
 * the query is done in O(log^2 n) time with HLD
 * where, n is the number of nodes
 *
 * The template type is the data type of the value stored in the nodes.
 * If a non-primitive data-type is used as a template, 
 * the coressponding operators must be overloaded.
 *
 * An HLD object can only be created with a constant number of nodes, and
 * it cannot be changed later. Creaty an empty instance is not supported.
 *
 * To start answering updates and queries,
 * 1. Create an instance of HLD<X> object (obj), with the required data type.
 * 2. Read in the edge/parent information and update it with obj.add_edge().
 * Note: The edges addes must be 0 indexed.
 * 3. Call obj.init() to populate the required information for supporting operations.
 * 4. Call obj.update(node, new_val), to update the value at index 'node' to the new value.
 * Note: node must be 0 indexed
 * 5. Call obj.query(a, b) to get the (sum) of node values in the simple path from a to b.
 * Note: a and b, must be 0 indexed.
 *
 * Sample I/O at the bottom.
 * */

/* A Basic Tree, which supports binary lifting */
template<typename X>
struct Tree {
private:
	/* 
	 * Deleting the default constructor
	 * An instance can only be created with the number of nodes
	*/
	Tree() {}
protected:
	vector<list<int>> t_adj;
	const int t_nodes, t_maxlift;
	vector<vector<int>> t_par;
	vector<int> t_depth, t_size;

	/* Defaults:
	 * t_node indexing are zero based
	 * t_root is 0
	 * depth of root_node is 0
	*/
	
	void dfs_size(int u, int p = -1) {
		for(const int& v : t_adj[u]) if(v^p) {
			dfs_size(v, u);
			t_size[u] += t_size[v];
		}
	}

	void dfs_lca(int u, int p = -1) {
		t_par[u][0] = p;
		if(p != -1) t_depth[u] = 1 + t_depth[p];
		for(int k = 1; k < t_maxlift; k++) {
			if(t_par[u][k-1] != -1) {
				t_par[u][k] = t_par[t_par[u][k-1]][k-1];
			}
		}

		for(const int& v: t_adj[u]) if(v^p) {
			dfs_lca(v, u);
		}
	}

public:
	int t_root;
 	vector<X> t_val;
	Tree(int nodes) 
		: t_nodes(nodes), t_maxlift((int)floor(log2(nodes)) + 1) {
		/* Initialize and resize all the vectors */
		t_root = 0; /* Default */
		t_adj.resize(t_nodes);
		t_par.assign(t_nodes, vector<int>(t_maxlift, -1));
		t_depth.assign(t_nodes, 0);
		t_size.assign(t_nodes, 1);
		t_val.resize(t_nodes);
	}

	void add_edge(const int u, const int v) {
		t_adj[u].push_back(v);
		t_adj[v].push_back(u);
	}

	/* Initialization, sizes and parents */
	void init() {
		assert(t_nodes > 0);
		dfs_size(t_root);
		dfs_lca(t_root);
	}


	/* Supports:
	 * lift :- lift a node k units up the tree
	 * kth_ancestor :- returns the kth ancestor
	* lca :- returns the least common ancestor
	*/

	/* in place lift */
	void lift(int& p, int dist) {
		for(int k = 0; k < t_maxlift; k++) {
			if(p == -1) return;
			if(dist & 1) {
				p = t_par[p][k];
			}
			dist >>= 1;
		}
	} 
	
	/* returns the kth ancestor */
	int kth_ancestor(int p, const int& dist) {
		lift(p, dist);
		return p;
	}

	/* returns the least common ancestor */
	int lca(int a, int b) {
		assert(a >= 0 and b >= 0 and a < t_nodes and b < t_nodes);
		if(t_depth[a] > t_depth[b]) {
			lift(a, t_depth[a] - t_depth[b]);
		}
		if(t_depth[b] > t_depth[a]) {
			lift(b, t_depth[b] - t_depth[a]);
		}
		if(a == b) return a;
		for(int k = 0; k < t_maxlift; k++) {
			if(t_par[a][k] != t_par[b][k]) {
				a = t_par[a][k];
				b = t_par[b][k];
			}
		}
		return t_par[a][0];
	}
};

/* Segment Tree, to store heavy chains */
template<typename X>
struct SG {
public:
	/* Change the sret_init, based on requirement:
	 * Sum Query: 0 (Default)
	 * XOR Query: 0 (Default)
	 * Min Query: Infinity 
	 * Max Query: -Infinity
	*/
	X sret_init = 0;
	X combine(X lhs, X rhs) {
		return lhs + rhs;
	}
protected:
	/* Everything here is protected,
	 * and can only be acced thought the methods,
	 * in the derived class.
	*/
	vector<X> s_tree;
	int s_size;


	/* Construction requires a size */
	SG(int size) {
		s_size = size;
		s_tree.assign(2*s_size, 0ll);
	}

	/* update a segment tree node value */
	void update(int p, X v) {
		for(p += s_size; p > 0; p >>= 1) s_tree[p] += v;
	}

	/* make a segment tree range query */
	X query(int l, int r) {
		X lhs = sret_init, rhs = sret_init;
		for(l += s_size, r += s_size + 1; l < r; l >>= 1, r >>= 1) {
			if(l & 1) lhs = combine(lhs, s_tree[l++]);
			if(r & 1) rhs = combine(s_tree[--r], rhs);
		}
		return combine(lhs, rhs);
	}
};

/* The Heavy-Light Decomposition class */
template<typename X>
struct HLD : public Tree<X>, public SG<X> {
private:
	vector<int> h_label, h_heavychlid, h_parent;

	/* Utility functions */
	void dfs_hc(int u, int p = -1) {
		int hc_size = -1, hc_id = -1;
		for(const int& v : Tree<X>::t_adj[u]) if(v^p) {
			dfs_hc(v, u);
			if(Tree<X>::t_size[v] > hc_size) {
				hc_size = Tree<X>::t_size[v];
				hc_id = v;
			}
		}
		h_heavychlid[u] = hc_id;
	}

	void dfs_par(int u, int p = -1) {
		if(h_heavychlid[u] != -1) {
			h_parent[h_heavychlid[u]] = h_parent[u];
			dfs_par(h_heavychlid[u], u);
		}
		for(const int& v : Tree<X>::t_adj[u]) if(v^p and v^h_heavychlid[u]) {
			dfs_par(v, u);
		}
	}

	void dfs_labels(int u, int p = -1) {
		static int label = 0;
		h_label[u] = label++;
		if(h_heavychlid[u] != -1) dfs_labels(h_heavychlid[u], u);
		for(const int& v : Tree<X>::t_adj[u]) if(v^p and v^h_heavychlid[u]) {
			dfs_labels(v, u);
		}
	}

	X chain_query(int a, int b) {
		X ret = SG<X>::sret_init;
		if(Tree<X>::t_depth[a] < Tree<X>::t_depth[b]) swap(a, b);
		while(Tree<X>::t_depth[a] >= Tree<X>::t_depth[b]) {
			int l = h_label[h_parent[a]];
			int r = h_label[a];
			if(Tree<X>::t_depth[h_parent[a]] < Tree<X>::t_depth[b]) {
				l += Tree<X>::t_depth[b] - Tree<X>::t_depth[h_parent[a]];
			}
			ret = SG<X>::combine(ret, SG<X>::query(l, r));
			a = Tree<X>::t_par[h_parent[a]][0];
			if(a == -1) break;
		}
		return ret;
	}
public:
	HLD<X>(int nodes) : Tree<X>(nodes), SG<X>(nodes) { 
		/* Initialization and resize vectors */
		h_label.assign(Tree<X>::t_nodes, -1);
		h_heavychlid.assign(Tree<X>::t_nodes, -1);
		h_parent.resize(Tree<X>::t_nodes);
		iota(h_parent.begin(), h_parent.end(), 0);
	}

	/* Initialization */
	void init() {
		Tree<X>::init();

		/* Fill the heavy child, greatest parent, and labels */
		dfs_hc(Tree<X>::t_root);
		dfs_par(Tree<X>::t_root);
		dfs_labels(Tree<X>::t_root);

		/* Segment Tree Initialization */
		for(int i = 0; i < Tree<X>::t_nodes; i++) {
			SG<X>::s_tree[h_label[i] + Tree<X>::t_nodes] = Tree<X>::t_val[i];
		}
		for(int i = Tree<X>::t_nodes - 1; i > 0; i--) {
			SG<X>::s_tree[i] = SG<X>::combine(SG<X>::s_tree[i<<1], SG<X>::s_tree[i<<1|1]);
		}
	}

	/* Changes the value at node, to val */
	void update(int node, X val) {
		X diff  = val - Tree<X>::t_val[node];
		SG<X>::update(h_label[node], diff);
		Tree<X>::t_val[node] = val;
	}

	/* 
	 * return the (sum) of node values in,
	 * the simple path from a, to b
	*/
	X query(int a, int b) {
		int lc = Tree<X>::lca(a, b);
		X ret = SG<X>::sret_init;
		assert(lc != -1);
		ret += chain_query(a, lc);
		ret += chain_query(b, lc);
		return ret - Tree<X>::t_val[lc];
	}
};

int main() {
	int n, Q;
	cin >> n >> Q;
	HLD<long long> hld(n);
	for(int i = 0; i < n; i++) cin >> hld.t_val[i];
	for(int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		hld.add_edge(u-1, v-1);
	}
	hld.init();
	while(Q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int p, x;
			cin >> p >> x;
			hld.update(p - 1, x);
		}
		else {
			int p;
			cin >> p;
			cout << hld.query(0, p - 1) << endl;
		}
	}
}
/*
 * Sample Test Case:
10 10
1 8 6 8 6 2 9 2 3 2
10 5
6 2
10 7
5 2
3 9
8 3
1 4
6 4
8 7
2 10
2 6
1 3 4
2 9
1 5 3
1 7 8
2 4
2 8
1 1 4
1 2 7

 * Sample Output:
27
11
45
9
34
*/
