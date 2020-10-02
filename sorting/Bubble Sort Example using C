/*Bubble Sort - C program to sort an Array 
in Ascending and Descending Order.*/
 
#include <stdio.h>
 
#define MAX 100
 
int main()
{
    int arr[MAX],limit;
    int i,j,temp;
     
    printf("Enter total number of elements: ");
    scanf("%d",&limit);
     
    /*Read array*/
    printf("Enter array elements: \n");
    for(i=0; i<limit; i++)
    {
        printf("Enter element %3d: ",i+1);
        scanf("%d",&arr[i]);
    }
     
    /*sort elements in Ascending Order*/
    for(i=0; i<(limit-1); i++)
    {
        for(j=0; j<(limit-i-1); j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
 
    printf("Array elements in Ascending Order:\n");
    for(i=0; i<limit; i++)
        printf("%d ",arr[i]);
     
    printf("\n");
         
    /*sort elements in Descending Order*/
    for(i=0; i<(limit-1); i++)
    {
        for(j=0; j<(limit-i-1); j++)
        {
            if(arr[j]<arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
 
    printf("Array elements in Descending Order:\n");
    for(i=0; i<limit; i++)
        printf("%d ",arr[i]);
     
    printf("\n");
     
    return 0;
}
