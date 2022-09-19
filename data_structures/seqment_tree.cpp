#include<bits/stdc++.h>
using namespace std;

/*
SEGEMENT TREE
->given a array of elements find the minimum in 
the given range/update the val
*/

int build(int i,int low,int high, int a[],int seq[]){
    if(low==high){
        seq[i]=a[low];
        return seq[i];
    }
    int mid=(low+high)/2;
    int left=build(2*i+1,low,mid,a,seq);
    int right=build(2*i+2,mid+1,high,a,seq);
    return seq[i]=min(left,right);
}

int query(int i,int low,int high,int l, int r, int seq[]){
    if(r<low || l>high) return INT_MAX;
    if(low>=l && r<=high) return seq[i];

    int mid=(low+high)/2;
    int left=query(2*i+1,low,mid,l,r,seq);
    int right=query(2*i+2,mid+1,high,l,r,seq);

    return min(left,right);
}

void update(int i,int low, int high, int ind,int val,int seq[]){
    if(low==high){
        seq[i]=val;
        return ;
    }
    int mid=(low+high)/2;
    if(ind<=mid) update(2*i+1,low,mid,ind,val,seq);
    else update(2*i+2,mid+1,high,ind,val,seq);

    seq[ind]=min(seq[2*i+1], seq[2*i+2]);
}

int main(){

    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++) cin>>a[i];
    int seq[n*4];
    build(0,0,n-1,a,seq);

    return 0;
}
