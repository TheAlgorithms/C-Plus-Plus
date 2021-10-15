/**
 * @file
 * @brief This code is a basic implementation for use of map STL in C++.
 * @details
 * The below code includes:
 * (a) Insertion in a map
 * (b) Finding an entry in a map
 * (c) Removing elements from a map
 * (d) Iterating over a map
 * @author abhishek vanjani(https://github.com/KillerAV)
 */

#include <iostream> /// For input output
#include <map> /// For usage of map
#include <cassert> /// For asserts

int main() 
{
    std::map<std::string,int> M;

    // Insert in map
    M["Paris"]=1;
    M["New York"]=2;

    // Find an entry in a map #1
    assert(M.count("Paris"));

    // Find an entry in a map #2
    auto it=M.find("Paris");
    if(it!=M.end()) {
        assert("Paris"==it->first);
        assert(1==it->second);
    }

    // Remove from map
    M.erase("Paris");

    // Iterate over map
    for(std::pair<std::string,int> item : M) {
        std::cout<<item.first<<", "<<item.second<<std::endl;
    }

}
