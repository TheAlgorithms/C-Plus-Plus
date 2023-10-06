#include<iostream>
using namespace std;

void printArray(int arr[3][100],int n){
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void sort(int arr[3][100], int n){
    for(int i = 0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[0][j]<arr[0][i]){
                int temp1 = arr[0][i],temp2 = arr[1][i],temp3 = arr[2][i];
                arr[0][i] = arr[0][j];
                arr[1][i] = arr[1][j];
                arr[2][i] = arr[2][j];

                arr[0][j] = temp1;
                arr[1][j] = temp2;
                arr[2][j] = temp3;
                
            }
        }
    }
}

int main(){
    // sort all edges in increasing order of weights
    // thn take each vertex and if it does not form cycle thn add it to the graph and cost

    int v = 6, cost = 0, e = 0;
    int adj[6][6] = {{0,3,0,6,0,7},{3,0,1,4,0,0},{0,1,0,5,0,0},{6,4,5,0,10,0},{0,0,0,10,0,12},{7,0,0,0,12,0}};
    bool check[6];

    for(int i=0;i<v;i++){
        check[i] = false;
    }

    int arr[3][100];
    // 0 => weight     1 => parent1     2 => parent2

    // find all non zero weight edges
    int k = 0, n=0;
    for(int i=0;i<v;i++){
        for(int j=n;j<v;j++){
            if(adj[i][j]!=0){
                arr[0][k] = adj[i][j];
                arr[1][k] = i; 
                arr[2][k] = j; 
                k++;
            }
        }
        n++;
    }

    cout<<endl;
    printArray(arr,k-1);
    cout<<endl;

    // sort the edges in increasing order of weight
    sort(arr ,k-1);
    cout<<endl;
    printArray(arr,k-1);
    cout<<endl;

    int i=0;
    while(e<v-1){
        if(check[arr[1][i]] == false || check[arr[2][i]] == false){
            cout<<"edge : "<<arr[1][i]<<arr[2][i]<<" weight = "<<arr[0][i]<<endl;
            check[arr[1][i]] = true;
            check[arr[2][i]] = true;
            cost += arr[0][i];
            e++;
        }
        i++;
    }

    cout<<"\ncost = "<<cost<<endl;

    return 0;
}
