#include<bits/stdc++.h>
using namespace std;

void aux(vector<vector<int>>& image, int sr, int sc, int newColor){
    int n=image.size();
    int m=image[0].size();
    int C=image[sr][sc];
    image[sr][sc]=newColor;
    if((sr-1>=0) && image[sr-1][sc]==C)
        aux(image,sr-1,sc,newColor);
    if((sc-1>=0) && image[sr][sc-1]==C)
        aux(image,sr,sc-1,newColor);
    if((sr+1<n) && image[sr+1][sc]==C)
        aux(image,sr+1,sc,newColor);
    if((sc+1<m) && image[sr][sc+1]==C)
        aux(image,sr,sc+1,newColor);
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    if(image[sr][sc]==newColor)
        return image;
    aux(image,sr,sc,newColor);
    return image;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>>image(n, vector<int>(m,0));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++)
			cin >> image[i][j];
	}
	int sr, sc, newColor;
	cin >> sr >> sc >> newColor;
	vector<vector<int>> ans = floodFill(image, sr, sc, newColor);
	for(auto i: ans){
		for(auto j: i)
			cout << j << " ";
		cout << "\n";
	}

	return 0;
}

/* Test Case 1:
Input-
3 3
1 1 1
1 1 0
1 0 1
1 1 2

Output-
2 2 2
2 2 0
2 0 1*/
