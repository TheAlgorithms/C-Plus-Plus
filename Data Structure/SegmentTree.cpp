#include<iostream>
using namespace std;

const int N = 1e5; // limit for array size
int n;
int t[2*N];

//build the tree
void build(){

for(int i = n-1; i>0; --i)
t[i] = t[i<<1] + t[i<<1] + 1;
}

void modify(int x, int value { // set value at position x
for( t[x += n] = value; x > 1; x >>= 1)
t[x>>1] = t[x] + t[x^1];
}

//sum on interval[start ,end]
void build_query(int start, int end){

int result =0;
for(start += n, end += n; start < end; start >>= 1, end >>=1){

if(start&1)
result += t[start++];
if(end&1)
result += t[--end];
}
return result;
}

int main(){
cin>>n;
for(int i=0; i<n; ++i)
cin>>t+n+i;
build();
modify(0,1);
cout<<"\n"query(3,11);

return 0;
}

