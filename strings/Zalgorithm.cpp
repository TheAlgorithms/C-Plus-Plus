#include<bits/stdc++.h>
using namespace std;
void buildZ(int *z,string str){

int l=0;
int r=0;
int n = str.size();
for(int i=1; i<n; i++){

if(i>r){

//not found pattern yet trying to find it
	
l=i;
r=i;

while(r<n && str[r-l]==str[r]){
r++;
}

z[i] = r-l;
r--;
}else{
int k = i-l;
if(z[k]<=r-i){
	z[i] = z[k];
}else{

 l=i;
 while(r<n && str[r-l]==str[r]){
 	r++;
 }

 z[i] = r-l;
 r--;
}

}

}


}


void searchstring(string text,string pattern){

//abc$aaabc
//012345678
		string str = pattern+"$"+text;
		int n = str.length();
		int *z = new int[n]();
		buildZ(z,str);
		for(int i=1; i<n; i++){
			if(z[i] == pattern.length()){
				cout<<i-pattern.length()-1<<endl;
			}
		}

		

}



int main(){

/// below is the sample string and pattern
	string text = "abxabcabcaby";
	string pattern = "abcaby";

	searchstring(text,pattern);




}