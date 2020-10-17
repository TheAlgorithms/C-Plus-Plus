#include <math.h>
#include <stdio.h>
// The program read three integers at a time and forms the quadratic ax^2 + bx +
// c = 0 and hence finds it roots respectively and writes them in the output
// file roots.txt  The output file is given in .csv format Last Modified
// 09-11-2019 18:32       Copyrights:-SANCHIT GUPTA (Elliptic Studios)
int printroots()  // The function print roots basically finds the roots and
                  // prints them in a file
{
    FILE *ptr;
    FILE *ptr2;
    int a, b, c;
    ptr2 = fopen("roots.txt", "w");   // open writing file
    ptr = fopen("results.csv", "r");  // open reading file
    int desc = 0;
    while (
        feof(ptr) ==
        0)  // till end of file , read a,b,c , apply equation and write in file
    {
        fscanf(ptr, "%d", &a);
        fgetc(ptr);

        fscanf(ptr, "%d", &b);
        fgetc(ptr);

        fscanf(ptr, "%d", &c);
        fgetc(ptr);

        desc = (b * b - 4 * a * c);  // calculate the descriminant
        fprintf(ptr2, "%d %d %d", a, b, c);
        if (desc >=
            0)  // check for cases if descriminant is greater than 0 and real
                // roots are there or if less than 0 and the roots are complex.
        {
            fprintf(ptr2, "   %f   ",
                    (float)(-b + (sqrt(desc))) / (float)(2 * a));
            fprintf(ptr2, "   %f   \n",
                    (float)(-b - (sqrt(desc))) / (float)(2 * a));
        } else {
            fprintf(ptr2, "   %f+i%f   ", (float)-b / (float)(2 * a),
                    (float)sqrt(4 * a * c - b * b) / (float)(2 * a));
            fprintf(ptr2, "   %f-i%f   \n", (float)-b / (float)(2 * a),
                    (float)sqrt(4 * a * c - b * b) / (float)(2 * a));
        }
    }

    if (ptr != NULL) {
        fclose(ptr);
    }
    if (ptr2 != NULL) {
        fclose(ptr2);
    }  // close the open files
}

void main() {
    printroots();  // just call the funtion in void main
}