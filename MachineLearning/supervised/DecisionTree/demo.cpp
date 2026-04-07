#include "decision_tree.hpp"
#include <iostream>
using namespace ml::supervised;
int main(){ Eigen::MatrixXd X(160,2); Eigen::VectorXd y(160); for(int i=0;i<160;++i){ double a=(i-80)/40.0,b=(i%20-10)/8.0; X(i,0)=a; X(i,1)=b; y(i)=2*a-0.5*b+1; } DecisionTree model; std::cout<<"Before MSE: "<<(y.array().square().mean())<<std::endl;  model.fit(X,y); std::cout<<"After MSE: "<<model.score(X,y)<<std::endl; }
