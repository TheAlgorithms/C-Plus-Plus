#include<iostream>
using namespace std;

//computes and print totient of all numbers

void compute(int n){

// create an array to store fun values
long long fun[n+1];
for(int i=1; i<n; i++){
fun[i] = i; //initialize for product

for(int k=2; k<=n; k++){
// check if fun[k] not computed earlier then number k is prime
if(value[k]==k){

//fun of a prime number k is always equal to k-1
fun[k] = k-1;

//update fun value for all multiple of k
for(int i=2*k; i<=n; i+=k)
{
fun[i] = (fun[i]/k) * k-1;
}

}
}
//print pre-computed fun values
for(int i=1; i<=n; i++){
cout<<fun[i]<<endl;
}

int main(){

int n;
cin>>n;

compute(n);
return 0;
}
