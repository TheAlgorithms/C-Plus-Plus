#include <stdio.h>

// This program intends to do arithmetic on large integers and then store them
// in a file . The two large integers are read from a file. The operations are
// achieved as follows Addition and subtraction are achieved by reversing number
// and adding or subtracting Multiplication and division are achieved by
// adding/subtracting th corresponding number of times and finding a correct
// solution

int num1[1000];     // Big number  1
int num2[1000];     // Big number 2
int result[2001];   // variable to store result
int result1[2001];  // variable to store another result

int decrement(int num[1000])  // The function decrements the number by 1
{
    int i = 0;
    int flag = 1;  // i is the counter variable , flag is the variable to keep
                   // track of whether the number is 0 or not.
    while (num[i] != -1)  // to check if the number is 0
    {
        if (num[i] != 0) {
            flag = 0;
            break;
        }
        i++;
    }
    if (flag == 1)  // if the number is 0 , then return 0
    {
        return 0;
    } else {
        i = 0;
        int carry = 0;
        int flag = 0;  // else decrement the number by 1
        while (num[i] != -1) {
            if (num[i] - carry > 0 && flag == 0) {
                num[i] = num[i] - carry - 1;
                break;
            } else if (num[i] - carry >= 0 && flag == 1) {
                num[i] = num[i] - carry;
                break;
            } else {
                num[i] = 9;
                carry = 1;
                i++;
                flag = 1;
            }
        }
    }
}

int copy(int a[1000], int b[1000])  // copies int array 'a' the array 'b'
{  // copies integer by the integer in the array
    int i = 0;
    while (b[i] != -1) {
        a[i] = b[i];
        i++;
    }
    a[i] = -1;
}

int revnumber(int num[1000])  // reverses the number - swaps (length-i)element
                              // by ielement till length/2
{
    int count = 0;
    int temp;
    while (num[count] != -1) {
        count++;
    }
    count--;
    int i = 0;
    for (i = 0; i <= count / 2; i++) {
        temp = num[i];
        num[i] = num[count - i];
        num[count - i] = temp;
    }
}

int add(int a[1000], int b[1000])  // adds num1+num2
{  // adds ith elements and stores the caary to be addded in the next element's
   // addition
    int i = 0, carry = 0;
    while (a[i] != -1 && b[i] != -1) {
        if (a[i] + b[i] + carry <= 9) {
            result[i] = a[i] + b[i] + carry;
            carry = 0;
        } else {
            result[i] = (a[i] + b[i] + carry) - 10;
            carry = 1;
        }
        i++;
    }

    if (b[i] == -1) {
        while (a[i] != -1) {
            if (a[i] + carry <= 9) {
                result[i] = a[i] + carry;
                carry = 0;
            } else {
                result[i] = a[i] + carry - 10;
                carry = 1;
            }
            i++;
        }
    } else {
        while (b[i] != -1) {
            if (b[i] + carry <= 9) {
                result[i] = b[i] + carry;
                carry = 0;
            } else {
                result[i] = b[i] + carry - 10;
                carry = 1;
            }
            i++;
        }
    }
    if (carry != 0) {
        result[i] = 1;
        i++;
    }
    result[i] = -1;
}

int compare(int a[1000], int b[1000])  // compares if a is greater than b
{  // if number of digits of one number is greater , then the number is greater
   // else it checks element by element till one number is found greater than
   // second.
    revnumber(a);
    revnumber(b);
    int flag = 1, i = 0, flag2 = 0;  // i is counter , flag is variable to check
                                     // which number is greater .
    int count1 = 0, count2 = 0;
    while (a[i] == 0) {
        i++;
    }
    while (a[i] != -1) {
        count1++;
        i++;
    }
    i = 0;
    while (b[i] == 0) {
        i++;
    }
    while (b[i] != -1) {
        count2++;
        i++;
    }
    i = 0;
    if (count1 > count2) {
        revnumber(a);
        revnumber(b);
        return 1;
    } else if (count1 < count2) {
        revnumber(a);
        revnumber(b);
        return 0;
    } else if (count1 == count2) {
        flag = 0;
        while (a[i] != -1) {
            if (a[i] > b[i]) {
                flag = 1;
                break;
            } else if (a[i] < b[i]) {
                flag = -1;
                break;
            } else if (a[i] == b[i]) {
                flag = 0;
                i++;
            }
        }
        if (flag == 0 || flag == 1) {
            revnumber(a);
            revnumber(b);
            return 1;
        } else {
            revnumber(a);
            revnumber(b);
            return 0;
        }
    }
}

int subtract(int d[1000], int c[1000])  // subtracts c from d
{  // subtracts and if it is -ve carries one from the left side.
    int a[1000];
    a[0] = -1;
    int b[1000];
    b[0] = -1;
    copy(b, c);
    copy(a, d);
    int i = 0;
    int flag = 1;  // flag1
    while (flag == 1) {
        flag = 0;
        for (i = 0; b[i] != -1; i++) {
            if (b[i] != 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            decrement(a);
            decrement(b);
        }
    }

    copy(result, a);
    i = 0;
}

int quotient[1000], remain[1000];

int division(int c[1000], int d[1000])  // divides c by d
{
    int a[1000];
    int b[1000];
    copy(a, c);
    copy(b, d);
    int i = 0, flag = 0;

    quotient[0] = -1;
    int one[1000];
    one[0] = 1;
    one[1] = -1;
    remain[0] = -1;
    copy(remain, a);
    i = 0;

    while (compare(remain, b) > 0) {
        add(quotient, one);
        copy(quotient, result);
        subtract(remain, b);
        copy(remain, result);
    }
}

int substring(int a[1000], int b[1000])  // Finds all the substrings
{
    int j = 0;
    int len;
    printf("Enter the length of substring");
    scanf("%d", &len);
    FILE *ptr2;
    ptr2 = fopen("substring1.txt", "w");
    int i = 0;
    for (i = 0; a[i] != -1; i++) {
        fprintf(ptr2, "%d", a[i]);
    }
    fprintf(ptr2, "\n");
    int count = 0;
    while (a[count] != -1) {
        count++;
    }
    for (j = 0; j <= count - len; j++) {
        for (i = j; i < j + len; i++) {
            fprintf(ptr2, "%d", a[i]);
        }
        fprintf(ptr2, "\n");
    }
    fprintf(ptr2, "\n\n");
    for (i = 0; b[i] != -1; i++) {
        fprintf(ptr2, "%d", b[i]);
    }
    count = 0;
    i = 0;
    fprintf(ptr2, "\n");
    while (b[count] != -1) {
        count++;
    }
    j = 0;
    for (j = 0; j <= count - len; j++) {
        for (i = j; i < j + len; i++) {
            fprintf(ptr2, "%d", b[i]);
        }
        fprintf(ptr2, "\n");
    }

    fclose(ptr2);
}

int multiply(int a[1000], int c[1000]) {
    int b[1000];
    copy(b, c);
    result1[0] = -1;
    printf("Entered");
    int i = 0;
    int flag = 1;
    while (flag == 1) {
        flag = 0;
        for (i = 0; b[i] != -1; i++) {
            if (b[i] != 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            add(result1, a);
            decrement(b);
            copy(result1, result);
            i = 0;
        }
    }
}

void main() {
    int choice = 1;
    FILE *ptr;
    ptr = fopen("inputnum.txt", "r");
    int i = 0;
    char ch;
    while (feof(ptr) == 0) {
        if ((ch = fgetc(ptr)) != '\n') {
            num1[i] = (int)ch - 48;
            i++;

        } else
            break;
    }
    num1[i - 1] = -1;
    i = 0;
    while (feof(ptr) == 0) {
        if ((ch = fgetc(ptr)) != '\n')
            num2[i] = (int)ch - 48;
        i++;
    }
    num2[i - 1] = -1;
    fclose(ptr);

    i = 0;
    while (num1[i] != -1) {
        printf("%d", num1[i]);
        i++;
    }

    printf("\n");

    i = 0;
    while (num2[i] != -1) {
        printf("%d", num2[i]);
        i++;
    }
    while (choice != 0) {
        printf("Enter the choice");
        scanf("%d", &choice);
        if (choice == 1) {
            revnumber(num1);
            revnumber(num2);

            ptr = fopen("arithmetic1.txt", "w");
            add(num2, num1);
            i = 0;

            fprintf(ptr, "Addition : ");
            revnumber(result);
            while (result[i] != -1) {
                fprintf(ptr, "%d", result[i]);
                i++;
            }
            fprintf(ptr, "\n");

            subtract(num1, num2);
            revnumber(result);
            i = 0;
            fprintf(ptr, "Subtraction : ");
            while (result[i] != -1) {
                fprintf(ptr, "%d", result[i]);
                i++;
            }
            fprintf(ptr, "\n");

            multiply(num1, num2);
            revnumber(result1);
            fprintf(ptr, "Multiplication : ");
            i = 0;
            while (result[i] != -1) {
                fprintf(ptr, "%d", result1[i]);
                i++;
            }
            fprintf(ptr, "\n");

            division(num1, num2);
            revnumber(remain);
            revnumber(quotient);
            fprintf(ptr, "Division , Quotient : ");
            i = 0;
            while (quotient[i] != -1) {
                fprintf(ptr, "%d", quotient[i]);
                i++;
            }
            i = 0;
            fprintf(ptr, " Remainder : ");
            while (remain[i] != -1) {
                fprintf(ptr, "%d", remain[i]);
                i++;
            }
            fprintf(ptr, "\n");
            revnumber(num1);
            revnumber(num2);
            fclose(ptr);
        }

        if (choice == 2) {
            substring(num1, num2);
        }
    }
}