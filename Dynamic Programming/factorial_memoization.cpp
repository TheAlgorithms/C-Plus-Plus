// Factorial of a number using memoization
#include<stdio.h>
int result[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int factorial(int num){
    if(num < 0){
        printf("Number should not be negative.");
        return(0);
        }
    if(result[num] != -1)
        return result[num];
    else{
        result[num] = num * factorial(num - 1);
        // uncomment the following to see how recalculations are avoided
        // printf(result)
        return(result[num]);
        }
    }

int main(){
    result[0] = 1;
    result[1] = 1;
    printf("%d",factorial(5));
    return(0);
}
