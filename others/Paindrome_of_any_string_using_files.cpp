#include <stdio.h>

// It checks if the number or input string is a palindrome. A palindrome is a
// string which is the same when read from the first and last. Last Modified
// :-23:22   15-11-2019			Copyrights:-SANCHIT GUPTA (Elliptic Studios)

int palindrome(char arr[])  // function to check if string is palindrome
{
    int length = 0;  // initialise length to 0.
    int i = 0;
    while (arr[i] != '\0')  // till the end of character array is used . FInd
                            // the length of the string
    {
        length++;
        i++;
    }
    printf("%d", length);
    int flag = 1;
    for (i = 0; i < length / 2;
         i++)  // Go till half of the string and check if the string reads the
               // same from the start or the end.
    {
        printf("%c", arr[length - i - 1]);
        if (arr[length - i - 1] != arr[i]) {
            flag = 0;
            break;  // if at any point it is unequal ,assign flag as 0 and break
                    // the loop.
        }
    }
    if (flag == 1)  // if the flag still remains 1 , then return 1 as the output
                    // signifying that the string is a palindrome
    {
        return 1;
    } else if (flag == 0) {
        return 0;
    }
}

void main() {
    FILE *ptr, *ptr2;
    char ar[20] = {'a', 'b', 'c', 'd', 'd',
                   'c', 'b', 'a', '\0'};  // Initialises the character string.
    ptr = fopen("input.txt", "r");
    ptr2 = fopen("output.txt", "w");
    while (feof(ptr) == 0)  // till end of file is reached.
    {
        fscanf(ptr, "%s", ar);
        fprintf(ptr2, "%s ", ar);
        fprintf(ptr2, "%d \n",
                palindrome(ar));  // writes the output -> 1 if its palindrome
                                  // and 0 if it isnt palindrome
    }
}