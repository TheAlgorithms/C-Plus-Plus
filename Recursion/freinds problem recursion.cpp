/* Friends pair problem
Given N friends who want to go to a party. Each guy can go as a single , or as a couple.
Find the no. of ways in which N friends can go to the party.
N=3
ways=4    
solution:-
base cases:-
if N=0,return 1
if N=1,return 1
if N=2,return 2
recursive case:-
f(N)=f(N-1)+n-1C1f(N-2)
*/

#include<iostream>
using namespace std;
int ways(int N){
	//base case
	if(N==0){
		return 1;
		
	}
	if(N==1){
		return 1;
		
	}
	if(N==2){
		return 2;
	}
	//recursive case
	return ways(N-1)+((N-1)*ways(N-2));
	
}
int main(){
	int N;
	cin>>N;
	cout<<ways(N);
	return 0;
}
