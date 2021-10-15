#include <iostream>
#include <map>
#include <cassert>

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
    assert(M.count("Paris"));

    //Find an entry in a map #2
    auto it=M.find("Paris");
    if(it!=M.end()) {
        assert("Paris"==it->first);
        assert(1==it->second);
    }

    //Remove from map
    M.erase("Paris");

    //Iterate over map
    for(std::pair<std::string,int> item : M) {
        std::cout<<item.first<<", "<<item.second<<std::endl;
    }

}
