/**
*\file
*\breif[determinant of a square matrix using Gauss Elimination](https://en.wikipedia.org/wiki/Gaussian_elimination)
*\author [mmzafar]
*/

#include <iostream>
#include<cassert>
using namespace std;
#define N 5

/**
*function to print and take entries of matrix
*/
void get_matrix(float A[][N],int *n){
	cout<<"Enter the order of matrix A:\n";
	cin>>*n;
	cout<<"Enter the entries of matrix A:\n";
	for(int i=0;i<*n;i++){
		cout<<"Row "<<i+1<<endl;
		for(int j=0;j<*n;j++)
			cin>>A[i][j];
	}
	cout<<"\nMatrix A:\n";
	for(int i=0;i<*n;i++){
		for(int j=0;j<*n;j++)
			cout<<A[i][j]<<"\t";
		cout<<endl;
	}
}
/**
*function to get row with non zero ith element
*/
int get_row(float A[][N],int n,int i){
	for(int j=i;j<n;j++){
		if(A[j][i]!=0){
			return j;
		}
	}
	return -1;
}
/**
*function to interchange the rows
*/
void swap_row(float A[][N],int n,int i,int j){
	float temp;
	for(int k=0;k<n;k++){
		temp=A[i][k];
		A[i][k]=A[j][k];
		A[j][k]=temp;
	}
}
/**
*function to operate on rows
*jth row is substracted by key*ith row
*/
void substract_row(float A[][N],int n,int i,int j,float key){
	for(int k=0;k<n;k++){
		A[j][k]-=key*A[i][k];
	}
}
/**
*function to compute determinant
*/
float determinant(float A[][N],int n){
	float det=1,key;
	for(int i=0;i<n;i++){
		int j=get_row(A,n,i);
		if(j==-1){
		   //if rank(A)<n, then determinant is zero
		   return 0;
		}
		if(j!=i){
		   swap_row(A,n,i,j);
		   det*=-1;
		}
		for(j=i+1;j<n;j++){
			key=A[j][i]/A[i][i];
			substract_row(A,n,i,j,key);
		}
	}
	for(int i=0;i<n;i++){
		det*=A[i][i];
	}
	return det;
}
/**
*test implementation
*/
void test(){
   cout<<"testing…";
   int n=2;
	float A[N][N]={{0,4},{5,1}};
	assert(determinant(A,n)==-20);
	cout<<"passed"<<endl;
}
/**
*main function
*/
int main() {
	//perform self test
	test();
	int n;
	float A[N][N]={};
	get_matrix(A,&n);
	cout<<"Determinant of A is \t"<<determinant(A,n);
	return 0;
}

