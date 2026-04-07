#include "neural_network.hpp"
#include <iostream>
using namespace ml::supervised;
int main(){ Eigen::MatrixXd X(160,2); Eigen::VectorXi y(160); for(int i=0;i<160;++i){ double a=(i-80)/40.0,b=(i%20-10)/8.0; X(i,0)=a; X(i,1)=b; y(i)=(a*a+b>0.5)?1:0; } NeuralNetwork model; std::cout<<"Before Acc: "<<(0.5)<<std::endl;  model.fit(X,y); std::cout<<"After Acc: "<<model.score(X,y)<<std::endl; }
