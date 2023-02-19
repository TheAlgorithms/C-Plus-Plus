#include <vector> //for std::vector<T>
#include <iostream> //for IO operations

// The algorithm is using the colouring technique for finding a cycle in a graph
// you can see more details here : https://en.wikipedia.org/wiki/Graph_coloring


class Graph {
 private:
  int V;//number of Vertices
  std::vector<int> *adj;//adjacency list for our graph

  //typical node colouring , if the node is unvisited we color it as NOT_STARTED
  //if we've started the traversal , we color it as STARTED
  //if we've finished the traversal we color it as FINISHED
  enum status { NOT_STARTED, STARTED, FINISHED };

  /**
  * @brief Typical DFS funtion for our graph
  *
  * @param visited : node colouring vector to keep track of our nodes
  * @param previous : our parent vector so we can print the path(or else path tree)
  */
  //typical DFS for the graph , we have to store colored nodes in visited and a parent vector with previous
  void dfs_help(int u, std::vector<status> &visited, std::vector<int> &previous) const {
    visited[u] = STARTED;
    for (int v : adj[u]){
      if (visited[v] == NOT_STARTED) {// if its unvisited we update the previous vector
        previous[v] = u;
        //and we dfs recursively again
        dfs_help(v, visited, previous);
      } else if (visited[v] == STARTED) {
        //if we see the node again in the same traversal then we have a cycle
        // so we throw the pair of nodes to print the cycle
        throw std::make_pair(u, v);
      }
     }
      //if we finish the traversal , we update the current node to FINISHED
    visited[u] = FINISHED;
  }

 public:
  /**
  * @brief Constructor of our graph
  *
  * @param n number of Vertices
  */
  Graph(int n) { V = n; adj = new std::vector<int>[V]; }
  /**
  * @brief Destructor of our graph
  */
  ~Graph() { delete [] adj; }

  /**
  * @brief Function that add edge between two nodes or vertices of graph
  *
  * @param v any node or vertex of graph
  * @param w any node or vertex of graph
  */
  //currently the graph is directed , if you want an undirected graph
  //delete comments
  void addEdge(int v, int w) { 
    adj[v].push_back(w); 
    //adj[w].push_back(v);
  }
  /**
  * @brief Function that detects if there's a cycle in the graph
  *
  * @param path : a vector that we store the path of the cycle
  */
  bool cycle(std::vector<int> &path) const {
    std::vector<status> visited(V, NOT_STARTED);//visited vector , at start all NOT_STARTED
    std::vector<int> previous(V, -1);//parent vector with all values at -1
    try {
      for (int u = 0; u < V; ++u){
        if (visited[u] == NOT_STARTED){//if node's unvisited , we dfs
          dfs_help(u, visited, previous);
     }
       }
      return false;//there's no cycle
    } catch (const std::pair<int, int> &p) {//here we catch-if there's a cycle- the pair of nodes from dfs_help
      path.clear();
      for (int u = p.first; u != p.second; u = previous[u]){
        //we traverse the parent vector and we update the path
        path.push_back(u);
      }
      path.push_back(p.second);//we push the last node
      path.push_back(p.first);//we add the first node to clearly see the cycle
      std::reverse(path.begin(), path.end());//we reverse so we can have a better outcome(because its from end to start)
      return true;//and we return true if there's a cycle in our graph
    }
  }
};

int main(){
    /**
    * @brief Main function
    *
    * @param v: number of vertices
    * @param u: number of edges
    * @param path: path saving array
    */
    int v , u;
    std::cout << "Enter the number of vertices , :";
    std::cin >> v;
    std::cout << "Enter the number of edges , :";
    std::cin >> u;
    Graph g(v);
    while(u--){
        int fr , to; std::cin >> fr >> to;
        g.addEdge(fr , to);
    }
    std::vector<int> path;//here we store-if there's a cycle- the path from start-end
    bool temp = g.cycle(path);
    if(temp){
        std::cout << "Cycle detected , path is -> ";
        for(int &x : path){
            std::cout << x << " ";
        }
        std::cout << '\n';
    }
    else{
        std::cout << "No cycle" << '\n';
    }
}

