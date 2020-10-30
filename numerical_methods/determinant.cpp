/**
*\file
*\breif[determinant of a square matrix using Gauss Elimination](https://en.wikipedia.org/wiki/Gaussian_elimination)
*\author [mmzafar]
*/

#include <iostream>
#include<cassert>
#include<array>

/**
*function to get row with non zero ith element
*/
int get_row(std::array<std::array<float,2>,2> &A,int i)
{
	int n=A.size();
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
void swap_row(std::array<std::array<float,2>,2> &A,int i,int j)
{
	int n=A.size();
	float temp=0;
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
void substract_row(std::array<std::array<float,2>,2> &A,int i,int j,float key)
{
	int n=A.size();
	for(int k=0;k<n;k++){
		A[j][k]-=key*A[i][k];
	}
}
/**
*function to compute determinant
*/
float determinant(std::array<std::array<float,2>,2> &A)
{
	int n=A.size();
	float det=1,key=0;
	for(int i=0;i<n;i++){
		int j=get_row(A,i);
		if(j==-1){
		   //if rank(A)<n, then determinant is zero
		   return 0;
		}
		if(j!=i){
		   swap_row(A,i,j);
		   det*=-1;
		}
		for(j=i+1;j<n;j++){
			key=A[j][i]/A[i][i];
			substract_row(A,i,j,key);
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
static void test()
{
	std::cout<<"testing…";
	int n=2;
	std::array<std::array<float,2>,2> A={{{0,4},{5,1}}};
	assert(determinant(A)==-20);
	std::cout<<"passed"<<std::endl;
}
/**
*main function
*/
int main() 
{
	//perform self test
	test();
	return 0;
}

