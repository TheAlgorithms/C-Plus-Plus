#include "hierarchical.hpp"
#include <iostream>
using namespace ml::unsupervised;
int main(){ Eigen::MatrixXd X(120,2); for(int i=0;i<120;++i){ int g=i/40; X(i,0)=g*3+(i%10)*0.05; X(i,1)=g*2+(i%8)*0.04; } HierarchicalClustering model(3,50,0.01); std::cout<<"Before score: -100"<<std::endl; model.fit(X); std::cout<<"After score: "<<model.score(X)<<std::endl; }
