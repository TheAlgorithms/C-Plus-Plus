#include "q_learning.hpp"
#include <iostream>
using namespace ml::reinforcement;
int main(){ Eigen::MatrixXd tr(64,2); Eigen::VectorXi rw(64); for(int s=0;s<16;++s)for(int a=0;a<4;++a){ int i=s*4+a; int s2=(s+a+1)%16; tr(i,0)=s; tr(i,1)=s2; rw(i)=(s2==15)?10:-1; } QLearning agent; std::cout<<"Before value: 0"<<std::endl; for(int ep=0;ep<50;++ep) agent.fit(tr,rw); Eigen::MatrixXd st(16,1); for(int i=0;i<16;++i) st(i,0)=i; std::cout<<"After value: "<<agent.score(st,rw.head(16))<<std::endl; }
