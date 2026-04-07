#pragma once
#include "eigen_compat.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace ml::utils {
inline Eigen::MatrixXd load_csv(const std::string& path, char delimiter=',') {
    std::ifstream file(path);
    std::string line;
    std::vector<std::vector<double>> rows;
    while(std::getline(file,line)){
        if(line.empty()) continue;
        std::stringstream ss(line); std::string cell; std::vector<double> row;
        while(std::getline(ss,cell,delimiter)) row.push_back(std::stod(cell));
        rows.push_back(row);
    }
    if(rows.empty()) return Eigen::MatrixXd();
    Eigen::MatrixXd X(rows.size(), rows[0].size());
    for(size_t i=0;i<rows.size();++i) for(size_t j=0;j<rows[i].size();++j) X(i,j)=rows[i][j];
    return X;
}
}
