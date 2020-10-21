#include<iostream>
#include<deque>
using namespace std;
int main()
{
	deque<int> d;
	d.assign(6,75);
	deque<int> ::iterator it;
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	
	it=d.begin();
	advance(it,2);
	d.insert(it,2,45);
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	
	cout<<"push back";
	d.push_back(30);
	d.push_back(90);
	d.push_back(70);
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	
	cout<<"push front";
	//similarly we have pop_back and pop_front
	d.push_front(60);
	d.push_front(80);
	d.push_front(50);
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	
	
	d.pop_back();
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	
	d.pop_front();
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;
	/*advance(it,2);
	d.erase(it);
	cout<<"elements are"<<endl;
	for(it=d.begin();it!=d.end();it++)
	cout<<*it<<endl;*/
	
	cout<<"size of deque is "<<d.size();
	
}


