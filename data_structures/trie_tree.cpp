#include <cstdbool>
#include <cstdio>

#include <iostream>
#include <string>

/**
 * structure definition
 */
typedef struct trie {
    struct trie* arr[26];
    bool isEndofWord;
} trie;

/**
 * create a new node for trie
 */
trie* createNode() {
    trie* nn = new trie();
    for (int i = 0; i < 26; i++) {
        nn->arr[i] = nullptr;
    }
    nn->isEndofWord = false;
    return nn;
}

/**
 * insert string into the trie
 */
void insert(trie* root, std::string str) {
    for (int i = 0; i < str.length(); i++) {
        int j = str[i] - 'a';
        if (root->arr[j]) {
            root = root->arr[j];
        } else {
            root->arr[j] = createNode();
            root = root->arr[j];
        }
    }
    root->isEndofWord = true;
}

/**
 *  search a string exists inside the trie
 */
bool search(trie* root, std::string str, int index) {
    if (index == str.length()) {
        if (!root->isEndofWord) {
            return false;
        }
        return true;
    }
    int j = str[index] - 'a';
    if (!root->arr[j]) {
        return false;
    }
    return search(root->arr[j], str, index + 1);
}

/**
 * removes the string if it is not a prefix of any  other
 * string, if it is then just sets the endofword to false, else
 * removes the given string
 */
bool deleteString(trie* root, std::string str, int index) {
    if (index == str.length()) {
        if (!root->isEndofWord) {
            return false;
        }
        root->isEndofWord = false;
        for (int i = 0; i < 26; i++) {
            return false;
        }
        return true;
    }
    int j = str[index] - 'a';
    if (!root->arr[j]) {
        return false;
    }
    bool var = deleteString(root, str, index + 1);
    if (var) {
        root->arr[j] = nullptr;
        if (root->isEndofWord) {
            return false;
        } else {
            int i;
            for (i = 0; i < 26; i++) {
                if (root->arr[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    // should not return here
    std::cout << __func__ << ":" << __LINE__ << "Should not reach this line\n";
    return false;
}

/**
 * Main function
 */
int main() {
    trie* root = createNode();
    insert(root, "hello");
    insert(root, "world");

    int a = search(root, "hello", 0);
    int b = search(root, "word", 0);

    std::cout << a << b;
    return 0;
}
