#include <iostream>
#include <map>
using namespace std;

/**
 * The following code makes use of Map STL.
 * Following features of map are depicted in the below code:
 * (a) Insertion in a map
 * (b) Finding an entry in a map
 * (c) Removing elements from a map
 * (d) Iterating over a map
 */
int main() 
{
    map<string,int> M;

    //Insert in map
    M["Paris"]=1;
    M["New York"]=2;

    //Find an entry in a map #1
    if(M.count("Paris")) {
        cout<<"Paris present in map"<<endl;
    }

    //Find an entry in a map #2
    auto it=M.find("Paris");
    if(it!=M.end()) {
        cout<<"Paris present in map with value: "<<it->second<<endl;
    }

    //Remove from map
    M.erase("Paris");

    //Iterate over map
    for(auto it=M.begin();it!=M.end();it++) {
        cout<<it->first<<", "<<it->second<<endl;
    }

}
