#include<bits/stdc++.h>
using namespace std;

int* getlps(string pattern){
	int len = pattern.length();
	int *lps = new int[len];


	lps[0] = 0;
	int i=1;
	int j=0;
	while(i<len){

		if(pattern[i]==pattern[j]){
			lps[i] = j+1;
			j++;
			i++;
		}else{
			if(j!=0){
			j = lps[j-1];
			}else{
				lps[i] = 0;
				i++;

			}

		}
	}

return lps;

}
bool kmp(string text,string pattern){
	int lentext = text.length();
	int lenpattern = pattern.length();

	int i=0;
	int j=0;

	int *lps = getlps(pattern);
	while(i<lentext && j<lenpattern){
		if(text[i]==pattern[j]){
			i++;
			j++;
		}else{
			if(j!=0){
		j = lps[j-1];
			}else{
				i++;
			}
		}
	}

	if(j==lenpattern){
		return true;
	}else{
		return false;
	}

}


int main(){


string a="abcde";
string b="";

if(kmp(a,b)){
	cout<<"YES"<<endl;
}else{
	cout<<"NO"<<endl;
}


}