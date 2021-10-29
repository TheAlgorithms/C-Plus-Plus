#include<stdio.h>
#include<stdlib.h>
//using namespace std;
int a[100][100], q[100],v,n,visited[100],f=0,r=-1,level[100],x,y,z;
void bfs(int v){
	for(int i=1;i<=n;i++){
		if(a[v][i] && !visited[i]){
			q[++r]=i;
		}
		if(a[v][i] && !visited[i] && !level[i]){
			level[i]=level[v]+1;
			//printf("%d\t",v);
			//printf("%d\t",i);
			//printf("%d\n",level[i]);
		}
	}
	if(f<=r){
		visited[q[f]]=1;
		bfs(q[f++]);
	}
}
int main(){
	printf("enter no of vertices: ");
	scanf("%d",&n);
	printf("enter adjacency matrix: \n");
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[x][y]=0;
		}
		visited[i]=0;
		q[i]=0;
		level[i]=0;
	}
	for(int i=1;i<n;i++){
		scanf("%d",&x);
		scanf("%d",&y);
		a[x][y]=1;
		a[y][x]=1;
	}
	v=1;
	level[v]=1;
	bfs(v);
	level[v]=1;
	printf("\n");
	printf("Enter x: ");
	scanf("%d",&z);
	int count=0;
	for(int i=1;i<=n;i++){
		if(level[i]==z && visited[i]){
			//printf("%d\t",i);
			//printf("%d\n",level[i]);
			count++;
		}
	}
	printf("%d\n",count);
}
