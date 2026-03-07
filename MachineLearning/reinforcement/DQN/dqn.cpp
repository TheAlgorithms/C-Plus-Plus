#include "dqn.hpp"
#include <fstream>
#include <random>
namespace ml::reinforcement {
DQN::DQN(int s,int a,double al,double g,double e):states_(s),actions_(a),alpha_(al),gamma_(g),epsilon_(e),Q_(Eigen::MatrixXd::Zero(s,a)){}
/**
 * DQN-style one-step target:
 * $y=r+\gamma\max_{a'}Q_\theta(s',a')$ and minimize squared TD error.
 */
void DQN::fit(const Eigen::MatrixXd& tr, const Eigen::VectorXi& r){
    std::mt19937 gen(7); std::uniform_real_distribution<> u(0,1); std::uniform_int_distribution<> ai(0,actions_-1);
    for(int i=0;i<tr.rows();++i){ int s=(int)tr(i,0), s2=(int)tr(i,1); int a=u(gen)<epsilon_?ai(gen):(int)(Eigen::Index)Q_.row(s).maxCoeff(); int target=r(i)+gamma_*Q_.row(s2).maxCoeff(); Q_(s,a)+=alpha_*(target-Q_(s,a)); }
}
/** Greedy policy extraction from Q-network approximation. */
Eigen::VectorXi DQN::predict(const Eigen::MatrixXd& states) const{ Eigen::VectorXi a(states.rows()); for(int i=0;i<states.rows();++i){ int s=(int)states(i,0); Eigen::Index idx; Q_.row(s).maxCoeff(&idx); a(i)=idx; } return a; }
/** Mean action-value proxy. */
double DQN::score(const Eigen::MatrixXd& states,const Eigen::VectorXi&) const{ auto a=predict(states); double s=0; for(int i=0;i<a.size();++i) s+=Q_((int)states(i,0),a(i)); return s/a.size(); }
/** Save Q-table and hyperparameters. */
void DQN::save(const std::string& f) const{ std::ofstream o(f); o<<states_<<" "<<actions_<<" "<<alpha_<<" "<<gamma_<<" "<<epsilon_<<"\n"; for(int i=0;i<states_;++i){for(int j=0;j<actions_;++j)o<<Q_(i,j)<<" "; o<<"\n";} }
/** Load Q-table and hyperparameters. */
void DQN::load(const std::string& f){ std::ifstream i(f); i>>states_>>actions_>>alpha_>>gamma_>>epsilon_; Q_.resize(states_,actions_); for(int r=0;r<states_;++r)for(int c=0;c<actions_;++c)i>>Q_(r,c); }
}
