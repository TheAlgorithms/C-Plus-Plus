// find max xor pair in array using trie.
class Solution {

	typedef struct data{
		data* bit[2];
		int cnt=0;
	}trie;
	trie * head;

public:
    void insert(int x){
        // cout<<"Insert\n";
        trie* node = this->head;
        for(int i=30; i>=0; --i){
            int curbit = (x>>i)&1;
			if( node->bit[curbit] == NULL){
				node->bit[curbit] = new trie();
			}
			node = node->bit[curbit];
			node->cnt++;
		}
	}
    int maxxor(int x){
        trie* node = this->head;
		int ans = 0;
		for(int i=30; i>=0; --i){
			int curbit = (x>>i)&1;
			if(node->bit[curbit^1] != NULL and node->bit[curbit^1]->cnt > 0 ){
				ans += (1<<i);
				node = node->bit[curbit^1];
			}else{
				node = node->bit[curbit];
			}
		}
		return ans;
	}

    int findMaximumXOR(vector<int>& arr) {
        this->head = new trie();
		int n = arr.size();
		insert(arr[0]);
		int ans = 0;
		for(int i=1; i<n; ++i){
			int get = maxxor(arr[i]);
			ans = max(get, ans);
			insert(arr[i]);
		}
		return ans;
    }
};

// Resource: https://qr.ae/TWvjgq
