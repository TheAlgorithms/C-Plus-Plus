#include<stdio.h>

long long collatz(long long num){
	long long count = 0;
	while( num!= 1){
		while((num&1)==1){
			num = (3*num + 1)/2;
			count +=2;
		}
		while((num&1)==0){
			num/=2;
			++count;
		}
	}
	return count;
}

int main(){
	long long count = 0, max = 0, mnum = 0, num = 0;
	for(long long i = 1;i<1000000;++i){
		count = collatz(i);
		if(count > max){
			max = count;
			mnum = i;
		}
		count = 0;
	}
	printf("%d\n", mnum);
	return 0;
}
