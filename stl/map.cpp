#include <iostream>
#include <map>

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
    std::map<std::string,int> M;

    //Insert in map
    M["Paris"]=1;
    M["New York"]=2;

    //Find an entry in a map #1
    if(M.count("Paris")) {
        std::cout<<"Paris present in map"<<std::endl;
    }

    //Find an entry in a map #2
    auto it=M.find("Paris");
    if(it!=M.end()) {
        std::cout<<"Paris present in map with value: "<<it->second<<std::endl;
    }

    //Remove from map
    M.erase("Paris");

    //Iterate over map
    for(std::pair<std::string,int> item : M) {
        std::cout<<item.first<<", "<<item.second<<std::endl;
    }

}
