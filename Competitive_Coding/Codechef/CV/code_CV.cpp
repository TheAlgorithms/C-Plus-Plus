#include<iostream>

using namespace std;

int main(void){
	int t,n,count = 0;
	string S,comp ="aeiou";
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>n>>S;
		for(int i =0;i<S.length();i++){
			for(int j=0;j<comp.length();j++){
				if(S[i] == comp[j]){
					for(int k = 0;k<comp.length();k++){
						if(S[i-1] == comp[k] || S[i-1] == NULL)
						goto jump;
					}
				count++;
				}
			}
			jump:;
		}
		cout<<count<<endl;
		count = 0;
		}
	}
