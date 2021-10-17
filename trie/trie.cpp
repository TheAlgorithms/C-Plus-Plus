#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Trie data structure
struct node
{
  map<char,node*> m;
  bool end=false;
  set<string> name;
};

class trie{
  public:
    node* root;
    trie()
    {
        root= new node;
        root->end=false;
    }
    ll insert(string s)
    {
        node* temp=root;

        for(int i=0;i<s.length();++i)
        {
            if((temp->m).find(s[i])==(temp->m).end())
            {
                node* temp1=new node;
                (temp->name).insert(s);
                (temp->m)[s[i]]=temp1;
                temp=temp1;
            }
            else
            {
                (temp->name).insert(s);
                temp=(temp->m)[s[i]];
            }
        }
        temp->end=true;
    }

    set<string> search(string s)
    {
        node* temp=root;
        for(int i=0;i<s.length();++i)
        {
            if((temp->m).find(s[i])==(temp->m).end())
            {
                set<string> t;
                return t;
            }
            temp=(temp->m)[s[i]];
        }
        return temp->name;
    }

    node* deleteNode(node* root,string s,int i)  //root is root of trie,i is 0 initially
    {
        (root->name).erase(s);
        // completed the given word
        if(i==s.length())
        {
            // word found if root->end is true
            root->end=false;

            // Word Found
            if((root->m).empty())
            {
                delete root;
                root=NULL;
            }
            return root;
        }

        // word not found
        if((root->m).find(s[i])==(root->m).end()) return root;

        // Removing the node's pointer if that was deleted earlier
        if(deleteNode((root->m)[s[i]],s,i+1)==NULL)
        {
            (root->m).erase(s[i]);
        }

        if((root->m).empty() && root->end==false)
        {
            delete root;
            root=NULL;
        }
        return root;
    }
};

int main()
{
    cout<<"Hello Everyone!"<<endl;
    
    trie tr;
    string s="Hello World!";
    
    // Inserting
    tr.insert(s);
    cout<<"Insertion successful!"<<endl;
    
    // searching
    set<string> ans = tr.search(s);
    cout<<"Search successful!"<<endl;
    
    // Deleting
    tr.deleteNode(tr.root,s,0);
    cout<<"Deletion successful!"<<endl;

    cout<<"Good Bye!!!"<<endl;
}
