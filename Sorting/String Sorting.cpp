#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

bool comp(pair<string,int> f1,pair<string,int> f2){
	return f1.second < f2.second ;
}

int main(){

	int n;
	cin>>n;

	string name;
	int price;

	vector<pair<string,int> > fruits;

	for(int i=0;i<n;i++){
		cin>>name;
		getline(cin,name);
		fruits.push_back(make_pair(name,price));
	}

	sort(fruits.begin(),fruits.end(),comp);

	for(int i=0;i<n;i++){
		cout<<fruits[i].first<<" , "<<fruits[i].second;
	}
}