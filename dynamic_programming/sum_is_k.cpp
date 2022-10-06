#include"bits/stdc++.h"

using namespace std;
vector<int> vi = {1, 2, 1};
int sum = 2;

void Print(vector<int > ans)
{
    cout<<"[";
    for(auto i :ans )
    {
        cout<<i<<" ";
    }
    cout<<"]"<<endl;
}

void solution(int i,vector<int> container,int cur_sum)
{
    if(i==vi.size())
    {
        if(cur_sum==sum)
        Print(container);
         return;
    }
    solution(i + 1, container, cur_sum);

    container.push_back(vi[i]);
    cur_sum+=vi[i];
    solution(i+1,container,cur_sum);
   
}

int main()
{
    
    vector<int> container;
    solution(0,container,0);

}