/*
 * C++ Program to Implement Hash Tables Chaining with Binary Trees
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;
 
/*
 * Node Class Declaration
 */
template <class T>
class BSTNode
{
    private:
        T value;
        BSTNode *left, *right;
    public:
        BSTNode(T value)
        {
            this->value = value;
            left = NULL;
            right = NULL;
        }
        /*
         * Adding element to a node
         */
        void add(T& value)
        {
            if (value < this->value)
            {
                if (left)
                    left->add(value);
                else
                    left = new BSTNode(value);
            }
            else if (this->value < value)
            {
                if (right)
                    right->add(value);
                else
                    right = new BSTNode(value);
            }
        }
        /*
         * Check if node contains element
         */
        bool contains(T& value)
        {
            if (value < this->value)
    	    {
                if (left)
            	    return left->contains(value);
        	else
           	    return false;
    	    }
    	    else if (this->value < value)
    	    {
                if (right)
            	    return right->contains(value);
        	else
            	    return false;
    	    }
    	    else
    	    {
                return true;
    	    }
        }
        friend class BSTHashtable;
};
 
/*
 * Table Class Declaration
 */
class BSTHashtable
{
    private:
        int size;
        vector<BSTNode<string>*>* bucket;
        int hash(string& s)
        {
            unsigned int hashVal = 0;
            for (unsigned int i = 0; i < s.length(); i++)
                hashVal ^= (hashVal << 5) + (hashVal >> 2) + s[i];
            return hashVal % size;
        }
    public:
        BSTHashtable(int vectorSize)
        {
            size = vectorSize;
            bucket = new vector<BSTNode<string>*>(size);
        }
        /*
         * Adding string in the table
         */
        void add(string& s)
        {
            int index = hash(s);
            if (bucket->at(index) == NULL)
                bucket->at(index) = new BSTNode<string>(s);
            else
                bucket->at(index)->add(s);
        }
        /*
         * Check if table contains string
         */
        bool contains(string& s)
        {
            int index = hash(s);
            if (bucket->at(index) == NULL)
                return false;
	    cout<<"String \""<<s<<"\" found at index: "<<index<<endl;
            return bucket->at(index)->contains(s);
        }
        /*
         * Display Table
         */
        void display()
        {
            for (unsigned int i = 0; i < bucket->size(); i++)
            {
                cout <<"[" << i << "] ";
	        if (bucket->at(i) != NULL)
                {
                    BSTNode<string> *node = bucket->at(i);
                    display_bst(node);
                }
                cout << endl;
            }
        }
        /*
         * Display BST
         */
        void display_bst(BSTNode<string> *node)
        {
	    if (node!=NULL)
            {
            	display_bst(node->left);
            	cout << node->value << " ";
            	display_bst(node->right);
            }
        }
};
 
/*
 * Main Contains Menu
 */
int main()
{
    BSTHashtable table(10);
    string str;
    int choice;
    while (1)
    {
        cout<<"\n----------------------"<<endl;
	cout<<"Operations on BST Hash Table"<<endl;
	cout<<"\n----------------------"<<endl;
	cout<<"1.Insert element into the table"<<endl;
	cout<<"2.Find element in the table"<<endl;
	cout<<"3.Display Table Chained with Binary Tree"<<endl;
	cout<<"4.Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter String to be inserted: ";
            cin>>str;
            table.add(str);
            break;
        case 2:
            cout<<"Enter String to search: ";
            cin>>str;
            if (table.contains(str) == 0)
            {
	        cout<<"String \""<<str<<"\" not found in the table"<<endl;
		continue;
	    }
            break;
        case 3:
            cout<<"Displaying Table Chained with Binary Tree: "<<endl;
            table.display();
            break;
        case 4:
            exit(1);
        default:
            cout<<"\nEnter correct option\n";
        }
    }
    return 0;
}