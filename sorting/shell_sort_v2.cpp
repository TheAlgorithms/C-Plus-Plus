#include <vector>
#include <algorithm>
#include <iostream>

/**
 * This function implements the Shell Sorting Algorithm.
 * 
 * @note Knuth sequence was used.
 * 
 * @param v Vector to be sorted.
 */
void shell_sort(std::vector<int> &v) { 
    int gap;
    // calculate the first gap, based on Knuth sequence
    for(gap = 1; gap < (v.end() - v.begin()); gap = 3 * gap + 1); 
    while(gap > 0) { // change to while(gap)
        // descrease the gap
        gap = (gap - 1)/3;
        // pass by elements to swap then if necessary
        for(size_t i = 0; v.begin() + gap + i < v.end(); i++) {
            if(*(v.begin() + gap + i) < *(v.begin() + i)) {
                std::swap(*(v.begin() + gap + i), *(v.begin() + i));
                // in case some element was sawpped, it will try swap the elements before, maintaining the gap
                for(int j = i - gap; j >= 0; j -= gap) {   
                    if(*(v.begin() + gap + j) < *(v.begin() + j)) { std::swap(*(v.begin() + gap + j), *(v.begin() + j)); }         
                }
            }
        }
        
    }
}

/**
 * Simple print function.
 */
void print_vec(std::vector<int> v) {  
    for(int i = 0; i < v.size(); i++) std::cout << v[i] << " "; 
    std::cout << std::endl; 
} 

/**
 * Driver code.
 */ 
int main() {  
    std::vector<int> v = {23, -10, 20, -11, 12, -6, 7, 299, 9, -1, 37, 51, 0};      
    shell_sort(v);
    std::cout << "Sorted: ";
    print_vec(v); 
    
    return 0;  
}  