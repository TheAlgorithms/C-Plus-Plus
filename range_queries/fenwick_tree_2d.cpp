#include <iostream>
#include <cassert>
#include <vector>


template <class T>
struct fenwick {
    // siz - size of the fenwick tree
    // arr - fenwick tree array
    int siz;
    std::vector<T> arr;

    // Constructor 
    // n - size of the array on which fenwick tree is used
    // creates a new array with all entries as 0
    // indicies are 1-indexed
    explicit fenwick(int n) {
	siz = n;
	arr.resize(n + 1);
    }

    // Calculates a prefix sum till index idx
    T sum(int idx) {
	T an = 0;
	while(idx > 0) {
	    an += arr[idx];
	    // subtract first active bit from idx
	    idx -= idx & -idx;
	}
	return an;
    }

    // update the values at idx by delta
    // update all the indices which include idx in their sum
    void update(int idx, T delta) {
	while (idx < siz + 1) {
	    arr[idx] += delta;
	    // add the first active bit to idx
	    idx += idx & -idx;
	}
    }

    // find sum in range l to r
    T query(int l, int r) {
	// sum l--r == sum 0--r - sum 0--(l-1)
	return sum(r) - sum(l - 1);
    }
};

// implements 2D fenwick using a array of 1-D fenwicks
template<class T>
struct fenwick2D{
    
    // siz - size of the fenwick tree
    // arr - fenwick tree array
    int siz;
    std::vector<fenwick<T>> arr;

    // Constructor 
    // n - size of the array on which fenwick tree is used
    // creates a new array of fenwick trees of size n with all entries 0
    // indicies are 1-indexed
    explicit fenwick2D(int n) {
	siz = n;
	arr.resize(n + 1, fenwick<T>(n));
    }

    // if position x, y needs to be updates 
    // then go to all fenwick tree which have position x
    // and then for each of those fenwick trees make an update at
    // position y
    void update(int x, int y, T delta) {
	while(x < siz + 1) {
	    // update in 1-D fenwick
	    arr[x].update(y, delta);
	    // add the last bit of x to x itself
	    x += x & -x;
	}
    }

    // sum of region {1 to x} and {1 to y}
    T sum(int x, int y) {
	T an = 0;
	while(x > 0) {
	    // for each fenwick tree in range calucate sum till y
	    an += arr[x].sum(y);
	    // remove the last bit of x from x
	    x -= x & -x;
	}
	return an;
    }

    // sum of region {x1 to x} and {y1 to y}
    // sum in region x1 to x and y1 to y can written as
    //    - sum (x, y) - sum(x1 - 1, y) - sum(x, y - 1) + sum(x1 - 1, y1 - 1)
    // last part as is add rectangle {x1, y1} is subtracted twice
    T query(int x1, int y1, int x, int y) {
	return sum(x, y) - sum(x1 - 1, y) - sum(x, y1 - 1) + sum(x1 - 1, y1 - 1);
    } 

};

int main() {

    int n = 5;

    fenwick2D<int> fenwick_tree_2D(n);

    fenwick_tree_2D.update(1, 1, 2);
    fenwick_tree_2D.update(1, 2, 3);
    fenwick_tree_2D.update(2, 1, 3);
    fenwick_tree_2D.update(1, 3, 4);
    fenwick_tree_2D.update(2, 2, 4);
    fenwick_tree_2D.update(3, 1, 4);
    fenwick_tree_2D.update(1, 4, 5);
    fenwick_tree_2D.update(2, 3, 5);
    fenwick_tree_2D.update(3, 2, 5);
    fenwick_tree_2D.update(3, 3, 6);

    assert(fenwick_tree_2D.query(1, 1, 2, 2) == 12);
    assert(fenwick_tree_2D.query(1, 2, 3, 3) == 27);
    fenwick_tree_2D.update(1, 1, -3);
    assert(fenwick_tree_2D.query(1, 1, 2, 2) == 9);
    assert(fenwick_tree_2D.query(1, 2, 3, 3) == 27);

    std::cout << "All Test Passed\n";

    return 0;
}
