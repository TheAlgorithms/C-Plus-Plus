#include<iostream>
using namespace std;

/*********************************
	@author Manas Uniyal
*********************************/

int st[(int)4e6];	//segment tree of size 4*10^6
int arr[(int)1e6];	//array which contains the input

//Builds the segment tree
void build(int node, int beg, int end){
	//Base condition
	if(beg==end){
		st[node]=arr[beg];
		return;
	}
	int mid = beg + (end-beg)/2;
	//Rcursively build the left part
	build(2*node+1, beg, mid);
	//Rcursively build the right part
	build(2*node+2, mid+1, end);
	st[node] = st[2*node+1] + st[2*node+2];
}

//Queries the segment tree
int query(int node, int beg, int end, int ql, int qr){
	if(end<ql || beg>qr || ql>qr){
		//When the segment does not contribute to the query
		return 0;
	} 
	if(beg>=ql && end<=qr){
		//Incase the segment completely lies inside the range
		return st[node];
	}
	int mid = beg + (end-beg)/2;
	//Calculate the result of the required left segment recursively
	int a = query(2*node+1, beg, mid, ql, qr);
	//Calculate the result of the required left segment recursively
	int b = query(2*node+2, mid+1, end, ql, qr);
	//Return the result
	return a+b;
}

//Updates the segment tree with the val at the position specified
void update(int node, int beg, int end, int val, int pos){
	if(beg == end){
		//Base condition, arises when the desired node is reached in the segment tree
		st[node] = val;
		arr[pos] = val;
		return;
	}
	int mid = beg + (end-beg)/2;
	if(pos<=mid)	//Element to be updated lies in the left half
		update(2*node+1, beg, mid, val, pos);
	else          //Element to be updated lies in the right half
		update(2*node+2, mid+1, end, val, pos);		
	st[node] = st[2*node+1] + st[2*node+2]; 
}

int main()
{
	//Initialsing the array
	int n = 5;
	arr[0]=1;
	arr[1]=3;
	arr[2]=4;
	arr[3]=10;
	arr[4]=11;
	build(0,0,n-1);                   //Build the segment tree
	cout<<query(0,0,n-1,0,2)<<"\n";   //Result = 8
	update(0,0,n-1,1,2);              //arr[2] now becomes 1 
	cout<<query(0,0,n-1,0,4)<<"\n";   //Result = 26
	return 0;
}
