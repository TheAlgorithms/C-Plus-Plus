#include<stdio.h>
#include<stdlib.h>
int visited[10][10],a[10][10];
int floodfill(int x, int y, int dest_x, int dest_y,int n,int m){
	if(visited[x][y]==1 || a[x][y]==0){
		printf("1\t");
		return 0;
	}
	if(x>n || y>m){
		printf("8\t");
		return 0;
	}
	if(x<=0 || y<=0){
		printf("9\t");
		return 0;
	}
	 
	if(x==dest_x && y==dest_y){
		printf("2\t");
		return 1;
	}
	visited[x][y]=1;
	if(floodfill(x+1,y,dest_x,dest_y,n,m)==1){
		printf("3\t");
		return 1;
	}
	if(floodfill(x,y+1,dest_x,dest_y,n,m)==1){
		printf("4\t");
		return 1;
	}
	if(floodfill(x-1,y,dest_x,dest_y,n,m)==1){
		printf("5\t");
		return 1;
	}
	if(floodfill(x,y-1,dest_x,dest_y,n,m)==1){
		printf("6\t");
		return 1;
	}
	printf("7\t");
	return 0;
	//if(x<0 || y<0) return 0;
}
int main(){
	int n,m;
	//printf("Enter m and n: ");
	scanf("%d%d",&n,&m);
	//printf("Enter matrix: \n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
			visited[i][j]=0;
		}
	}
	if(floodfill(1,1,n,m,n,m)==1){
		printf("yes");
	}
	else{
		printf("no");
	}
}
