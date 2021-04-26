//SATYAM SINGH  
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

#define ll 				long long int
#define pb 				push_back
#define mod             1000000007
#define inf             1e18
#define ump				unordered_map
#define mp 				make_pair

#define  inpv(v,n)  for(int i=0;i<n;i++) cin>>v[i]
#define  outv(v)    for(auto i:v) cout<<i<<' ' 
#define  loop(i,a,b)  for(int i=(a);i<(b);i++)
#define  looprev(i,a,b)  for(int i=(a);i>=0;i--)

void file_i_o()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}

// structure to create a node or vertex of graph 
struct node{
    int data;
    node*next;
};

// this will create the head pointer for particuklar for particular vertex 
struct List{
    node*head;
};

// this will create the adjancency list with v vertices and array of linked lists 
struct Gr{
    int v;
    List* array;
};


// a graph to implement all the function 
class Graph {

    // declaring an adjancency list name 
    Gr * adj;

    // this is the function to creata a node or vertex and allocate the memory 
    node*newnode(int data) {
        node*temp=new node();
        temp->data = data;
        temp->next = NULL;
        return temp;
    }

    //  public method starts 
    public:

    //  constructor to initialise and allocate the memory for the graph 
    Graph(int v) {
        // create a new graph 
        this->adj = new Gr();
        // allocate the no of vertices 
        adj->v = v;

        // allocate the linked list memory according to the no of vertices 
        adj->array = (struct List*)malloc(v * sizeof(struct List));

        //  initially head of all the vertices will point to null 
        loop(i,0,v) {
            adj->array[i].head = NULL;
        }
    }

    //  this the function to add the edge in graph 
    void addedge(int src,int dest) {
        // create a temp node of vertex dest 
        node * temp = this->newnode(dest);
        // des next will point to the source head 
        temp->next = this->adj->array[src].head ;
        // now move the source head to new allocate vertex which is the temp
        this->adj->array[src].head = temp;

        //  since it is undirected graph we need to make changes in both the vertices 
        // same process only change the source and destination 
        node * temp1 = this->newnode(src);
        temp1->next = this->adj->array[dest].head;
        this->adj->array[dest].head = temp1;
    }

    // this is the display funtion to display the graph in map linked list format
    void display() {
        // traverl to each vertex 
        for(int i = 0;i<this->adj->v ; i++) {
            // get the referene of the head pointer of particular vertex 
            node* temp = this->adj->array[i].head;
            cout<<i<<" --> ";
            // traverse all it edges one by one 
            while(temp) {
                cout<<temp->data <<" ,";
                temp=temp->next;
            }
            cout<<endl;
        }
    }


    // this is the dfs helper which will do the dfs traversal of graph 
    void dfsHelper(int src,ump<int,bool> &visited) {
        visited[src] =true;
        cout<<src<<" ";
        // get the reference to head pointer of the src vertex 
        node * temp =this->adj->array[src].head;
        // traverse while the list is empty 
        while(temp!=NULL) {
            //  if not vistes the vertex ,visit it and go to depth 
            if(not visited[temp->data]) {
                dfsHelper(temp->data,visited);
            }
            temp=temp->next;
        }
    }
    
    // dfs function 
    void DFS(int src) {
        ump<int,bool>visited;  // map to mark the visted places while dfs traversal 
        dfsHelper(src,visited);
    }

    // bfs function to traverse the graph in bfs manner 
    void BFS(int src) {
        // for visiting the vertex 
        ump<int,bool>visited;

        queue<int>q;
        visited[src] =true;
        q.push(src);
        while(not q.empty()) {
            int v= q.front();
            q.pop();
            cout<<v<<" ";

            node * temp =this->adj->array[v].head;
            while(temp !=NULL ) {
                if(not visited[temp->data]) {
                    visited[temp->data] = true;
                    q.push(temp->data);
                }
                temp=temp->next;
            }
        }
    }
};

int main( ) {
    clock_t begin = clock();
    file_i_o();
    // Write your code here....

    // get the vertex and edges from the user 
    int V,E;
    cin>>V>>E;

    // make a graph obj 
    Graph g(V);

    // get the edges and connecting edges 
    loop(i,0,E) {
        int u,v;
        cin>>u>>v;
        g.addedge(u,v);
    }

    g.DFS(1);
    cout<<endl;
    g.BFS(1);
     

    // code ends here !!!!!! 
    #ifndef ONLINE_JUDGE 
      clock_t end = clock();
      cout<<"\n\nExecuted In: "<<double(end - begin) / CLOCKS_PER_SEC<<" seconds";
    #endif 
    return 0;
}
