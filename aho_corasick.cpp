#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;

struct trie{

    struct trie* next[26];
    struct trie* fail;
    struct trie* outlink;
    bool end;

    trie(){
        fail = NULL;
        outlink = NULL;
        end = false;
        for(int i=0; i<26; i++){
            next[i] = NULL;
        }
    }
};

trie* root = new trie();

void buildTrie(string s){
    int n = s.length();
    trie* p = root;
    for(int i=0; i<n; i++){
        int idx = s[i]-'a';
        if(p->next[idx] == NULL){
            p->next[idx] = new trie();
        }
        p = p->next[idx];
    }
    p->end = 1;
}

void buildFailure(){
    queue<trie*> q;
    q.push(root);

    while(!q.empty()){
        trie* cur = q.front();
        q.pop();

        for(int i=0; i<26; i++){
            if(cur->next[i] != NULL){
                if(cur == root){
                    cur->next[i]->fail = root;
                } else{
                    trie* p = cur->fail;

                    while(p != NULL && p->next[i] == NULL){
                        p = p->fail;
                    }

                    if(p == NULL){
                        cur->next[i]->fail = root;
                    } else{
                        cur->next[i]->fail = p->next[i];
                    }
                }
                q.push(cur->next[i]);
            }
        }
    }
}

void buildOutlinks(){
    queue<trie*> q;
    q.push(root);

    while(!q.empty()){
        trie* cur = q.front();
        q.pop();

        for(int i=0; i<26; i++){
            if(cur->next[i] != NULL){
                if(cur != root){
                    if(root->next[i] != NULL && root->next[i]->end == 1){
                        cur->next[i]->outlink = root->next[i];
                    } else{
                        cur->next[i]->outlink = NULL;
                    }
                } else {
                    cur->next[i]->outlink = NULL;
                }
                q.push(cur->next[i]);
            }
        }
    }
}

int query(string b){
    trie* p = root;
    int cnt = 0;
    int n = b.length();

    for(int i=0; i<n; i++){
        int idx = b[i]-'a';

        while(p->next[idx] == NULL && p != root){
            p = p->fail;
        }

        if(p->next[idx] == NULL){
            continue;
        }

        p = p->next[idx];
        if(p->end == true)
            cnt++;
        if(p->outlink != NULL){
            cnt++;
        }
    }

    return cnt;
}

int main(){
    int n;
    cin >> n;
    
    for(int i=0; i<n; i++){
        string l;
        cin>>l;
        buildTrie(l);
    }
    
    string s;
    cin >> s;

    buildFailure();
    buildOutlinks();

    int ans = query(s);
    cout << ans << endl;
    return 0;
}
