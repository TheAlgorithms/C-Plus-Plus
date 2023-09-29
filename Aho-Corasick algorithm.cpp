#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Define the maximum number of characters in the alphabet
const int ALPHABET_SIZE = 26;

// Trie node structure
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    TrieNode* fail;
    vector<int> output;

    TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
        fail = nullptr;
    }
};

// Aho-Corasick Trie class
class AhoCorasick {
public:
    AhoCorasick() {
        root = new TrieNode();
    }

    // Function to add a keyword to the Trie
    void addKeyword(const string& keyword, int keywordIndex) {
        TrieNode* current = root;

        for (char c : keyword) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new TrieNode();
            }
            current = current->children[index];
        }

        current->output.push_back(keywordIndex);
    }

    // Function to build the failure links in the Trie using BFS
    void buildFailureLinks() {
        queue<TrieNode*> q;
        root->fail = root;

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root->children[i]) {
                root->children[i]->fail = root;
                q.push(root->children[i]);
            }
        }

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (current->children[i]) {
                    TrieNode* child = current->children[i];
                    TrieNode* failure = current->fail;

                    while (failure != root && !failure->children[i]) {
                        failure = failure->fail;
                    }

                    if (failure->children[i]) {
                        failure = failure->children[i];
                    }

                    child->fail = failure;
                    child->output.insert(child->output.end(), failure->output.begin(), failure->output.end());

                    q.push(child);
                }
            }
        }
    }

    // Function to search for keywords in the text and return their positions
    vector<vector<int>> search(const string& text) {
        TrieNode* current = root;
        vector<vector<int>> positions(text.length());

        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
            int index = c - 'a';

            while (current != root && !current->children[index]) {
                current = current->fail;
            }

            if (current->children[index]) {
                current = current->children[index];
            }

            for (int keywordIndex : current->output) {
                positions[i].push_back(keywordIndex);
            }
        }

        return positions;
    }

private:
    TrieNode* root;
};

int main() {
    AhoCorasick ac;

    // Input keywords
    int numKeywords;
    cout << "Enter the number of keywords: ";
    cin >> numKeywords;

    vector<string> keywords; // Store keywords in a vector

    cout << "Enter the keywords, one per line:" << endl;
    cin.ignore(); // Consume newline character
    for (int i = 0; i < numKeywords; i++) {
        string keyword;
        getline(cin, keyword);
        ac.addKeyword(keyword, i);
        keywords.push_back(keyword); // Store keywords in the vector
    }

    // Build failure links in the Trie
    ac.buildFailureLinks();

    // Input text
    string text;
    cout << "Enter the text to search for keywords in:" << endl;
    cin.ignore(); // Consume newline character
    getline(cin, text);

    // Search for keywords in the text
    vector<vector<int>> positions = ac.search(text);

    // Print the positions of each keyword in the text
    for (int i = 0; i < keywords.size(); i++) {
        cout << "Keyword \"" << keywords[i] << "\" found at positions: ";
        for (int j = 0; j < positions.size(); j++) {
            if (!positions[j].empty() && positions[j][0] == i) {
                cout << j << " ";
                positions[j].erase(positions[j].begin());
            }
        }
        cout << endl;
    }

    return 0;
}
