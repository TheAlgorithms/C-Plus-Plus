#include "logistic_regression.hpp"
#include <iostream>
using namespace ml::supervised;
int main(){ Eigen::MatrixXd X(160,2); Eigen::VectorXi y(160); for(int i=0;i<160;++i){ double a=(i-80)/40.0,b=(i%20-10)/8.0; X(i,0)=a; X(i,1)=b; y(i)=(a+b>0)?1:0; } LogisticRegression m; std::cout<<"Before Acc: "<<(0.5)<<std::endl;  m.fit(X,y); std::cout<<"After Acc: "<<m.score(X,y)<<std::endl; }
