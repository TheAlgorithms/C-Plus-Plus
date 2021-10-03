/*
That is a Quicksort algorithm version using the Hoare Partition method and
choosing the first number of the array as the pivot.
*/

#include <iostream>
#include <cstdlib>

using namespace std;

int HoarePartition(int *vet, int l, int r){
    int i = l, j = r+1, p = vet[l];
    do{ 
        do{
            i = i+1;
        }while((vet[i] < p) && (i < r));
        do{
            j = j-1;
        }while(vet[j] > p);
        swap(vet[j],vet[i]);
    }while(i < j);
    swap(vet[j],vet[i]);
    swap(vet[j],vet[l]);
    return j;
}

void quickSort(int *vet, int l, int r){
    int s;
    if(l < r){
        s = HoarePartition(vet, l, r); 
        quickSort(vet, l, s-1);
        quickSort(vet, s+1, r);
    }
}

#define max 100

int main(){

    int n, v[max]; //n is the size of the array

    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    quickSort(v, 0, n-1);
    
    printf("\n");

    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }

    return 0;
}