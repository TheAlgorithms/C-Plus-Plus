#include<stdio.h> //preprocessor directive
void tower_hanoi(int n,char A,char B,char C)  //Tower of Hanoi Function
{ if(n>0)
{ tower_hanoi(n-1,A,C,B);
printf("Moved: %d no. disc (%c,%c)\n",n,A,C); //Moving disc from one place to other
tower_hanoi(n-1,B,A,C);
}
}
int main() //Decleration of Main function
{ int a; 
 printf("Enter number of disks in which TOH operation to be performed: ");
scanf("%d",&a);
 tower_hanoi(a,'A','B','C');
return 0;
}