#include<stdio.h>
#include<stdlib.h>
void blockcells(int rect[][], int X, int Y, int N, int R, int A[], int B[]){
	for(int i=0;i<X;i++){
		for(int j=0;j<Y;j++){
			for(int p=0;p<N;p++){
				if((pow(A[p]-i-1),2) + (pow(B[p]-j-1),2) <= pow(R,2)){
					rect[i][j]=-1;
				}
			}
		}
	}
}
void bfs(int v){
	for(int i=0;i<n;i++){
		if(rect[v][i] && !visited[i]){
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
	
    int i,j,X,Y,N,R;
    scanf("%d",&X);
    scanf("%d",&Y);
    scanf("%d",&N);
    scanf("%d",&R);
    int rect[X][Y]={0};
    int A[N],B[N];
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for(i=0;i<N;i++){
        scanf("%d",&B[i]);
    }
    
    
    
    
    
    if(solve(A,B,R,N,x,y)==1){
        printf("YES");
    }
    else{
        printf("NO");
    }
}
