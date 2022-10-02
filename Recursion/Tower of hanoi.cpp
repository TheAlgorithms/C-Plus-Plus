#include<iostream>
using namespace std;

void move(int n,char src,char helper,char destination){
	//base case
	if(n==0){
		return;
	}
	//recursive case
	//move n-1 disks from source to helper
	move(n-1,src,destination,helper);
	cout<<"shift disk "<<n<<" from "<<src<<"to "<<destination<<endl;
	move(n-1,helper,src,destination);
	
}

int main(){
	int n;
	cin>>n;
	
	move(n,'A','B','C');
	
}
