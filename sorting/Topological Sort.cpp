#include<iostream>
 
using namespace std;
 
int main(){
	int i,j,k,n,a[10][10],x[10],y[10],count=0;
 
	cout<<"no of vertices:\n";
	cin>>n;
 
	cout<<"adjacency matrix:\n";
	for(i=0;i<n;i++){
		cout<<"Enter row "<<i+1<<"\n";
		for(j=0;j<n;j++)
			cin>>a[i][j];
	}
 
	for(i=0;i<n;i++){
        x[i]=0;
        y[i]=0;
    }
 
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            x[i]=x[i]+a[j][i];
 
    cout<<"\nThe topological order is:";
 
    while(count<n){
        for(k=0;k<n;k++){
            if((x[k]==0) && (y[k]==0)){
                cout<<k+1<<" ";
                y[k]=1;
            }
 
            for(i=0;i<n;i++){
                if(a[i][k]==1)
                    x[k]--;
            }
        }
 
        count++;
    }
 
    return 0;
}
