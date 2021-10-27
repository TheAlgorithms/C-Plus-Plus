#include<bits/stdc++.h>
using namespace std;
int main(){
	char str1[]="state";
	char str2[]="tast";
	unordered_map<char,int>mp;
	int n1=sizeof(str1)/sizeof(str1[0]);
	int n2=sizeof(str2)/sizeof(str2[0]);
	if(n1!=n2){
		cout<<"Not anagram";
		return 0;
	}
	for(int i=0;i<n1;i++){
		mp[str1[i]]++;
	}
	for(int i=0;i<n2;i++){
		mp[str2[i]]--;
		if(mp[str2[i]] < 0){
			cout<<"Not anagram";
			return 0;
		}
	}
	cout<<"anagram";
	return 0;
}
