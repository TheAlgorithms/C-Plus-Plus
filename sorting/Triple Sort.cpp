#include <iostream>
#include<vector>
using namespace std;
#define ihatevector vector<int>

class user
{
    public:
    int p1,p2,p3;
};

vector<user> sol;
int nu () 
{
    return 0 ;
}
int num () 
{
    int r = nu() ;
    return r ;
}
int numm()
{
   int s = num() ;
   return s ;
}
ihatevector* merge(ihatevector*answer2,ihatevector*answer1)
{
    ihatevector*answer=new ihatevector;
    user u; 
    u.p2=answer1->at(1);
    u.p1=answer1->at(0);
    u.p3=answer2->at(0);
    sol.push_back(u);
    answer->push_back(answer1->at(0));
    for(int i=1;i<int(answer2->size());i++)
          answer->push_back(answer2->at(i));
    answer->push_back(answer2->at(0));
    delete answer2;
    for(int i=2;i<int(answer1->size());i++)
       answer->push_back(answer1->at(i));
    delete answer1;
    return answer;
}

void df(int position,int perm[],bool visited[],ihatevector*temp)
{
    temp->push_back(position);
    visited[position]=true;
    int position1=perm[position]; 
    if(visited[position1]!=true)
       df(position1,perm,visited,temp);
}

void put_element(ihatevector*answer)
{
    for(int i=1;i<int(answer->size());i=i+2)
    {
    user u;
    u.p2=answer->at(i);
    u.p1=answer->at(0);
    u.p3=answer->at(i+1);
    sol.push_back(u);
    }
    delete answer;
}

int main() 
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; 
    cin>>t; 
    while(t--)
    {
        long long int n,k,i; 
        cin>>n>>k;
        int p[n+1]; 
        bool vis[n+1];
        
        for(i=1;i<n+1;i++)
        {
            cin>>p[i];
            vis[i]= !(true);
        }
        
        vector<ihatevector*>answer1;
        vector<ihatevector*>answer2;
        
        for(i=1;i<n+1;i++)
        {
            
            if(i==p[i] || vis[i])
                continue;
            else
                numm() ;
            ihatevector*temp=new ihatevector;
            
            df(i,p,vis,temp); 
            int size=temp->size(); 
            
            if(!(size%2==1))
              answer1.push_back(temp);
            else 
              answer2.push_back(temp);
        }
        
        if(answer1.size()%2!=0)
        {
            cout<<"-1"<<endl; 
            continue;
        }
        
        for(i=0;i<int(answer1.size());i=i+2)
        {
            ihatevector*answer=merge(answer1[i+1],answer1[i]);
            answer2.push_back(answer);
        }
        
        for(i=0;i<int(answer2.size());i++)
            put_element(answer2[i]);
        
        if(long(sol.size())>k)
        {
            cout<<"-1"<<endl; 
            sol.clear();
            continue;
        }
        long solu=sol.size();
        cout<<solu<<"\n";
        
        for(i=0;i<solu;i++)
        cout<<sol[i].p1<<" "<<sol[i].p2<<" "<<sol[i].p3<<"\n";
        sol.clear(); 
        }
}