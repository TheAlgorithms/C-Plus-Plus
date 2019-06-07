//Astar example(8 puzzle )
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;

#define DEG 3	//Number of rows and columns

const bool SUCCESS=true;

class state {

public:
	int board[DEG][DEG];
	int g,f;

	state *came_from;

	state() {
		g=0;
		f=0;
		came_from = NULL;
	}
	
	static int heuristic(state from,state to) {
		int i,j,dist=0;
		for(i=0;i<DEG;i++)
			for(j=0;j<DEG;j++)
				if(from.board[i][j] != to.board[i][j])
					dist++;
		return dist;
	}

	bool operator ==(state a) {
		for(int i=0;i<DEG;i++)
			for(int j=0;j<DEG;j++)
				if(this->board[i][j] != a.board[i][j])
					return false;
		return true;
	}

	void print() {
		for(int i=0;i<DEG;i++) {
			for(int j=0;j<DEG;j++)
				cout<<board[i][j]<<" ";
			cout<<endl;
		}
		printf("g: %d\n",g);
		printf("f: %d\n\n",f);
	}
};

vector<state> output;

bool lowerF(state a,state b) {
	return a.f < b.f;
}

void swap(state &a,int i,int j,int posi,int posj) {
	int temp;
	temp = a.board[i][j];
	a.board[i][j] = a.board[posi][posj];
	a.board[posi][posj] = temp;
}

bool isInSet(state a,vector<state> b) {
	for(int i=0;i<b.size();i++)
		if(a == b[i])
			return true;

	return false;
}

void addNeighbor(state current,state goal, int newI, int newJ, int posi, int posj,
					vector<state> &openset,vector<state> closedset) {
					
	state newstate = current;
	swap(newstate,newI,newJ,posi,posj);
		if(!isInSet(newstate,closedset)) {

			int tentative_g_score = current.g + 1;

			if( !isInSet(newstate,openset) || tentative_g_score < newstate.g ) {

				newstate.g = tentative_g_score;
				newstate.f = newstate.g + state::heuristic(newstate,goal);
                
                state *temp = new state();
                *temp = current;
				newstate.came_from = temp;
				openset.push_back(newstate);
			}
		}
}

void neighbors(state current,state goal, vector<state> &openset,vector<state> closedset) {
	int i,j,posi,posj;
	
	//Find the position of '0'
	for(i=0;i<DEG;i++)
		for(j=0;j<DEG;j++)
			if(current.board[i][j] == 0)
			{
				posi=i;
				posj=j;
			}

	i=posi; j=posj;

	if((i-1)>=0) {
		addNeighbor(current,goal,(i-1),j,posi,posj,openset,closedset);
	}
	
	if((i+1)<DEG) {
		addNeighbor(current,goal,(i+1),j,posi,posj,openset,closedset);
	}

	if((j-1)>=0) {
		addNeighbor(current,goal,i,(j-1),posi,posj,openset,closedset);
	}
	
	if((j+1)<DEG) {
		addNeighbor(current,goal,i,(j+1),posi,posj,openset,closedset);
	}
}

void reconstruct_path(state current, vector<state> &came_from) {
    state *temp = &current;
    while(temp != NULL) {
        came_from.push_back(*temp);
        temp = temp->came_from;
    }
}

bool astar(state start, state goal) {
	vector<state> closedset;
	vector<state> openset;

	state current;

	start.g = 0;
	start.f = start.g + state::heuristic(start,goal);

	openset.push_back(start);
	
	while(!openset.empty()) {

		sort(openset.begin(),openset.end(),lowerF);

		current = openset[0]; //select the state having lowest fscore value.
		
		if(current == goal) {
			reconstruct_path(current,output);
			return SUCCESS;
		}

		openset.erase(openset.begin());
		closedset.push_back(current);

		neighbors(current,goal,openset,closedset);
	}

	return !SUCCESS;
}

int main() {
	state start,goal;
	int i,j;
	
	freopen("in.txt","r",stdin);
	
	cout<<"Enter "<<DEG<<"x"<<DEG<<" board :\n";
	for(i=0;i<DEG;i++)
		for(j=0;j<DEG;j++)
			cin>>start.board[i][j];

	cout<<"Enter goal board :\n";
	for(i=0;i<DEG;i++)
		for(j=0;j<DEG;j++)
			cin>>goal.board[i][j];

	if(astar(start,goal) == SUCCESS) {
        for(i=output.size()-1;i>=0;i--) {
            output[i].print();
        }
        cout<<"\nSUCCESSFUL.\nNumber of moves: "<<output.size()-1<<endl;
	}
	else
		cout<<"\nUNSUCCESSFUL.\n";
	return 0;
}

//reference site "https://github.com/Bhambya/Astar-8-puzzle/blob/master/astar.cpp"
