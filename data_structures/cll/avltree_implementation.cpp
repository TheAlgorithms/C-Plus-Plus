#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    string name; //name id
    long id; //number id
    int h; //height
    int bf;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(string name, long id) {
        left = nullptr;
        right = nullptr;
        this->name = name;
        this->id = id;
        h = 0;
        bf = 0;
    }
};

class AVLtree {

    Node* head = nullptr;
    int height;
    //Right rotate
    //Left rotate

public:
    Node* insertID(Node* node, long id, string name); //building the AVL ->
    //insert helper function
    Node* removeID(Node* root, long id);
    void searchID(Node* root, long id, bool& success);
    void searchName(Node* root, string name, vector <long>& ids);

    void printInorder(Node* node, vector <string>& strings); //traversing the AVL ->
    void printPreorder(Node* node, vector <string>& strings);
    void printPostorder(Node* node, vector <string>& strings);
    void printLevelCount(Node* node);
    Node* removeInorder(Node* node, long index);

    Node* returnRoot();
    void setRoot(Node* node);

    AVLtree();
    ~AVLtree();
};

AVLtree::AVLtree() {
    head = nullptr;
    height = 0;
}

AVLtree::~AVLtree() {
    delete head;
}

Node* AVLtree::returnRoot() {
    return head;
}
void AVLtree::setRoot(Node* node) {
    head = node;
}

int getHeight(Node* root) { //Citation: https://www.techiedelight.com/calculate-height-binary-tree-iterative-recursive/
    if (root == nullptr) {
        return 0;
    }
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

int balanceFactor(Node* root) { //Inspired by the powerpoint module 4
    if (root == nullptr)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

//rotations!

Node* rotateLeft(Node *node) { //This is from my stepik answer
    //your code here
    Node* boi = new Node;
    Node* root = new Node;

    boi = node;
    root = boi->right;
    boi->right = root->left;
    root->left = boi;

    node->h = getHeight(node);
    boi->h = getHeight(node);
    root->h = getHeight(node);

    return root;
}

Node* rotateRight(Node *node) { //From my stepik answer
    //your code here
    Node* stinky_boi = new Node;
    Node* root = new Node;

    stinky_boi = node;
    root = stinky_boi->left;
    stinky_boi->left = root->right;
    root->right = stinky_boi;

    node->h = getHeight(node);
    stinky_boi->h = getHeight(stinky_boi);
    root->h = getHeight(root);

    return root;
}

bool isAVL(Node* root) { //From my stepik answer
    int left_height, right_height;

    if (root == nullptr) {
        return true;
    }

    right_height = getHeight(root->right);
    left_height = getHeight(root->left);

    if ((left_height - right_height <= 1) && (left_height - right_height >= -1)) {
        if (isAVL(root->left) && isAVL(root->right)) {
            return true;
        }
    }
    else {
        return false;
    }
}

Node* checkBalanceTree(Node* node) { //Inspired by my stepik answer

    int bF = balanceFactor(node);
    node->h = getHeight(node);
    int h_left = getHeight(node->left);
    int h_right = getHeight(node->right);

    if (bF > 1 && (getHeight(node->left->left) - getHeight(node->left->right) == -1)) { //leftright
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if (bF < -1 && (getHeight(node->right->left) - getHeight(node->right->right) == 1)) { //rightleft
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    else if (bF > 1 && getHeight(node->left->left) - getHeight(node->left->right) == 1) {
        return rotateRight(node);
    }
    else if (bF < -1 && getHeight(node->right->left) - getHeight(node->right->right) == -1) {
        return rotateLeft(node);
    }

    return node;
}

//insertion!

Node* AVLtree::insertID(Node* node, long id, string name) { //Inspired by the Module 4 powerpoint

    if (node == nullptr) {
        cout << "successful" << endl;
        return new Node(name, id);
    }
    else if (id == node->id) {
        cout << "unsuccessful" << endl;
    }
    else if (id < node->id) {
        node->left = insertID(node->left, id, name);
        if (!isAVL(node))
            node = checkBalanceTree(node);
    }
    else {
        node->right = insertID(node->right, id, name);
        if (!isAVL(node))
            node = checkBalanceTree(node);
    }

    return node;
}

//removeID function below

Node* AVLtree::removeID(Node* root, long id) {
    //update balance attribute too (balance it out)
    Node* stinky;

    if (root == nullptr) { //cant remove it if its already not there
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    if (root->id < id) {
        root->right = removeID(root->right, id);
        return root;
    }
    else if (root->id > id) {
        root->left = removeID(root->left, id);
        return root;
    }
    else { //item is in the root
        if (root->left == nullptr && root->right == nullptr) { //has no children
            cout << "successful" << endl;
            delete root;
            return nullptr;
        }
        else if (root->left != nullptr && root->right != nullptr) { //has 2 children
            if (root->right->left == nullptr) {
                root->right->left = root->left;

                stinky = root->right;
                //stinky->left = root->left;
                cout << "successful" << endl;
                delete root;
                return stinky;
            }
            else { //2 children
                Node* right_child = root->right;
                //keep going left til get furthest left node in the right tree
                while (right_child->left != nullptr) {
                    right_child = right_child->left;
                }
                root->id = right_child->id;
                root->name = right_child->name;
                //root->right->left = nullptr;
                root->right = removeID(root->right, root->id);
                //cout << "unsuccessful" << endl;
                return root;
            }
        }
        else if (root->left == nullptr) { //has 1 child and want to remove the right
            Node* rightc = root->right;
            delete root;
            cout << "successful" << endl;
            return rightc;
        }
        else if (root->right == nullptr) { //has 1 child and want to remove the left
            Node* leftc = root->left;
            delete root;
            cout << "successful" << endl;
            return leftc;
        }
    }
    return nullptr;
}

//search functions

void AVLtree::searchID(Node* root, long id, bool &success) {
    Node* search = root;
    //cout << "root is: " << root->id << endl;
    while (search != nullptr) {
        //cout << "now searching: " << search->id << endl;
        if (search->id == id) {
            //cout << "found id" << endl;
            cout << search->name << endl;
            success = true;
            break;
        }
        else if (search->id > id) {
            //cout << "moving left" << endl;
            search = search->left;
        }
        else {
            //cout << "moving right" << endl;
            search = search->right;
        }
    }
}

void AVLtree::searchName(Node* root, string name, vector <long>& ids) { //return anything that matches
    if (root != nullptr) {
        if (root->name == name) {
            ids.push_back(root->id);
        }
        searchName(root->left, name, ids);
        searchName(root->right, name, ids);
    }
}

// --------- printing/traversal functions ------------ //

void AVLtree::printInorder(Node* node, vector <string>& strings) { //Left ROOT Right
    if (node != nullptr) {
        printInorder(node->left, strings);
        strings.push_back(node->name);
        printInorder(node->right, strings);
    }
}

void AVLtree::printPreorder(Node* node, vector <string>& strings) {
    if (node != nullptr) {
        strings.push_back(node->name);
        printPreorder(node->left, strings);
        printPreorder(node->right, strings);
    }
}

void AVLtree::printPostorder(Node* node, vector <string>& strings) {
    if (node != nullptr) {
        printPostorder(node->left, strings);
        printPostorder(node->right, strings);
        strings.push_back(node->name);
    }
}

void AVLtree::printLevelCount(Node* node) { //just the root node's height
    cout <<  getHeight(node) << endl;
}

// -------------- remove inorder funcs ------------ //

void sortVecInorder(Node* node, vector<Node*> &nodes) {
    if (node != nullptr) { //man this was insane to figure out
        sortVecInorder(node->left, nodes);
        nodes.push_back(node);
        sortVecInorder(node->right, nodes);
    }
}

Node* AVLtree::removeInorder(Node* node, long index) {
    vector<Node*> nodes;
    sortVecInorder(node, nodes);

    if (index <= nodes.size()) {
        Node* temp = removeID(node, nodes[index]->id); //removeID prints successful
        return temp;
    }
    else {
        return nullptr;
    }
}

/*---  MAIN & PARSING BELOW ---*/

int main() {

    AVLtree sprout = AVLtree();

    int it;
    cin >> it; //appropriate number of times to call on functions
    cin >> ws;

    for (int i = 0; i < it; i++) { //this that parsing nonsense. calling on appropriate functions
        string line, function, name, id;
        getline(cin, line);
        istringstream in(line);
        in >> function;

        if (line.find(" ") != string::npos) {   //this is good; it parses the first word, function
            function = line.substr(0 , line.find(" "));
        }
        else {
            function = line;
        }

        // ----- specific commands below ------- //

        if (function == "insert") {
            in >> name >> id;
            name =  name.substr(1, name.size()-2);
            //if its not a letter than print unsuccessful, if its valid then (if the id is valid)
            bool valid = true;
            for (int i = 0; i < name.length(); i++) {
                char c = name[i];
                if (!isalpha(c)) {
                    cout << "unsuccessful";
                    valid = false;
                }
            }
            if (valid) {
                try {
                    long fresh_id = stol(id);
                    if (id.length() != 8) {
                        cout << "unsuccessful" << endl;
                    }
                    else {
                        sprout.setRoot(sprout.insertID(sprout.returnRoot(), fresh_id, name));
                    }
                }
                catch (exception e) {
                    cout << "unsuccesful"  << endl;
                }
            }
        }
        else if (function == "search") {
            in >> name;
            if (line.find("\"") != string::npos) { //if the next word contains quotation marks, then it's a string
                name =  name.substr(1, name.size()-2);
                vector <long> ids;
                sprout.searchName(sprout.returnRoot(), name, ids);
                if (ids.empty()) {
                    cout << "unsuccessful" << endl;
                }
                else {
                    for (int k = 0; k < ids.size(); k++) {

                        cout << to_string(ids[k]) << endl;
                    }
                }
            }
            else {
                bool success = false;
                sprout.searchID(sprout.returnRoot(), stol(name), success); //therefore you should call upon search ID cus its an integer
                if (!success) {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (function == "remove") {
            in >> id;
            sprout.setRoot(sprout.removeID(sprout.returnRoot(), stol(id)));
        }
        else if (function == "removeInorder") {
            in >> id;
            sprout.setRoot(sprout.removeInorder(sprout.returnRoot(), stol(id)));
        }
        else if (function == "printInorder") {
            vector <string> strings;
            sprout.printInorder(sprout.returnRoot(), strings);
            for (int j = 0; j < strings.size(); j++) {
                cout << strings[j];
                if (j != strings.size()-1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else if (function == "printPreorder") {
            vector <string> strings;
            sprout.printPreorder(sprout.returnRoot(), strings);
            for (int j = 0; j < strings.size(); j++) {
                cout << strings[j];
                if (j != strings.size()-1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else if (function == "printPostorder") {
            vector <string> strings;
            sprout.printPostorder(sprout.returnRoot(),strings);
            for (int j = 0; j < strings.size(); j++) {
                cout << strings[j];
                if (j != strings.size()-1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else if (function == "printLevelCount") {
            sprout.printLevelCount(sprout.returnRoot());
        }
    }
}