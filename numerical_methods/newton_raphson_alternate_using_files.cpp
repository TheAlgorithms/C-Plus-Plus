#include <math.h>
#include <stdio.h>

// The program is simple application of Newton-Raphson Method to find roots of
// the number . An initial value of 10 is taken and then it is used to find a
// number which is close to the root with a given accuracy using the method Last
// Modified  09-11-2019  18:43      Copyrights:- SANCHIT GUPTA (Elliptic
// Studios)
float roots(float X, float Y)  // The function uses a simple recursion to find
                               // the root to an accuracy of 0.0001
{
    float temp;
    temp = X - (((X * X) - Y) / (2 * X));
    if (((X - temp) > 0.0001) ||
        ((X - temp) <
         -0.0001))  // +- 0.0001 is the accuracy to which the root is found out.
        return roots(temp, Y);  // Calls the function recursively.
    else
        return temp;  // Returns the final root value
}

int main()  // The main function opens the files ,reads and writes the answer
            // rounding it to 2 decimals and then finally closes the files
{
    float input;
    FILE *ptr, *ptr2;
    ptr = fopen("roots.txt", "r");    // open the file to open.
    ptr2 = fopen("output.txt", "w");  // open the file to write.
    while (feof(ptr) == 0)            // till end of file is reached
    {
        fscanf(ptr, "%f", &input);       // read the input
        fprintf(ptr2, "%f    ", input);  // print the number
        fprintf(ptr2, "%f\n",
                roundf(roots(10, input) * 100) /
                    100);  // find the root and print in the file.
    }

    fclose(ptr);
    fclose(ptr2);
}