#include<stdio.h>
#include<stdlib.h>
int fact(int);
int main()
{
	int n;
	printf("enter the no.");
	scanf("%d",&n);
	printf("factorial of %d is %d",n,fact(n));
	
}
 int fact(int m)
 {
    int f;
	if(m==1)
	{
	
	return 1;
}
else if(!(m>0))
exit(0);
	return m*fact(m-1);	
 }
