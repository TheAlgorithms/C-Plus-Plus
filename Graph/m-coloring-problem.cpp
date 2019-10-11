#include<bits/stdc++.h>
using namespace std;
 
bool isSafe(int** arr, int v, int k, int* assigned, int n){
   for(int x = 0; x < n; x++){
        if(arr[v][x] == 1 && assigned[x] == k){
           return false;
        }
   }
   return true;
}   
bool mColoring(int** arr, int v, int* assigned, int n, int* colors, int m){
    if(v == n){
        return true;
    }
    for(int i = 0; i < m; i++){
        int col = colors[i];
        if(isSafe(arr, v, col, assigned, n)){
            assigned[i] = col;
            bool isPossibleToSolveFurther = mColoring(arr, v+1, assigned, n, colors, m);
            if(isPossibleToSolveFurther){
                return true;
            }
            assigned[i] = -1;
        }
    }
    return false;
}
 
int main()
 {
	//code
	int t;
	cin>>t;
	while(t--){
	    int n, m, e;
	    cin>>n>>m>>e;
	    int** arr = new int*[n];
	    for(int i = 0; i < n; i++){
	        arr[i] = new int[n];
	    }
	    int* assigned = new int[n];
	    for(int i = 0; i < n; i++){
	        assigned[i] = -1;
	    }
	    int* colors = new int[m];
	    for(int i = 0; i < m; i++){
	        colors[i] = i;
	    }
	    int a, b;
	    while(e--){
	        cin>>a>>b;
	        a--;
	        b--;
	        arr[a][b] = 1;
	        arr[b][a] = 1;
	    }
	    bool ans = mColoring(arr, 0, assigned, n, colors, m);
	    if(ans){
	        cout<<1<<endl;
	    }
	    else{
	        cout<<0<<endl;
	    }
	}
	return 0;
}
