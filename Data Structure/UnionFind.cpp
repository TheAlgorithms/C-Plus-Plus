#include <iostream>
#include <string>
using namespace std;


class UNION_FIND {
private:
    int *parent, *height;
public:
    explicit UNION_FIND(int size) {
        this->parent = new int[size];
        this->height = new int[size]();
        for (int i = 0; i < size; i++)
            this->parent[i] = i;
    }
    int find(int agent){
        if(this->parent[agent] == agent)
            return agent;
        this->parent[agent] = this->find(parent[agent]);
        return  this->parent[agent];
    }
    void join(int agent1, int agent2){
        if(this->parent[agent1] == this->parent[agent2])
            return;
        int agent1_pos = find(agent1), agent2_pos = find(agent2);

        if(this->height[agent1_pos] < this->height[agent2_pos] )
            this->parent[agent1_pos] = agent2_pos;
        else{
            this->parent[agent2_pos] = agent1_pos;
            if(this->height[agent1_pos] == this->height[agent2_pos])
                this->height[agent1]++;
        }
    }
    bool is_joined(int agent1, int agent2){
        return find(agent1) == find(agent2);
    }

};




int main(){
    //cout<<"IT WORKS"<<endl;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    UNION_FIND union_find(100);

    union_find.join(10,30);
	union_find.join(10,50);
	cout<<union_find.is_joined(10,50);
}
