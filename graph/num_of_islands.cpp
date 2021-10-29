
#include<iostream>
#include<vector>
using namespace std;


int X[] = {-1 , 0 , 0 , 1};
int Y[] = {0 , -1 , 1 , 0};



void dfs(int graph[][50] , int n , bool visited[][50] , int i , int j){
    
    visited[i][j] = true;
    
    for(int k=0 ; k<4 ; k++){
        int x = i + X[k];
        int y = j + Y[k];
        if(x>=0 && y>=0 && x<n && y<n &&!visited[x][y] && graph[x][y]!=0){
            dfs(graph , n , visited , x , y);
        }
    }

}


int main(){
    // n = num of nodes
    // m = num of edges
    

    // grid

    int n;
    cin>>n;
    int graph[50][50]{0};
    
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            cin>>graph[i][j];
        }
    }   

    bool visited[50][50]{0};
    int num_of_cc = 0;
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            if(!visited[i][j] && graph[i][j]!=0){
                dfs(graph , n , visited , i , j);
                num_of_cc++;
            }
        }
    }
 
    cout<<num_of_cc<<endl;


}


// 4
// 1 0 1 0
// 1 1 0 1
// 0 1 0 1
// 1 0 1 1



