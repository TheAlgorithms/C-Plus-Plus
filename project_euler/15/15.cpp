#include<stdio.h>

void nCr(int n, int r, long long * ans) {
    if(r > n / 2)
	 r = n - r; // This is because nCr(n, r) == nCr(n, n - r)
    *ans = 1;
    int i;
    for(i = 1; i <= r; i++) {
        *ans *= n - r + i;
        *ans /= i;
    }
}

int main(){
	long long ans;
	nCr(40, 20, &ans);
	printf("%lld\n", ans);
	return 0;
}
