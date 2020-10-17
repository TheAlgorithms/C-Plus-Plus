/**************************************************************************
 *  Program-2 DS_LAB - 7
 *  File:    PostFix.cpp
 *
 *  Purpose:    To evaluate a postfix expression
 *
 *  Author:    Sanchit Gupta (CS19B071)
 *
 *  Created:    16th Sept , 2020  3:00pm
 *
 *  Last modified:  16th Sept , 2020  3:00pm
 *
 *  Bugs:    None
 *
 * While(!(succeed==try());
 **************************************************************************/
#include <stdio.h>
#include <string.h>

#include <iostream>
/*  The class stack defines an ADT stack.
    See Ref. Aho, Hopcroft and Ullmann : Data Structures and Algorithms,
    Addison Wesley, 1978. */

/* begin {Definition of class stack} */

#define STACK_SIZE  1000  // Define StackSize to be 1000
#define EXPR_LENGTH 1000  // Define ExprLength as 1000
typedef int ElemType;     // TypeDef element Type to be int

using namespace std;
/* Stack ADT predefined with Top , Push , Pop , Empty and makeNull functions.
Has elements an array of integers an a pointer to the top of stack*/
class stack {
    ElemType stackArray[STACK_SIZE];  // A stack of characters
    int tos;                          // A pointer to the top of stack.

 public:
    ElemType Top();         // returns the element on Top of the stack
    void Push(ElemType x);  // Pushes an element on to the stack
    ElemType Pop();         // Pops an element from the stack
    int Empty();            // returns 1 if stack is Empty
    void MakeNull();        // creates an Empty stack
};
/* end{Definition of class stack} */

/* begin{Implementation of the class stack} */

ElemType stack::Top() {
    if (tos < STACK_SIZE)
        return (stackArray[tos]);
    else
        return (0);
}

int stack::Empty() {
    if (tos >= STACK_SIZE)
        return 1;
    else
        return 0;
}

void stack::Push(ElemType x) {
    tos--;
    stackArray[tos] = x;
}

ElemType stack::Pop() {
    ElemType tmp;

    if (tos >= STACK_SIZE)
        return (-1);
    else {
        tmp = stackArray[tos];
        tos++;
        return (tmp);
    }
}

void stack::MakeNull() { tos = STACK_SIZE; }
/* end {Implementation of stack} */

/* Function to evaluate PostFix Expression
Arguemenst :- A pointer to a 2D character array and the length of expression
Return Value :- An integer Result */
int EvaluatePostFix(char **postFixExpr, int exprLength) {
    int result;    // An integer for result
    int i = 0;     // Iteration variable
    stack s;       // A stack s
    s.MakeNull();  // Allocate memory to stack
    ElemType number;
    while (i != exprLength)  // While there are elements in expression
    {
        ElemType a, b, opr;            // three integers
        if (postFixExpr[i][0] == '+')  // If the term is an operation
        {                              // carry it out on the top two elem of
            a = s.Pop();               // stack and push back the result
            b = s.Pop();
            opr = a + b;
            // cout<<opr<<" ";
            s.Push(opr);
        } else if (postFixExpr[i][0] == '-') {
            a = s.Pop();
            b = s.Pop();
            opr = b - a;
            // cout<<opr<<" ";
            s.Push(opr);
        } else if (postFixExpr[i][0] == '*') {
            a = s.Pop();
            b = s.Pop();
            opr = b * a;
            // cout<<opr<<" ";
            s.Push(opr);
        } else if (postFixExpr[i][0] == '/') {
            a = s.Pop();
            b = s.Pop();
            opr = b / a;
            // cout<<opr<<" ";
            s.Push(opr);
        } else           // Otherwise if it is a number
        {                // Calculate the number in decimal
            number = 0;  // format and push it in stack
            int j = 0;
            // cout<<"n"<<postFixExpr[i]<<" ";
            while (postFixExpr[i][j] <= 57 && postFixExpr[i][j] >= 48) {
                // cout<<postFixExpr[i][j];
                number = number * 10 + ((int)postFixExpr[i][j] - 48);
                j++;
            }
            // cout<<" ";
            // cout<<"n"<<number<<" ";
            s.Push(number);
        }
        i++;
    }
    /*


    Write your code here



    */
    result = s.Pop();  // Pop the only value left in s

    return result;  // return the result
}

int main() {
    char **postFixExpr;  // Pre declared pointer to 2D arr
    int n;               // length of expression
    int i;               // iteration variable
    cin >> n;            // Input the size
    i = 0;
    postFixExpr = new char *[1005];  // Allocate memory to D array
    while (i != n) {
        postFixExpr[i] = new char[10];  // Read each term and insert in
        cin >> postFixExpr[i];          // 2D char array
        cout << postFixExpr[i] << " ";
        i++;
    }
    cout << endl;
    /* Read the input postfix expression */

    /*

    Write your code here


    */

    int value = (int)EvaluatePostFix(postFixExpr,
                                     n);  // Evaluate the postfix expression
    std::cout << "The Result is :" << value << std::endl;  // Print the result
    return 0;  // return 0 in case of multiple files
}