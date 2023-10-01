#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// TrieNode structure to represent a node in the trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    TrieNode* failureLink;  // Link to the longest proper suffix that is also a prefix
    vector<int> output;     // Patterns ending at this node
};

// Aho-Corasick class
class AhoCorasick {
public:
    AhoCorasick() {
        root = new TrieNode();
    }

    // Function to add a pattern to the trie
    void addPattern(const string& pattern, int patternIndex) {
        TrieNode* current = root;

        for (char ch : pattern) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        current->output.push_back(patternIndex);
    }

    // Function to build the failure links and output functions for each node
    void buildAhoCorasick() {
        queue<TrieNode*> nodeQueue;

        // Initialize failure links of all nodes at depth 1
        for (const auto& entry : root->children) {
            TrieNode* child = entry.second;
            child->failureLink = root;
            nodeQueue.push(child);
        }

        // Breadth-first traversal to build failure links and output functions
        while (!nodeQueue.empty()) {
            TrieNode* current = nodeQueue.front();
            nodeQueue.pop();

            for (const auto& entry : current->children) {
                char ch = entry.first;
                TrieNode* child = entry.second;
                nodeQueue.push(child);

                TrieNode* failureLink = current->failureLink;
                while (failureLink != root && failureLink->children.find(ch) == failureLink->children.end()) {
                    failureLink = failureLink->failureLink;
                }

                if (failureLink->children.find(ch) != failureLink->children.end()) {
                    child->failureLink = failureLink->children[ch];
                } else {
                    child->failureLink = root;
                }

                // Merge output functions
                child->output.insert(child->output.end(), child->failureLink->output.begin(), child->failureLink->output.end());
            }
        }
    }

    // Function to search for patterns in the text
    void search(const string& text) {
        TrieNode* current = root;

        for (int i = 0; i < text.size(); ++i) {
            char ch = text[i];

            while (current != root && current->children.find(ch) == current->children.end()) {
                current = current->failureLink;
            }

            if (current->children.find(ch) != current->children.end()) {
                current = current->children[ch];

                // Output matches
                for (int patternIndex : current->output) {
                    cout << "Pattern found at position " << i - patterns[patternIndex].size() + 1 << ": " << patterns[patternIndex] << endl;
                }
            }
        }
    }

private:
    TrieNode* root;
    vector<string> patterns;
};

int main() {
    AhoCorasick aho;

    // Add patterns to search for
    aho.addPattern("he", 0);
    aho.addPattern("she", 1);
    aho.addPattern("his", 2);
    aho.addPattern("hers", 3);

    // Build the Aho-Corasick trie
    aho.buildAhoCorasick();

    // Text to search in
    string text = "hershehishe";

    // Search for patterns in the text
    aho.search(text);

    return 0;
}
