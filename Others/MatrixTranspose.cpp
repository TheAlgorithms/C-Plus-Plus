#include <vector>
#include <iostream>

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> target){
    
    int dimx = target.at(0).size();
    int dimy = target.size();

    std::vector<std::vector<int>> res(dimx, std::vector<int> (dimy));

    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            res.at(i).at(j) = target.at(j).at(i);
        }
    }

    return res;
}

void printMatrix(std::vector<std::vector<int>> target){
    for(int y = 0; y < target.at(0).size(); y++){
        for(int x = 0; x < target.size(); x++){
            std::cout << target.at(x).at(y) << ",";
        }
        std::cout << std::endl;
    }
}

int main(){
    
    std::vector<std::vector<int>> matrix{
        {1, 0, 0, 1},
        {0, 1, 0, 1},
        {0, 0, 1, 1}
    };

    std::vector<std::vector<int>> transposed = transpose(matrix);

    printMatrix(matrix);
    std::cout << "------" << std::endl;
    printMatrix(transposed);

    return 0;
}