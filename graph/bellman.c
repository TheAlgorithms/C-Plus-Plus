#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int a[5][5],dist[5],n;
void Bellman(int v){
	dist[1]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dist[j]>dist[i]+a[i][j] && i!=j && a[i][j]!=0){
				dist[j]=dist[i]+a[i][j];
				//printf("path: ");
				//printf("%d\n",i);
			}
		}
	}
}
int main(){
	int x,y,w,p,m;
	int root=1;
	//printf("enter no of vertices and edges: ");
	scanf("%d%d",&n,&m);
	//printf("enter m: ");
	//scanf("%d",&m);
	//printf("enter adjacency matrix: \n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=0;
		}
		dist[i]=INT_MAX;
		//q[i]=0;
		//level[i]=0;
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		scanf("%d",&y);
		scanf("%d",&w);
		a[x][y]=w;
		a[y][x]=w;
	}
	//printf("enter src: ");
	//scanf("%d",&v);
	dist[root]=0;
	Bellman(root);
	//printf("%d\n");
	for(int i=2;i<=n;i++){
		printf("%d ",dist[i]);
	}
}
