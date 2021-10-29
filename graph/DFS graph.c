#include<stdio.h>
#include<stdlib.h>
int a[100][100], visited[100], n;
void DFS(int v){
	visited[v]=1;
	//printf("%d\t",v);
	for(int i=1;i<=n;i++){
		if(a[v][i] && !visited[i]){
		DFS(i);
		}
	}	
}
int main(){
	int m,x,y;
	//printf("enter n: ");
	scanf("%d",&n);
	//printf("enter m: ");
	scanf("%d",&m);
	printf("%d\n",m);
	//printf("enter adjacency matrix: \n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=0;
		}
		visited[i]=0;
		//q[i]=0;
		//level[i]=0;
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		scanf("%d",&y);
		
		a[x][y]=1;
		a[y][x]=1;
	}
	int v;
	//printf("Enter v");
	scanf("%d",&v);
	//printf("vertices traversed are: \n");
	DFS(v);
	int ans=0;
	for(int i=1;i<=n;i++){
		if(!visited[i]){
			//printf("%d",i);
			ans++;
		}
	}
	//printf("answer is: ");
	printf("%d",ans);
}

