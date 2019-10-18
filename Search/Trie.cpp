#include <bits/stdc++.h>
using namespace std;

constexpr int R = 256;

struct Node
{
    Node*       next_[R] = {};
    std::string val_;
};

class Trie
{
    public:

    void Put(const string& key, const string& val)
    {
        root_ = Put(root_, key, val, 0);
    }

    string Get(const string& key)
    {
        Node* x = Get(root_, key, 0);

        if (!x)
            return "";

        return x->val_;
    }

    private:

    Node* Put(Node* x, const string& key, const string& val, int d)
    {
        if (!x)
            x = new Node();

        if (d == key.size())
        {
            x->val_ = val;
            return x;
        }

        char c      = key.at(d);
        x->next_[c] = Put(x->next_[c], key, val, d + 1);

        return x;
    }

    Node* Get(Node* x, const string& key, int d)
    {
        if (!x)
            return nullptr;

        if (d == key.size())
            return x;

        char c = key.at(d);

        return Get(x->next_[c], key, d + 1);
    }

    Node* root_ {};
};

int main()
{
    Trie t;
    t.Put("Kitty", "feline animal");
    t.Put("Snake", "eaten by Kitty");

    cout << t.Get("Snake") << endl;
    cout << t.Get("cow") << endl;

    t.Put("Snake", "a reptile");

    cout << t.Get("Ssnake") << endl;

    return 0;
}