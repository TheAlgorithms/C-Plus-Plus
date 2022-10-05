#include <bits/stdc++.h>
using namespace std;
bool custom_sorting(const pair<int,int> &a,const pair<int,int> &b)
{
    return a.second<b.second;

}
int main()
{
vector<pair<int,int>> job={{0,3},{1,3},{0,5},{3,6},{4,7},{3,9},{5,10},{8,10}};

sort(job.begin(),job.end(),custom_sorting);
for(int i=0;i<job.size();i++)
{
    cout<<job[i].first<<" "<<job[i].second<<endl;
    
}
vector<pair<int,int>> optimal;
int finish=0;
for(auto &val:job)
{
    if(finish<=val.first)
    {
        finish=val.second;
        optimal.push_back({val.first,val.second});

    }
}
cout<<"The optimal non overlapping jobs are \n";
for(auto &val:optimal)
{
    cout<<val.first<<" "<<val.second<<endl;

}
vector<vector<int>> conflicts;
for(int i=0;i<job.size();i++)
{
    int count=0;
    int start=job[i].first;
    int finish=job[i].second;
    for(int j=0;j<job.size();j++)
    {
        if(i!=j && job[i].first<job[j].second && job[j].first<job[i].second)
        count++;

    }
    conflicts.push_back({job[i].first,job[i].second,count});

}
cout<<"Conflicting type for each job :"<<endl;
for(auto &val:conflicts)
{
    cout<<"("<<val[0]<<", "<<val[1]<<")"<<"--->"<<val[2]<<endl;

}
int min=INT_MAX , max=INT_MIN;
for(auto &val:conflicts)
{
    if(val[2]>max)
    max=val[2];
    if(val[2]<min)
    min=val[2];
}
cout<<"The jobs with minimum conflicts : "<<endl;
for(auto &val:conflicts)
{
    if(val[2]==min)
    cout<<"("<<val[0]<<","<<val[1]<<")"<<endl;

}
cout<<"The jobs with maximum conflicts : "<<endl;
for(auto &val:conflicts)
{
    if(val[2]==max)
    cout<<"("<<val[0]<<","<<val[1]<<")"<<endl;

}

}
