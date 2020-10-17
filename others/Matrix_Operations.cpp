#include <stdio.h>

// This program takes two input matrices from the user and then gives him
// several options to allow him to compute the determinant or product or dot
// product or rank of the matrices Last Modified 09-11-2019   18:55 Copyrights:-
// SANCHIT GUPTA (Elliptic Studios)

int InitialiseArray(float A[25][25]);  // Initialises matrix to 0
int Multiplication(float A[25][25], float B[25][25], float C[25][25], int row1,
                   int row2, int col1, int col2);  // Multiplies two matrices
float Determinant(float A[25][25], int row1,
                  int row2);  // finds the determinant of two matrices
int colexchange(float A[25][25], int row1, int col1, int i,
                int j);  // exchange ith and jth column of the matrix
float Dotproduct(float A[25][25], float B[25][25], int row1, int row2, int col1,
                 int col2);  // finds the dot product of two matrices
void columnupdate(float A[25][25], int row1, int col1, int i, int j,
                  float temp);  // updates the column of the them atrix
int rank(float A[25][25], int row1, int col1);  // finds the rank of the matrix
int rowexchange(float A[25][25], int row1, int col1, int i, int j);

void main() {
    float Array1[25][25], Array2[25][25];
    float Array3[25][25];
    int size = 25;
    float number = 0;
    int i = 0, j = 0;            // loop variables
    int row1, row2, col1, col2;  // number of rows and columns in matrix 1 and 2
    InitialiseArray(Array1);     // initialises all arrays
    InitialiseArray(Array2);
    InitialiseArray(Array3);

    // Enter the number of rows and columns and hence enter their values
    printf("Enter the number of rows of matrix1 ");
    scanf("%d", &row1);
    printf("Enter the number of columns of matrix1  ");
    scanf("%d", &col1);

    for (i = 0; i < row1; i = i + 1) {
        for (j = 0; j < col1; j = j + 1) {
            scanf("%f", &number);
            Array1[i][j] = number;
        }
    }
    // Enter the number of rows and columns and hence enter their values
    printf("Enter the number of rows of matrix2  ");
    scanf("%d", &row2);
    printf("Enter the number of columns of matrix2  ");
    scanf("%d", &col2);
    for (i = 0; i < row2; i = i + 1) {
        for (j = 0; j < col2; j = j + 1) {
            scanf("%f", &number);
            Array2[i][j] = number;
        }
    }

    int choice = 1;
    while (choice != 0)  // loop to get the choice of the user
    {
        printf(
            "Enter your choice : 0.Exit \n 1.Multiplication of two arrays  \n "
            "2.Dot product \n 3.Determinant \n 4.Rank");
        // Let the user Enter his choice on what he wants to do
        scanf("%d", &choice);
        /*Finding Multiplication Answer*/
        if (choice == 1) {
            Multiplication(Array1, Array2, Array3, row1, row2, col1, col2);

            /*for(i=0;i<row1;i++)
              {for(j=0;j<col1;j++)
              {printf("%d ",Array1[i][j]);}
              printf("\n");
              }

              for(i=0;i<row2;i++)
              {for(j=0;j<col2;j++)
              {printf("%d ",Array2[i][j]);}
              printf("\n");
              }*/

            printf("\n");
            for (i = 0; i < row1; i++) {
                for (j = 0; j < col2; j++) {
                    printf("%f ", Array3[i][j]);
                }
                printf("\n");
            }
        }

        /*Dot Product */
        if (choice == 2) {
            float dot = Dotproduct(Array1, Array2, row1, row2, col1, col2);
            printf("%f", dot);
        }

        if (choice == 3) {
            int choice2 = 1;
            printf(
                "Enter the number of the matrix of which you want to find "
                "determinant ");
            scanf("%d", &choice2);
            if (choice2 == 1) {
                float det = Determinant(Array1, row1, col1);
                /*printf("\n");
                for (i = 0; i < row1; i++) {
                  for (j = 0; j < col1; j++) {
                    printf("%f ", Array1[i][j]);
                  }
                  printf("\n");
                */
                printf("The determinant is %f", det);
            } else if (choice2 == 2) {
                float det = Determinant(Array2, row2, col2);
                printf("The Determinant is %f", det);
            }
        }

        if (choice == 4) {
            printf("The rank is %d", rank(Array1, row1, col1));
        }
    }
}

int InitialiseArray(float A[25][25]) {
    int i = 0, j = 0;
    for (i = 0; i < 25; i = i + 1) {
        for (j = 0; j < 25; j = j + 1) {
            A[i][j] = 0;
        }
    }

    return 0;
}

int Multiplication(
    float A[25][25], float B[25][25], float C[25][25], int row1, int row2,
    int col1,
    int col2) {  // Just check if multiplicable and also use the simple logic of
                 // multiplcation ising two iterated loops and a while loop
    int i = 0;   // The first row is successively multiplied by first column and
                 // then with second column to get elements of final array
    int j = 0;
    if (col1 != row2) {
        printf("Not multiplicable");
        return 0;
    } else {
        int answer;
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                int p = 0;
                int q = 0;
                while (p < col1 && q < row2) {
                    answer = answer + A[i][p] * B[q][j];
                    p++;
                    q++;
                }
                C[i][j] = answer;
                answer = 0;
            }
        }
    }
}

float Dotproduct(
    float A[25][25], float B[25][25], int row1, int row2, int col1,
    int col2) {  // Every element is multiplied with its corresponding in second
                 // matrix. If orders of both different then not possible
    int i = 0;
    int j = 0;
    int answer = 0;
    if (row1 != row2 || col1 != col2) {
        printf("Error , dot product not possible with given matrices");
    } else {
        answer = 0;
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                answer = answer + A[i][j] * B[i][j];
            }
        }
    }
    return answer;
}

int colexchange(float A[25][25], int row1, int col1, int i, int j) {
    int k = 0;
    int temp = 0;
    for (k = 0; k < row1; k++) {
        temp = A[k][j];
        A[k][j] = A[k][i];
        A[k][i] = temp;
    }
    return 0;
}

int rowexchange(float A[25][25], int row1, int col1, int i, int j) {
    int k = 0;
    int temp = 0;
    for (k = 0; k < col1; k++) {
        temp = A[j][k];
        A[j][k] = A[i][k];
        A[i][k] = temp;
    }
    return 0;
}

void columnupdate(float A[25][25], int row1, int col1, int i, int j,
                  float temp) {
    int counter = 0;
    for (counter = 0; counter < row1; counter++) {
        (A[counter][j]) = (A[counter][j]) - temp * (A[counter][i]);
        /*printf("\n");
            for(i=0;i<row1;i++)
            {for(j=0;j<col1;j++)
                {printf("%d ",A[i][j]);}
                printf("\n");
            }*/
    }
}

float Determinant(
    float B[25][25], int row1,
    int col1) {  // Finds Determinant of matrix using Gaussian Eliminaton Method
                 // . i.e by making the lower diagonal of the marix 0 and hence
                 // multiplying he diagonal elements

    float A[25][25];

    int sign = 1;
    int i = 0;
    int j = 0;
    for (i = 0; i < 25; i++) {
        for (j = 0; j < 25; j++) {
            A[i][j] = B[i][j];
        }
    }
    for (i = row1 - 1; i >= 0; i--) {
        int k = 0;
        while (A[i][i] == 0) {
            colexchange(A, row1, col1, i, k);
            sign = sign * -1;
            k++;
        }
        for (j = 0; j < i; j++) {
            if (A[i][j] == 0) {
                continue;
            } else {
                // printf("i: %f , j: %f",A[i][j], A[i][i]);
                float alpha = A[i][j] / A[i][i];
                // printf("alpha: %f", alpha);
                columnupdate(A, row1, col1, i, j, alpha);
            }
        }
    }

    /*printf("\n");
    for (i = 0; i < row1; i++) {
      for (j = 0; j < col1; j++) {
        printf("%f ", A[i][j]);
      }
      printf("\n");
    } */
    float det = 1;
    int l = 0;
    for (l = 0; l < row1; l++) {
        det = det * A[l][l];
    }
    return det * sign;
}

/*void Gaussian(float A[25][25], int row1, int col1) {		//Finds Determinant
   of matrix using Gaussian Elimination Method . i.e by making the lower
   diagonal of the marix 0 and hence multiplying he diagonal elements

    int i = 0;
    int j = 0;
    for (i = row1 - 1; i >= 0; i--)
    {
        int k = 0;
        while (A[i][i] == 0)
        {
            if(k==i)
            {
                break;
            }
            colexchange(A, row1, col1, i, k);
            k++;
        }

        if(k==i)
        {
            Rank = Rank - 1; continue;
        }


        for (j = 0; j < i; j++)
        {
            if (A[i][j] == 0)
            {
                continue;
            }
            else
            {
                //printf("i: %f , j: %f",A[i][j], A[i][i]);
                float alpha = A[i][j] / A[i][i];
                //printf("alpha: %f", alpha);
                columnupdate(A, row1, col1, i, j, alpha);
            }
        }
    }*/

/*printf("\n");
for (i = 0; i < row1; i++) {
  for (j = 0; j < col1; j++) {
    printf("%f ", A[i][j]);
  }
  printf("\n");
} */

//}

int rank(float A[25][25], int row1,
         int col1) { /*

                 int i = 0, j = 0, k = 0, flag = 1;
                     printf("%f",Determinant(A, row1, col1));
                     while (Determinant == 0)

                     {

                         Gaussian(A, &row1, &col1);
                         k = 0;
                         for (i = 0; i < row1; i++)
                         {
                             flag = 1;
                             for(j=0;j<col1;j++)
                             {
                                 if(A[j][i]!=0)
                                 {
                                     flag = 0;
                                     break;
                                 }
                             }
                             if (flag == 1)
                             {
                                 colexchange(A, row1, col1,col1-1,i);
                                 col1 = col1 - 1;
                             }
                         }
                     }
                     i = 0, j = 0;
                         for (i = 0; i < row1; i++)
                         {
                             printf("\n");
                             for(j=0;j<col1;j++)
                             {
                                 printf("%f  ", A[i][j]);
                             }
                         }*/

    int rank = 0;
    if (col1 > row1) {
        rank = row1;
    } else {
        rank = col1;
    }
    int row = 0;
    int col = 0;
    float mult = 0;
    int i = 0;
    for (row = 0; row < rank;
         row++)  // row < rank => lower triangle region ( including diagonal) of
                 // rank * rank matrix
    {
        /*  if ( row >= m )	   break;  //defensive programming; */
        if (A[row][row]) {
            for (col = 0; col < col1; col++) {
                if (col != row) {
                    mult = (double)A[col][row] / A[row][row];
                    for (i = 0; i < rank; i++) {
                        A[col][i] -= mult * A[row][i];
                    }
                }
            }
        } else {
            int reduce = 1;

            for (i = row + 1; i < row1; i++) {
                if (A[i][row]) {
                    // swap(mat, row, i, rank);
                    rowexchange(A, row1, rank, row, i);
                    reduce = 0;
                    break;
                }
            }

            if (reduce) {
                rank--;
                for (int i = 0; i < row1; i++) {
                    A[i][row] = A[i][rank];
                }
            }

            row--;
        }
    }
    return rank;
}