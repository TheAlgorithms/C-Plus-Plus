/* 
Q:-Given a (0-indexed) nxm matrix with a  binary value in it i.e(0, 1)
you have to find the Square with Max area consisting of all 1's in a binary matrix ?

Input:
4 5
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output:
4

(0-index nxm matrix)
Explanation: square from point (1, 2) to (2, 3) contain maximum area which of length 2 or
square from point (1, 3) to (2, 4) contain maximum area which of length 2.


*/
#include<iostream>
using std::cin;
using std::cout;
using namespace std;

int main(){
    
    cout<<"Enter the Height and Width of matrix respectively:\n";
    int H, W;
    cin>>H>>W;  /* H=height of matrix,  W=width of matrix */

    int matrix[H][W];

    cout<<"Enter the value of matrix\n";
    for(int row=0; row<H; row++){
        for(int col=0; col<W; col++){
            cin>>matrix[row][col];
        }
    }

     
      int lengthof_square_submatrix[H][W];

     /* initialize all the value with zero */
      for(int row=0; row<H; row++){
        for(int col=0; col<W; col++){
            lengthof_square_submatrix[row][col]=0;
        }
    }




    /*
    lengthof_square_submatrix[r][c]==(length of maximum square submatrix containing all value 1 and ending at rth row and cth column.)
       
       value
       matrix[x][y]=
       1 0 1 0 0
       1 0 1 1 1
       1 1 1 1 1
       1 0 0 1 0
      
      value of
      lengthof_square_submatrix[x][y]=
      1 0 1 0 0
      1 0 1 1 1
      1 1 1 2 2
      1 0 0 1 0


     if(matrix[x][y]==0) then lengthof_square_submatrix[x][y]=0;
     since square sub-matrix ending with xth row and yth column contain a value 0 as the rightmost bottom 
     so it's impossible to make square sub-matrix with value as 1

     else{

         1 1
         1 1

         only square of sub-matrix containing all value is (1) of length 2 is possible
         if  value of diagonally above it,i.e (x-1, y-1) to the left of it i.e(x-1, y) and to the above of it i.e(x, y-1) must be greater than or equal to 1;

         1 1 1
         1 1 1
         1 1 1

         only square of sub-matrix containing all value is (1) of length 3 is possible
         if  value of diagonally above it,i.e (x-1, y-1) to the left of it i.e(x-1, y) and to the above of it i.e(x, y-1) must be greater than or equal to 2;
         

         1 1 1 1 . .
         1 1 1 1 . .
         1 1 1 1 . .
         1 1 1 1 . .
         . . . .
         . . . .

         similarly
         only square of sub-matrix containing all value is (1) of length n is possible
         if  value of diagonally above it,i.e (x-1, y-1) to the left of it i.e(x-1, y) and to the above of it i.e(x, y-1) must be greater than or equal to n-1;


     }


    */


    int maximum_length_square=0;   /* maximum_length_square--->maximum length of square containing all value in it is 1. */

    for(int row=0; row<H; row++){
        for(int col=0; col<W; col++){
            int value=matrix[row][col];
            
            if(value==1){
                lengthof_square_submatrix[row][col]=1;

                if(row>0 && col>0)
                lengthof_square_submatrix[row][col]=1+min(min(lengthof_square_submatrix[row][col-1], lengthof_square_submatrix[row-1][col]) , lengthof_square_submatrix[row-1][col-1]);
            }
            

            if(maximum_length_square < lengthof_square_submatrix[row][col] ){
                maximum_length_square = lengthof_square_submatrix[row][col];

            }
        }
    }
    
    /* So maximum square area containing all the value 1 is (max_length_square*max_length_square). */
      int answer=maximum_length_square*maximum_length_square;

     cout<< answer <<"\n";

    
}