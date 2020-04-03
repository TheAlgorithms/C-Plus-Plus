#include<stdio.h>
#define MAX 500

void multiply(int num, int * arr, int * arr_size){
        int carry = 0;
        int product;
        for(int i = 0; i<*arr_size; ++i){
                product = arr[i] * num + carry;
                arr[i] = product%10;
                carry = product/10;
        }
        while(carry){
                arr[*arr_size] = carry % 10;
                carry = carry / 10;
                *arr_size += 1;
        }
}

void factorial(int n, int * ans_array, int * ans_size){
        ans_array[0] = 1;
        *ans_size = 1;
        for(int i=2; i<=n; ++i)
                multiply(i, ans_array, ans_size);
}

int main(){
	int arr[MAX], size = 1, sum = 0;
	int *psize = &size;
	factorial(100, arr, psize);
	for(int i = size - 1; i>=0; --i)
		sum += arr[i];
	printf("%d\n", sum);
	return 0;
}
