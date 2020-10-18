/*  Gram Schimdt Orthogonalisation  Created by akanksha gupta on 02/10/20.
    Copyright © 2020 akanksha gupta. All rights reserved.
    Used double as datatype for storing vectors (in maths) as inputs are integers.
    Change it to long double to increase digits of precision in case of decimal inputs.
    Have defined maximum dimension of vectors to be 10 and number of vectors taken is 20.
    Please do not give linearly dependent vectors
 */

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

/*
    dot_product() function. Storing maths vector in Array
    and calculating it here.
*/

double dot_product (double x[], double y[], int c) {
    double sum = 0;
    for (int i = 0; i < c; i++) {
        sum += x[i] * y[i];
    }
    return sum;
}

/*
    The dot product of two vectors is taken and the norm of the second vector
    is taken. Then, dot product value is divided by the norm and stored in factor.
    Then, multiply that factor with every element in a third vector, whose initial values are
    same as the 2nd vector. This vector will then be the projection of 2nd vector over 1st vector.
 */

void projection (double x[], double y[], double temp[], int c){
    double dot = dot_product(x, y, c);
    double anorm = dot_product(y, y, c);
    double factor = dot/anorm;
    for (int i = 0; i < c; i++) {
      temp[i]  = y[i] * factor;
    }
}

/*
   Function to print the orthogonalised vector
 */

void display(int r, int c, double B[][10]){
    for(int i = 0; i < r; i++){
        cout << "Vector " << i+1 << ": ";
        for(int j = 0; j < c; j++){
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
}

/*
   Function for the process of Gram Schimdt Process.
   First, we check whether appropriate dimensions are given or not.
   Then, we take a second 2-D array. This will store orthogonalised vectors
   of the input vectors.
   First vector is copied as it is. Then, from 2nd vector onwards,
   we take the projection with all the previous vector and add them.
   Then, twe subtract total projection vector from the input vector
 */

void gram_schmidt(int r, int c, double A[][10], double B[][10]){
    if(c < r)
    {
        cout << "Dimension of vector is less than number of vector, hence \n first "<< c <<" vectors are orthogonalised" << endl;
        r = c;
    }
    
    int k = 1;
    
    while (k <= r) {
        if (k == 1) {
            for(int j = 0; j < c; j++)
                B[0][j] = A[0][j];
        }
        
        else{
        
        double all_projection[c];
        for (int i = 0; i < c; i++) {
            all_projection[i] = 0;
        }
        
            int l = 1;
            while (l < k) {
                double temp[c];
                projection(A[k-1], B[l-1], temp, c);
                for (int j = 0; j < c; j++) {
                    all_projection[j] = all_projection[j] + temp[j];
                }
                l++;
            }
            for (int i = 0; i < c; i++) {
                B[k-1][i] = A[k-1][i] - all_projection[i];
            }
            
        }
        k++;
    }
}

static void test()
{
    double a1[3][10] = {{1,0,1,0},{1,1,1,1},{0,1,2,1}};
    double b1[3][10] = {{0}};
    double dot1;
    gram_schmidt(3, 4, a1, b1);
    int flag = 1;
    for(int i = 0; i < 2; i++)
    for(int j = i+1; j < 3; j++){
    dot1 =  fabs(dot_product(b1[i], b1[j], 4));
    if(dot1 > 0.1)
    {
        flag = 0;
        break;
    }
    }
    if(flag == 0)
        cout << "Vectors are linearly dependent " << endl;
    assert(flag == 1);
    cout << "Passed Test Case 1 " << endl;
    display(3, 4, b1);
    
    double a2[2][10] = {{3,1},{2,2}};
    double b2[2][10] = {{0}};
    double dot2;
    gram_schmidt(2, 2, a2, b2);
    flag = 1;
    for(int i = 0; i < 1; i++)
    for(int j = i+1; j < 2; j++){
    dot2 = fabs(dot_product(b2[i], b2[j], 2));
    if(dot2 > 0.1)
    {
        flag = 0;
        break;
    }
    }
    if(flag == 0)
        cout << "Vectors are linearly dependent " << endl;
    assert(flag == 1);
    cout << "Passed Test Case 2 " << endl;
    display(2, 2, b2);
    
    double a3[2][10] = {{1,2,2},{-4,3,2}};
    double b3[2][10] = {{0}};
    double dot3;
    gram_schmidt(2, 3, a3, b3);
    flag = 1;
    for(int i = 0; i < 1; i++)
    for(int j = i+1; j < 2; j++){
    dot3 = fabs(dot_product(b3[i], b3[j], 3));
    if(dot3 > 0.1)
    {
        flag = 0;
        break;
    }
    }
    if(flag == 0)
        cout << "Vectors are linearly dependent " << endl;
    assert(flag == 1);
    cout << "Passed Test Case 3 " << endl;
    display(2, 3, b3);
}

int main()
{
    int r, c;
    test();
    cout << "Enter the dimension of your vectors"<<endl;
    cin >> c;
    cout << "Enter the number of vectors you will enter "<<endl;
    cin >> r;
    
    double A[20][10];   // a 2-D array for storing all vectors
    double B[20][10] = {{0}};   // a 2-D array for storing orthogonalised vectors
    // storing vectors in array A
    for(int i = 0; i < r; i++)
    {
        cout << "Enter vector "<<i+1<<endl;
        for(int j = 0; j < c; j++)
        {
            cout << "Value "<<j+1<<"th of vector: ";
            cin >> A[i][j];
        }
        cout << endl;
    }
    
    gram_schmidt(r, c, A, B);
    display(r, c, B);
    double dot = 0;
    int flag = 1;
    for(int i = 0; i < r-1; i++)
    {
    for(int j = i+1; j < r; j++)
    {
    dot = fabs(dot_product(B[i], B[j], c));
    if(dot > 1)
    {
        flag = 0;
        break;
    }
    }
    }
    if(flag == 0)
        cout << "Vectors are linearly dependent " << endl;
}
