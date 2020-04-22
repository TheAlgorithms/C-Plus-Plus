/*
*this program is use to find any elemet in any row with variable array size
*aplication of pointer is use in it
*important point start from here to:
*the index value of array can be go to 1 to 100000
*check till array[1000]
*end here
*how to work example:
**Question:
***number of array 2
***quarry 3
***array 1 is {1 2 3 4 5}
***array 2 is {6 7}
****i) what is 2nd element in 1st array
****ii) what is 1st element in 2nd array
****iii) what is 5th element in 1st array
*****output:
*****Enter Number of array you want to Store : 2
*****Enter Number of Question or Quary you want to do Related to Array : 3
*****Enter number of element in 1 rows : 5
*****Enter the element of Array 1 2 3 4 5
*****Enter number of element in 2 rows : 2
*****Enter the element of Array 6 7
*****enter the number of row which element You want to find : 1
*****enter the position of element which You want to find : 2
*****The element is 2
*****enter the number of row which element You want to find : 2
*****enter the position of element which You want to find : 1
*****The element is 6
*****enter the number of row which element You want to find : 1
*****enter the position of element which You want to find : 5
*****The element is 5
*/
#include <iostream>

// this is main fuction
// ***
int main() {
    int64_t r, mr = 0, x, q, i, z;
    std::cout << "Enter Number of array you want to Store :";
    std::cin >> x;
    std::cout << "Enter Number of ";
    std::cout << "Question or Quary you ";
    std::cout << "want to do Related to Array :";
    std::cin >> q;
    // create a Array in run time because use can
    // change the size of each array which he/she is going to store
    // create a 2D array
    int** ar = new int* [x]();
    // this for loop is use for entering different variable size array
    // ***
    for (r = 0; r < x; r++) {
        std::cout << "Enter number of element in " << r + 1 << " rows :";
        std::cin >> mr;
        // creating a 1D array
        int* ac = new int[mr]();
        std::cout << "Enter the element of Array ";
        // this for loop is use for storing values in array
        // ***
        for (i = 0; i < mr; i++) {
            // entering the value of rows in array in Horizontal
            std::cin >> ac[i];
        }
        // Change the position of Array so that new arrays entery will be done
        ar[r] = ac;
    }
    // this for loop is use for display result of querry
    // ***
    for (z = 0; z < q; z++) {
        int64_t r1 = 0, q1 = 0;
        std::cout << "enter the number of row which element you want to find :";
        std::cin >> r1;
        r1 = r1 - 1;
        std::cout << "enter the position of element which you want to find :";
        std::cin >> q1;
        q1 = q1 - 1;
        // use this to find desire position of element in desire array
        std::cout <<"The element is "<< ar[r1][q1] <<std::endl;
    }
}
