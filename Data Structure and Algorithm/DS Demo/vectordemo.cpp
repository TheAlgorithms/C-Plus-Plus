#include<iostream>
#include<vector>
#include<iterator>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	vector<int> v;
	vector<int> v1;
	vector<int> ::iterator it;
	cout<<v.size();
	//it is an iterator
	//reffering vector
	int a[5]={1,2,3,4,5};
	v.assign(5,10);
	for(int i=0;i<5;i++)
	cout<<v[i]<<endl;
	
	v1.assign(a,a+3);
	cout<<"from array"<<endl;
	for(int i=0;i<v1.size();i++)
	cout<<v1[i]<<endl;
	cout<<v1[0];
	
	cout<<"using iterator"<<endl;
	for(it=v.begin();it<v.end();it++)
	cout<<*it<<endl;
	
	
	v1.push_back(200);//element is placed at the end
	v1.push_back(30);
	v1.push_back(25);
	cout<<"using iterator"<<endl;
	for(it=v1.begin();it<v1.end();it++)
	cout<<*it<<endl;
	
	
	
	cout<<"max of v1 is"<<*max_element(v1.begin(),
	v1.end())<<endl;
	cout<<"min of v1 is"<<*min_element(v1.begin(),
	v1.end())<<endl;
	
	sort(v1.begin(),v1.end(),greater<int>());
	
	cout<<"after sorting"<<endl;
	for(it=v1.begin();it<v1.end();it++)
	cout<<*it<<endl;
	
	
	it=find(v1.begin(),v1.end(),25);
	if(it!=v1.end())
	cout<<"found";
	else
	cout<<"not found";
	it=v1.begin();
	advance(it,2);
	v1.erase(it);
	
	cout<<"after delete";
	for(it=v1.begin();it<v1.end();it++)
	cout<<*it<<endl;
	
	v.clear();
	for(int i=0;i<v.size();i++)
	cout<<v[i];
	
}

