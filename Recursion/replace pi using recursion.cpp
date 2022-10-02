#include<iostream>
using namespace std;
//replace pi with 3.14
//xpighpimpipi----->x3.14m3.143.14
void replace_pi(char a[],int i){
	if(a[i]=='\0' or a[i+1]=='\0'){
		return ;
		
	}
	//look for pi at current location
	if(a[i]=='p' and a[i+1]=='i'){
		//shifting +replacement with 3.14
		int j=i+2;
		//jake j to the end of the array
		while(a[j]!='\0'){
			j++;
		}
		//shifting(right to left)
		while(j>=i+2){
			a[j+2]==a[j];
			j--;
			
		}
		//replacement + recursive call for the remaining part
		a[i]='3';
		a[i+1]='.';
		a[i+2]='1';
		a[i+3]='4';
		replace_pi(a,i+4);
		
		
		
		
	}
	else{
		//go to the next position
		replace_pi(a,i+1);
		
	}
	return ;
	
}
int main(){
	char a[1000];
	cin>>a;
	replace_pi(a,0);
	cout<<a<<endl;
}
