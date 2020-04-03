#include<stdio.h>
#define MAX 1001

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

void power(int * array, int * array_size, int pow){
	array[0] = 2;
	*array_size = 1;
	for(int i = 2; i<=pow; ++i)
		multiply(2, array, array_size);
}

int main(){
	int arr[MAX], ans = 0;
	int s = 1;
	int *size=&s;
	power(arr, size, 1000);
	for(int i=s-1; i>=0; --i){
		ans += arr[i];
	}
	printf("%d\n", ans);
	return 0;
}
