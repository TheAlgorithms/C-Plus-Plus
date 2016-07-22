#include<stdio.h>
#include<conio.h>
int main(){
	int number,decimal_number,temp=1;
printf("Enter any binary number= ");
scanf("%d",&number);
     int remainder;
	  while(number>0){
	  
	  remainder= number%10;
	  number=number/10;
	  decimal_number+=remainder*temp;
	  temp=temp*2;//used as power of 2
	  
 }
 printf("%d",decimal_number);
}
