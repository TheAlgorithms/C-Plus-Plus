#include <string>
#include <unordered_map>

using namespace std;

// hash map trie

class Trie {
 private:
    struct TrieNode {
        unordered_map<char, TrieNode *> children;
        bool isEnd;

        TrieNode() { isEnd = false; }
    };

    TrieNode *root = new TrieNode;

    bool isEmpty(TrieNode *cur) {
        if (cur->children.size() > 0)
            return false;
        return true;
    }

    void erase(string &word, int index, TrieNode *cur) {
        int length = word.length();

        if (index == length) {
            cur->isEnd = false;
            return;
        }

        int key = word[index];

        erase(word, index + 1, cur->children[key]);

        if (isEmpty(cur->children[key])) {
            cur->children[key] = NULL;
            delete cur->children[key];
        }
    }

 public:
    void insert(string word) {
        TrieNode *node = root;

        for (char c : word) {
            if (!node->children[c]) {
                node->children[c] = new TrieNode;
            }

            node = node->children[c];
        }

        node->isEnd = true;
    }

    bool search(string word) {
        TrieNode *node = root;

        for (char c : word) {
            if (!node->children[c]) {
                return false;
            }

            node = node->children[c];
        }

        return node && node->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode *node = root;

        for (char c : prefix) {
            if (!node->children[c]) {
                return false;
            }

            node = node->children[c];
        }

        return node;
    }

    void erase(string word) { erase(word, 0, root); }
};