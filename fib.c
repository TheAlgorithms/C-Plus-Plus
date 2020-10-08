#include<stdio.h>
void main(){
    int n,nxt,a=0,b=1,i;
    scanf("%d",&n);
    printf("%d\t%d",a,b);
    for(i=0 ;i<n-2;i++){
        nxt=a+b;
        a=b;
        b=nxt;
        printf("\t%d",nxt);
    }
}
