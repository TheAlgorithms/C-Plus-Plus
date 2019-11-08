// C++ program to implement gravity/bead sort 
#include <stdio.h>
#include <string.h>
using namespace std; 
  
#define BEAD(i, j) beads[i * max + j] 
  
// function to perform the above algorithm 
void beadSort(int *a, int len) 
{ 
    // Find the maximum element 
    int max = a[0]; 
    for (int i = 1; i < len; i++) 
        if (a[i] > max) 
           max = a[i]; 
  
    // allocating memory 
    unsigned char beads[max*len]; 
    memset(beads, 0, sizeof(beads)); 
  
    // mark the beads 
    for (int i = 0; i < len; i++) 
        for (int j = 0; j < a[i]; j++) 
            BEAD(i, j) = 1; 
  
    for (int j = 0; j < max; j++) 
    { 
        // count how many beads are on each post 
        int sum = 0; 
        for (int i=0; i < len; i++) 
        { 
            sum += BEAD(i, j); 
            BEAD(i, j) = 0; 
        } 
  
        // Move beads down 
        for (int i = len - sum; i < len; i++) 
            BEAD(i, j) = 1; 
    } 
  
    // Put sorted values in array using beads 
    for (int i = 0; i < len; i++) 
    { 
        int j; 
        for (j = 0; j < max && BEAD(i, j); j++); 
  
        a[i] = j; 
    } 
} 
  
// driver function to test the algorithm 
int main() 
{ 
    int a[] = {5, 3, 1, 7, 4, 1, 1, 20}; 
    int len = sizeof(a)/sizeof(a[0]); 
  
    beadSort(a, len); 
  
    for (int i = 0; i < len; i++) 
        printf("%d ", a[i]); 
  
    return 0; 
} 
