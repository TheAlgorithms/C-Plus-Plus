#include <iostream>
#include <list>
#include <map>
using namespace std;
class Node {
 public:
    char data;
    bool visited;
    Node(char el) {
        data = el;
        visited = false;
    }
};
class Compare_nodes {
 public:
    bool operator()(Node* temp_u, Node* temp_v) {
        return (temp_u->data < temp_v->data);
    }
};
class Graph {
 private:
    map<Node*, list<Node*>, Compare_nodes> adjlist;
    list<Node*> node_list;
    Node* find_node_in_list(char val) {
        for (auto i : node_list) {
            if (val == i->data) {
                return i;
            }
        }
        return NULL;
    }

    void _run_Dfs(Node* temp) {
        temp->visited = true;
        for (auto i : adjlist[temp]) {
            if (i->visited == false) {
                _run_Dfs(i);
            }
        }
    }
    bool _is_Connected() {
        int count = 0;
        Node* temp;
        for (auto i : adjlist) {
            count++;
            if (i.second.size() != 0) {
                temp = i.first;
                break;
            }
        }
        if (count ==
            adjlist.size())  // if there are no edges in the graph,
                             // then it will be considered as Eulerian acording
                             // to the definition of Eulerian Graph
        {
            return true;
        }
        _run_Dfs(temp);
        for (auto i : node_list) {
            if (i->visited == false && adjlist[i].size() > 0) {
                return false;
            }
        }
        return true;
    }
    int _is_Eulerian() {
        if (_is_Connected() == false) {
            return 0;
        }
        int odd = 0;
        for (auto i : adjlist) {
            if ((i.second.size()) % 2 != 0) {
                odd++;
            }
        }
        if (odd > 2) {
            return 0;
        }

        return (odd) ? 1 : 2;
    }

 public:
    void push_edge(char val_u, char val_v) {
        Node* temp_u = NULL;
        Node* temp_v = NULL;
        if (node_list.empty() == true) {
            temp_u = new Node(val_u);
            temp_v = new Node(val_v);
            node_list.push_back(temp_u);
            node_list.push_back(temp_v);
            adjlist[temp_u].push_back(temp_v);
            adjlist[temp_v].push_back(temp_u);
        } else {
            temp_u = find_node_in_list(val_u);
            temp_v = find_node_in_list(val_v);
            if (temp_u == NULL && temp_v == NULL) {
                temp_u = new Node(val_u);
                temp_v = new Node(val_v);
                node_list.push_back(temp_u);
                node_list.push_back(temp_v);
            } else if (temp_u != NULL && temp_v == NULL) {
                temp_v = new Node(val_v);
                node_list.push_back(temp_v);
            } else if (temp_u == NULL && temp_v != NULL) {
                temp_u = new Node(val_u);
                node_list.push_back(temp_u);
            } else {
                // both the nodes are already created and are found in the
                // variable temp_u, temp_v
            }
            adjlist[temp_u].push_back(temp_v);
            adjlist[temp_v].push_back(temp_u);
        }
    }
    void show_graph_data() {
        for (auto i = adjlist.begin(); i != adjlist.end(); i++) {
            Node* temp_u = i->first;
            list<Node*> j = i->second;
            cout << temp_u->data << "-->";
            for (auto k = j.begin(); k != j.end(); k++) {
                Node* temp_v = *k;
                cout << temp_v->data << " ";
            }
            cout << endl;
        }
    }
    void is_Eulerian() {
        int res = _is_Eulerian();
        if (res == 0) {
            cout << "The graph is not Eulerian" << endl;
        } else if (res == 1) {
            cout << "The graph has a Euler path" << endl;
        } else {
            cout << "The graph has a Euler cycle" << endl;
        }
    }
};
int main() {
    Graph obj;

    obj.push_edge('a', 'b');
    obj.push_edge('a', 'd');
    obj.push_edge('a', 'c');
    obj.push_edge('b', 'c');
    obj.push_edge('d', 'e');
    // obj.push_edge('b','d');
    obj.push_edge('a', 'e');

    obj.show_graph_data();
    obj.is_Eulerian();
    return 0;
}