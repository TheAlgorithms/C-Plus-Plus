/*********************************************************************************
* @file
* @brief [Sparse Matrix]
* @details
* A sparse matrix is a special type of matrix that contains mostly zeros. 
* In a regular matrix, most of the elements have values, but in a sparse matrix, the majority of the elements are zero. 
* This means that only a few elements have non-zero values, making the matrix "sparse" with empty spaces.
* Imagine a grid-like structure where each cell holds a number. 
* In a regular matrix, most cells have numbers in them, but in a sparse matrix, many cells are empty (zeros). 
* These empty cells make the sparse matrix more efficient to store and work with because you don't need to remember or process as many values.
* Sparse matrices are common in various fields like scientific computing, graph theory, and data analysis when dealing with large datasets or structures where only a small fraction of elements have meaningful values. Using sparse matrices can save memory and computational resources, which is beneficial in many practical applications.
*
* ### Implementation

* We counts the number of zero valued elements in the Matrix
* Check if the count is more than the half of the size of matrix
* If 50% of the elements from the matrix and zero valued, we call it a sparse matrix.

* @author [Vishal Sharma] (https://github.com/codingspace1)
***************************************************************************************/
#include<iostream> ///for I/O operations
#include<vector>   /// for std::vector
#include<cassert> /// for assert


/***
 * @brief 
 * function to check if matrix is sparse or not
 * @param vect Matrix to be tested
 * @returns zero if matrix is not sparse
***/
bool is_sparse_matrix(std::vector<std::vector<int>> vect)
{
    int zero_counter = 0;
    for(int i =0; i<vect.size(); i++)
    {
        for(int j = 0; j<vect[i].size(); j++)
        {
            if (vect[i][j]==0)
            {
                zero_counter+=1;
            }
        }
    }

    return (zero_counter>(vect.size() * vect[0].size())* 0.5); //return 1 if zero values are more than non zero values

}

/*******************************************************************************
 * @brief 
 * function to display the Matrix elements
 * @param vect Matrix to be displayed
 * @returns void
*******************************************************************************/

void display(std::vector<std::vector<int>> vect)
{
    for(int i =0; i<vect.size(); i++)
    {
        for(int j = 0; j<vect[i].size(); j++)
        {
            std::cout<<vect[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

/*******************************************************************************
 * @brief Self-test implementation #1
 * @returns void
 *******************************************************************************/

void test1()
{
    std::vector<std::vector<int>> vect1 = {{1, 0, 0, 1}, {0, 1, 0, 2}, {1, 0, 1, 4}};
    int expected_ans = 0;
    int derived_ans = is_sparse_matrix(vect1);
    std::cout<<"Test #1: ";
    assert(derived_ans == expected_ans);
    std::cout<<"Passed! \n"; 

}

/*******************************************************************************
 * @brief Self-test implementation #2
 * @returns void
 *******************************************************************************/

void test2()
{
    std::vector<std::vector<int>> vect1 = {{1, 1, 1, 0}, {0, 1, 0, 2}, {1, 1, 1, 1}};
    int expected_ans = 0;
    int derived_ans = is_sparse_matrix(vect1);
    std::cout<<"Test #2: ";
    assert(derived_ans == expected_ans);
    std::cout<<"Passed! \n"; 

}
/*******************************************************************************
 * @brief Self-test implementation #3
 * @returns void
 *******************************************************************************/

void test3()
{
    std::vector<std::vector<int>> vect1 = {{0, 0, 0, 1}, {0, 0, 0, 2}, {0, 1, 0, 4}};
    int expected_ans = 1;
    int derived_ans = is_sparse_matrix(vect1);
    std::cout<<"Test #3: ";
    assert(derived_ans == expected_ans);
    std::cout<<"Passed! \n"; 

}

 /*******************************************************************************
     * @brief Main function
     * @returns 0 on exit
     *******************************************************************************/

int main()
{
    test1();  // run self-test implementation #1
    test2();  // run self-test implementation #2
    test3();  // run self-test implementation #3
    
    return 0;
}
