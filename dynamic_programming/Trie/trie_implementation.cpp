#include <bits/stdc++.h>
using namespace std;
struct node {
    node* children[26] = {NULL};
    bool flag = false;
    bool isPresent(char c) {
        if (children[c - 'A'] != NULL)
            return true;
        return false;
    }
    node* getLink(char c) { return children[c - 'A']; }
    void add(char c, node* temp) { children[c - 'A'] = temp; }
};

class Trie {
 private:
    node* root;

 public:
    Trie() { root = new node(); }
    void insert(string str) {
        node* temp = root;
        for (int i = 0; i < str.size(); i++) {
            if (temp->isPresent(str[i])) {
                temp = temp->getLink(str[i]);
            } else {
                temp->add(str[i], new node());
                temp = temp->getLink(str[i]);
            }
        }
        temp->flag = true;
    }
    bool search(string str) {
        node* temp = root;
        for (int i = 0; i < str.size(); i++) {
            if (temp->isPresent(str[i]) == false)
                return false;
            else
                temp = temp->getLink(str[i]);
        }
        return temp->flag;
    }
    bool startwith(string str) {
        node* temp = root;
        for (int i = 0; i < str.size(); i++) {
            if (temp->isPresent(str[i]) == false)
                return false;
            else
                temp = temp->getLink(str[i]);
        }
        return true;
    }
};
int main() {
    Trie T;
    int ch;
    while (1) {
        cout << "1.Insert a string\n";
        cout << "2.Search a string\n";
        cout << "3.Search string with prefixes\n";
        cout << "4.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        string s;
        switch (ch) {
            case 1:
                cout << "Enter string you want to insert: ";
                cin >> s;
                T.insert(s);
                break;
            case 2:
                cout << "Enter string you want to search: ";
                cin >> s;
                if (T.search(s))
                    cout << s << " is present\n";
                else
                    cout << s << " is not present\n";
                break;
            case 3:
                cout << "Enter prefix: ";
                cin >> s;
                if (T.startwith(s))
                    cout << "strings present that starts with " << s << endl;
                else
                    cout << "strings not present that starts with " << s
                         << endl;
                break;
            case 4:
                exit(1);
            default:
                cout << "Again enter your choice\n";
        }
    }
}