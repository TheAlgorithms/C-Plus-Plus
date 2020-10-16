//
//  main.cpp
//  Gram Schimdt Orthonormalisation
//
//  Created by akanksha gupta on 02/10/20.
//  Copyright © 2020 akanksha gupta. All rights reserved.
//
//  Precision of vectors is taken upto 6 decimals

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

/*
 
 */

double dot_product (double x[], double y[], int c) {
    double sum = 0;
    for (int i = 0; i < c; i++) {
        sum += x[i] * y[i];
    }
    return sum;
}


void projection (double x[], double y[], double temp[], int c){
    double dot = dot_product(x, y, c);
    double anorm = dot_product(y, y, c);
    double factor = dot/anorm;
    for (int i = 0; i < c; i++) {
      temp[i]  = y[i] * factor;
    }
}


using namespace std;

int main()
{
    cout << "Enter the dimension of your vectors"<<endl;
    int c;
    cin >> c;
    cout << "Enter the number of vectors you will enter "<<endl;
    int r;
    cin >> r;
    
    double A[r][c];   // a 2-D array for storing all vectors
    
    // storing vectors in arrat A
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
    
    if(c < r)
    {
        cout << "Dimension of vector is less than number of vector, hence \n first "<<c<<" vectors are orthonormalized";
        r = c;
    }
    
    int k = 1;
    double B[r][c];    // a 2-D array for storing orthonormalized vectors
    
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
    
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    
}
