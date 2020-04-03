#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<int> space(std::string line){
    std::stringstream s (line);
    std::vector<int> result;
    std::string num;
    while(std::getline(s, num, ' '))
        result.push_back(std::stoi(num));
    return result;
}


int main(){
    std::vector<std::vector<int>> v;
    std::ifstream nums;
    nums.open("numbers.txt"); // file name
    std::string row;
    while(std::getline(nums, row, '\n')){
        v.push_back(space(row));
    }
    int t = v.back().size() - 1;
    for(int a = t; a >= 1; a--){
        for(int b = 0; b <= a; b++){
            if(v[a][b] > v[a][b+1]){
                v[a-1][b] += v[a][b];
            }
            else{
                v[a-1][b] += v[a][b+1];
            }
        }
    }
    std::cout<<v[0][0]<<std::endl;
    return 0;
}
