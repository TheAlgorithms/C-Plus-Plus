#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

// Huffman tree node
struct Node {
    char data;
    int freq;

    // Child nodes
    Node* left;
    Node* right;

    Node(char data_, int freq_) {
        data = data_;
        freq = freq_;

        left = nullptr;
        right = nullptr;
    }
};

// Compare object for constructing a min priority queue
struct compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Wrapper class for Huffman tree
class HuffmanTree {
 private:
    unordered_map<char, int> freq;
    unordered_map<char, string> code;
    priority_queue<Node*, vector<Node*>, compare> set;
    Node* root = nullptr;

    // Generates and stores the encoded string of each letter into a map
    void storeCode(Node* node, string str) {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
            code[node->data] = str;

        storeCode(node->left, str + "0");
        storeCode(node->right, str + "1");
    }

 public:
    // Reads the characters of input and constructs a Huffman tree
    // based on the character frequencies of the input string
    HuffmanTree(const string& input) {
        // Count frequency of each letter and store it in map
        for (unsigned int i = 0; i < input.size(); i++)
            freq[input.at(i)]++;

        // Traverse the map, create a node of the letter and its
        // frequency, then add it to the priority queue
        for (auto iter : freq)
            set.push(new Node(iter.first, iter.second));

        while (set.size() != 1) {
            // Get
            Node* left = set.top();
            set.pop();
            Node* right = set.top();
            set.pop();

            int sum = left->freq + right->freq;
            Node* top = new Node('\0', sum);
            top->left = left;
            top->right = right;

            set.push(top);
        }

        root = set.top();

        // If input is just one character, assign '0' as its code
        if (input.size() == 1)
            storeCode(root, "0");
        else
            storeCode(root, "");
    }

    // Input is a character with ascii value between 0-127
    // Returns the Huffman code for character if character is in
    // the tree and an empty string otherwise.
    string get_character_code(char character) const {
        // If character exists in code map, return its code
        // Otherwise, return empty string
        auto iter = code.find(character);

        if (iter != code.end())
            return iter->second;

        return "";
    }

    // Returns the Huffman encoding for the contents of input
    // If input contains letters not present in the huffman_tree,
    // return an empty string
    string encode(const string& input) const {
        string encode = "";

        if (input.size() == 0)
            return "";

        // For each character in input string, if it's not in the code map,
        // return empty string Otherwise, add code to end of input string
        for (unsigned int i = 0; i < input.size(); i++) {
            auto iter = code.find(input.at(i));

            if (iter == code.end())
                return "";
            else
                encode.append(iter->second);
        }
        return encode;
    }

    // string_to_decode is a string containing Huffman-encoded text
    // Returns the plaintext represented by the string if the
    // string is a valid Huffman encoding and an empty string otherwise
    string decode(const string& string_to_decode) const {
        string decode = "";
        Node* current = root;

        if (string_to_decode.size() == 0)
            return "";

        // For each character in the string, if its '0' go left
        // if its '1' go right until you've reached a leaf node
        for (unsigned int i = 0; i < string_to_decode.size(); i++) {
            if (string_to_decode.at(i) == '0') {
                if (current->left != nullptr)
                    current = current->left;
                else
                    return "";
            }
            else if (string_to_decode.at(i) == '1') {
                if (current->right != nullptr)
                    current = current->right;
                else
                    return "";
            }
            else
                return "";

            // Reached leaf node, contains letter
            if (current->left == nullptr && current->right == nullptr)
            {
                decode.push_back(current->data);
                current = root;
            }
        }
        return decode;
    }
};

// Driver function for testing
int main() {
    string s = "The quick brown fox jumps over the lazy dog";

    HuffmanTree tree(s);

    string ans = tree.get_character_code('i');

    cout << "get_character_code: " << ans << endl;

    ans = tree.encode(s);

    cout << "encode: " << ans << endl;

    ans = tree.decode("10001");

    cout << "decode: " << ans << endl;

    return 0;
}