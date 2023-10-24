#include <vector>	    //Header Files
#include <queue>
#include "Pque.cpp"
#include <cstring>
#include <string>

using namespace std;

//Defining Huffman Class
class Huffman
{
    //Defining Leaf Node of a Huffman Tree
    struct Leaf
    {
	   char data;
	   size_t freq;
	   Leaf* left;	    //Pointer to Left Child
	   Leaf* right;    //Pointer to right Child
	   Leaf(char data, size_t freq) //Default Constructor
		  : data(data), freq(freq), left(NULL), right(NULL)
	   {}
	   ~Leaf() //Destructor
	   {
		  delete left;
		  delete right;
	   }
    };
    //Function that tells the predefined priority Queue the basis 
    //upon which the queue will be prioritized
    struct compare
    {
	   bool operator()(Leaf* l, Leaf* r)
	   {
		  return (l->freq > r->freq);
	   }
    };

    Leaf* top;	 //Pointer to the Top Node or Root Node

    //This Function is kept private as it speficly designed to calculate all the Huffman Codes
    // and should be called be only once
    //Printing Recursive Function
    void print_Code(Leaf* root, string str, string* ar, char* cr, int& n)
    {
	   if (root == NULL)   //In case the Queue is Empty
		  return;

	   if (root->data == '*')  //In case the root is not a leaf	  
		  //Leaf nodes contains specific characters Internal Nodes 
			 //Contains the sum of the Leafs or Childern Nodes
	   {
		  //Adding 0 to the string/Hufman Code if we move to the left child/Node
		  print_Code(root->left, str + "0", ar, cr, n);
		  //Adding 1 to the string/Hufman Code if we move to the right child/Node
		  print_Code(root->right, str + "1", ar, cr, n);
	   }

	   if (root->data != '*')  //In case the root is a Leaf
	   {
		  cr[n] = root->data;	 //Saving characters in character Array
		  ar[n++] = str;	  //Saving Huffman Codes in a string

		  //Adding 0 to the string/Hufman Code if we move to the left child/Node
		  print_Code(root->left, str + "0", ar, cr, n);
		  //Adding 1 to the string/Hufman Code if we move to the right child/Node
		  print_Code(root->right, str + "1", ar, cr, n);
	   }
    }

public:
    //Default Constructor 
    Huffman()
    {
	   top = NULL;
    }
    //Destructor 
    ~Huffman()
    {
	   delete top;
    }
    //Huffman Tree and Code Creating Function
    void Huffman_tree(Pque p, string* str, char* cr)
    {
	   Leaf* left;
	   Leaf* right;
	   priority_queue<Leaf*, vector<Leaf*>, compare> Huffman_Tree; //Creating Priority Queue
	   //with Leaf Struct as it elements, Vector as its container, 
	   //The Piority is based on the Comapre function

	   //Initalizing The Predefined Priority Queue
	   while (!p.isEmpty())	  //Empting the User Defined Priority Queue into the Predined one
	   {
		  char c;	    //Temporary Variables
		  int f;	    //Temporary Variables
		  p.pop(c, f);		  //Poping Nodes
		  Huffman_Tree.push(new Leaf(c, f));	  //Pushing Values Into the Huffman Tree
	   }

	   while (Huffman_Tree.size() != 1)    //Making the Huffman Tree
	   {
		  left = Huffman_Tree.top();	    //Assigning Values
		  Huffman_Tree.pop();	 //poping Leafs from the queue

		  right = Huffman_Tree.top();	    //Assigning Values
		  Huffman_Tree.pop();	 //poping Leafs from the queue

		  //Creating Internal Node with * as identity and sum of its child leafs
		  top = new Leaf('*', left->freq + right->freq);
		  top->left = left;	  //Linking the Parent Node to Child Node
		  top->right = right; //Linking the Parent Node to Child Node
		  Huffman_Tree.push(top); //Pushing the Internal Node Back into the Queue
	   }
	   int n = 0;	//Temporary variable to traverse the arrays in the Priting Function

	   print_Code(Huffman_Tree.top(), "", str, cr, n); //Printing Function
    }
};
