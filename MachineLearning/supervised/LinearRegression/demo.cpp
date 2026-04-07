#include "linear_regression.hpp"
#include <iostream>
#include <random>
using namespace ml::supervised;
int main(){ std::mt19937 g(1); std::normal_distribution<> n(0,0.1); Eigen::MatrixXd X(160,2); Eigen::VectorXd y(160); for(int i=0;i<160;++i){ double a=(i-80)/40.0,b=(i%20-10)/8.0; X(i,0)=a; X(i,1)=b; y(i)=3*a-2*b+1+n(g); } LinearRegression m(0.05,2000); std::cout<<"Before MSE: "<<(y.array().square().mean())<<std::endl;  m.fit(X,y); std::cout<<"After MSE: "<<m.score(X,y)<<std::endl; }
