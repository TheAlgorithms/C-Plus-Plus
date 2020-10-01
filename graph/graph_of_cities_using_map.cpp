 
#include <iostream>
#include <map> 
#include <string>
#include <list>

using namespace std;
//Templates are used for Generic Graph->it can store any type of data like bool,int,string,etc.
template<typename T>
class Graph{
	//declaring map(key,values)
	map<T,list <T>> adjlist;
    public:
	//constructor
	Graph(){

	}
	void addedge(T u,T v,bool bidir=true){
		adjlist[u].push_back(v);
		if(bidir){
			adjlist[v].push_back(u);
		}
	}
	void printadjlist(){
		//iterating over map using for each loop
		for(auto row:adjlist) //auto automatically determines the datatype
		{
			T key = row.first;
			cout<<key<<"->";
			for(T element:row.second){
				cout<<element<<",";
			}
			cout<<endl;
		}
	}

};
int main(){
	Graph<string> g;
	//in o/p keys will be in sorted order
	g.addedge("Amritsar","Delhi");
	g.addedge("Amritsar","Jaipur");
	g.addedge("Delhi","Siachen");
	g.addedge("Delhi","Banglore");
	g.addedge("Delhi","Agra");
	g.addedge("Amritsar","Siachen");

	g.printadjlist();

	return 0;
}

/* OUTPUT

Agra->Delhi,
Amritsar->Delhi,Jaipur,Siachen,
Banglore->Delhi,
Delhi->Amritsar,Siachen,Banglore,Agra,
Jaipur->Amritsar,
Siachen->Delhi,Amritsar

*/
