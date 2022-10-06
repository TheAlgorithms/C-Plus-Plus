class Node{
    Node *links[2];
public:
    bool containsKey(int bit) {
        return links[bit];
    }
    Node *get(int bit) {
        return links[bit];
    }
    void put(int bit,Node *node) {
        links[bit]=node;
    }
};

class Trie{
    Node *root;
public:
    Trie(){
        root=new Node();
    }
    void insert(int x){
        Node *node=root;
        for(int i=31;i>=0;i--){
            int bit=(x>>i)&1;
            if(!node->containsKey(bit)){
                node->put(bit,new Node());
            }
            node=node->get(bit);
        }
    }
    int getMax(int x){
        Node *node=root;
        int maxNum=0;
        for(int i=31;i>=0;i--){
            int bit=(x>>i)&1;
            if(node->containsKey(1-bit)){
                maxNum|=(1<<i);
                node=node->get(1-bit);
            }else{
                node=node->get(bit);
            }
        }
        return maxNum;
    }
    
};
