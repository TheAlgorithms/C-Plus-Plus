#include <iostream>
#include<vector>
using namespace std;

int main(){
	
	
		int n;
		cin >> n;
		
		//take input for adjacency matrix
		vector<vector<int>>matrix(n, vector<int>(n, -1));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> matrix[i][j];
			}
		}
		
		//applying floyd warshall algorithm
		
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(matrix[i][k]==-1 || matrix[k][j]==-1)continue;
                    else if
                    (matrix[i][j]==-1)matrix[i][j]=matrix[i][k]+matrix[k][j];
                    else if(matrix[i][j]>matrix[i][k]+matrix[k][j]){
                        matrix[i][j]=matrix[i][k]+matrix[k][j];
                    }
                }
            }
        }
		
		//printing the resultant matrix
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << matrix[i][j] << " ";
			}
			cout <<endl;
		}
	
	return 0;
}  