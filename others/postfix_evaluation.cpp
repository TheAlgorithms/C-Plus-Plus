/**
 * @file
 * @brief Evaluation of Postfix Expression
 * @author [Darshana Sarma](https://github.com/Darshana-Sarma)
 * @details
 * Create a stack to store operands (or values).
 * Scan the given expression and do following for every scanned element.
 * If the element is a number, push it into the stack
 * If the element is a operator, pop operands for the operator from stack.   
 * Evaluate the operator and push the result back to the stack
 * When the expression is ended, the number in the stack is the final answer
 */
#include <array>           // for std::array
#include <iostream>        // for io operations 
#include <cassert>  // for assert

// Maximum size for stack
const int MAX_SIZE = 20;

// Defining stack
std::array<int, MAX_SIZE> stack;

// Index of top value in stack array
int top;

/**
 * Pushing operand, also called the integer in the array to the stack
 * @param operand integer value from the input array or evaluation
 * @returns none
 */
void push(int operand){
    top++;
    stack[top]=operand;
}

/**
 * Popping operand, also called the integer from the stack
 * @param none
 * @returns operand integer on top of stack
 */
int pop(){
    int operand = stack[top];
    top--;
    return operand;
}

/**
 * Evaluate answer using given operands and operation
 * @param a integer
 * @param b integer
 * @param operation operation to be performed with respective integers
 * @returns none
 */  
void evaluate(int a, int b, char operation){
    int c;
    switch(operation){
        case '+':
            c=a+b;
            push(c);
            break;

        case '-':
            c=a-b;
            push(c);
            break;

        case '*':
            c=a*b;
            push(c);
            break;

        case '/':
            c=a/b;
            push(c);
            break;

        default:
            std::cout<<"Operator not defined\n";
            break;
    }
}


/**
 * Postfix Evaluation algorithm to compute the value from given input array
 * @param input Array of characters consisting of integers and operations
 * @param N Array size
 * @returns stack[top] returns the top value from the stack
 */ 
template <std::size_t N>
int postfix_evaluation(std::array<char,N> input){

    top = -1;
    int j=0;
    while(input[j]){
        char scan = input[j];
        if(isdigit(scan)){
            
            push(scan-'0');
            

        }else{
            int op2 = pop();
            int op1 = pop();

            evaluate(op1,op2,scan);
        }
        j++;
    }

    std::cout<<stack[top]<<"\n";

    return stack[top];

}

/**
 * Test function 1 with input array
 * {'2', '3', '1', '*', '+', '9', '-'}
 * @returns none
 */
static void test_function_1(){

    std::array<char,7> input = {'2', '3', '1', '*', '+', '9', '-'};

    int answer = postfix_evaluation(input);

    assert(answer==-4);

}

/**
 * Test function 2 with input array
 * {'1', '2', '+', '2', '/', '5', '*', '7', '+'}
 * @returns none
 */
static void test_function_2(){
        
    std::array<char, 9> input = {'1', '2', '+', '2', '/', '5', '*', '7', '+'};
    int answer = postfix_evaluation(input);

    assert(answer==6);

}

/**
 * Main function
 */
int main(){

    test_function_1();
    test_function_2();

    return 0;
}




