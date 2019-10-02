//An iterative implementation of Quick Sort

#include<iostream>

using namespace std;


/*Function to sort two values*/
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

/*Function to sort the partition into two halves
 *      -Smaller elements to the left of the pivot
 *      -Greater elements to the right of the pivot
 * l -> starting index
 * r -> ending index
 */
int partition(int arr[], int l, int r){
    int x = arr[r];
    int i = (l-1);

    for(int j=l;j<=r-1;j++){
        if(arr[j] <= x){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[r]);
    return (i+1);

}

void quickSort(int arr[], int l ,int r){
    //Using to mimic recursive calls in recursive Quick Sort
    int stack[r-l+1];
    int top=-1; 

    stack[++top] = l;
    stack[++top] = r;
    
    //Pop while the stack is not empty
    while(top >= 0){
        r = stack[top--];
        l = stack[top--];

        //Pivoting
        int p = partition(arr,l,r);

       //Elements smaller than pivot go to the left
        if(p-1 > 1){
            stack[++top] = l;
            stack[++top] = p-1;
        } 

        //Elements greater than pivot go to the right
        if(p+1 < r){
            stack[++top] = p+1;
            stack[++top] = r;
        }
    }
}

int main(){
    
    //TEST CODE
    int n = 10;
    int arr[n] = {4,2,6,9,2,1,7,10,11,20};

    quickSort(arr,0,n-1);

    //Printing the array
    for(int i=0;i<n;i++) cout << arr[i] << " ";
    cout << "\n";

    return 0;
}
