#include <iostream>

template <typename DATA_TYPE>
class node{
public:
    DATA_TYPE value;
    uint8_t height;
    node *left;
    node *right;
};

template <typename DATA_TYPE>
class avl_tree{
private:
    node<DATA_TYPE> *root;
    uint8_t height(node<DATA_TYPE> *n);
    int8_t balance_factor(node<DATA_TYPE> *n);
    void fix_height(node<DATA_TYPE> *n);
    node<DATA_TYPE> *rotate_right(node<DATA_TYPE> *n);
    node<DATA_TYPE> *rotate_left(node<DATA_TYPE> *n);
    node<DATA_TYPE> *balance(node<DATA_TYPE> *n);
    node<DATA_TYPE> *insert_in_tree(DATA_TYPE value, node<DATA_TYPE> *n);
    node<DATA_TYPE> *find_min(node<DATA_TYPE> *n);
    node<DATA_TYPE> *remove_node(DATA_TYPE value, node<DATA_TYPE> *n);
    node<DATA_TYPE> *remove_min(node<DATA_TYPE> *n);
    void print_avl_tree(const std::string &prefix, node<DATA_TYPE> *n, bool is_left);
    void clear_tree(node<DATA_TYPE> *n);
public:
    avl_tree();
    void insert(DATA_TYPE value);
    void remove(DATA_TYPE value);
    node<DATA_TYPE> get_root();
    void print();
    void clear();

    ~avl_tree();
};

template <typename DATA_TYPE>
uint8_t avl_tree<DATA_TYPE>::height(node<DATA_TYPE> *n){
    return n ? n->height : 0;
}
template <typename DATA_TYPE>
int8_t avl_tree<DATA_TYPE>::balance_factor(node<DATA_TYPE> *n){
    return height(n->right)-height(n->left);
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::fix_height(node<DATA_TYPE> *n){
    n->height = std::max(height(n->left), height(n->right))+1;
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::rotate_right(node<DATA_TYPE> *n){
    node<DATA_TYPE> *new_root = n->left;
    n->left = new_root->right;
    new_root->right = n;
    fix_height(n);
    fix_height(new_root);
    return new_root;
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::rotate_left(node<DATA_TYPE> *n){
    node<DATA_TYPE> *new_root = n->right;
    n->right = new_root->left;
    new_root->left = n;
    fix_height(n);
    fix_height(new_root);
    return new_root;
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::balance(node<DATA_TYPE> *n){
    fix_height(n);
    int8_t b_factor = balance_factor(n);
    if (b_factor == 2){
        // right-left rotation
        if (balance_factor(n->right) < 0){
            n->right = rotate_right(n->right);
        }
        // just left rotation
        return rotate_left(n);
    }
    if (balance_factor(n) == -2){
        // left-right rotation
        if (balance_factor(n->left) > 0){
            n->left = rotate_left(n->left);
        }
        // just right rotation
        return rotate_right(n);
    }
    return n;
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::insert_in_tree(DATA_TYPE value, node<DATA_TYPE> *n){
    if (!n){
        n = new node<DATA_TYPE>;
        n->value = value;
        n->height = 1;
        n->left = n->right = nullptr;
        return n;
    }
    if (value < n->value){
        n->left = insert_in_tree(value, n->left);
    } else {
        n->right = insert_in_tree(value, n->right);
    }
    return balance(n);
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::find_min(node<DATA_TYPE> *n){
    return n->left ? find_min(n->left) : n;
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::remove_min(node<DATA_TYPE> *n){
    if (!n->left){
        return n->right;
    }
    n->left = remove_min(n->left);
    return balance(n);
}
template <typename DATA_TYPE>
node<DATA_TYPE> *avl_tree<DATA_TYPE>::remove_node(DATA_TYPE value, node<DATA_TYPE> *n){
    if (!n){
        return nullptr;
    }
    if (value < n->value) {
        n->left = remove_node(value, n->left);
    } else if (value > n->value){
        n->right = remove_node(value, n->right);
    } else {
        node<DATA_TYPE> *l = n->left;
        node<DATA_TYPE> *r = n->right;
        delete n;
        if (!r){
            return l;
        }
        node<DATA_TYPE> *temp_min = find_min(r);
        temp_min->right = remove_min(r);
        temp_min->left = l;
        return balance(temp_min);
    }
    return balance(n);
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::clear_tree(node<DATA_TYPE> *n){
    if (!n) return;
    if (n->left){
        clear_tree(n->left);
    }
    if (n->right){
        clear_tree(n->right);
    }
    delete n;
}
template <typename DATA_TYPE>
avl_tree<DATA_TYPE>::avl_tree(){
    root = nullptr;
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::insert(DATA_TYPE value){
    root = insert_in_tree(value, root);
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::remove(DATA_TYPE value){
    root = remove_node(value, root);
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::clear(){
    clear_tree(root);
    root = nullptr;
}
template<typename DATA_TYPE>
node<DATA_TYPE> avl_tree<DATA_TYPE>::get_root() {
    return root;
}
template <typename DATA_TYPE>
void avl_tree<DATA_TYPE>::print_avl_tree(const std::string& prefix, node<DATA_TYPE> *n, bool is_left){
    if(n){
        std::cout << prefix;
        std::cout << (is_left ? "├──" : "└──" );
        // print the value of the node
        std::cout << n->value << std::endl;

        // enter the next tree level - left and right branch
        print_avl_tree(prefix + (is_left ? "│   " : "    "), n->left, true);
        print_avl_tree(prefix + (is_left ? "│   " : "    "), n->right, false);
    }
}
template <typename DATA_TYPE>
avl_tree<DATA_TYPE>::~avl_tree(){
    clear();
}

template<typename DATA_TYPE>
void avl_tree<DATA_TYPE>::print() {
    print_avl_tree("", root, false);
}

int main() {
    avl_tree<int> number_tree;
    number_tree.insert(50);
    number_tree.print();
    number_tree.insert(60);
    number_tree.print();
    number_tree.insert(70);
    number_tree.print();
    number_tree.insert(80);
    number_tree.print();
    number_tree.insert(90);
    number_tree.print();
    number_tree.remove(60);
    number_tree.print();
    number_tree.clear();
    number_tree.print();
    number_tree.insert(60);
    number_tree.print();
    return 0;
}
