#include <iostream>

using namespace std;

bool checkFileExistence(string filename) {
    ifstream f(filename);
    return f.is_open();
}

bool getFile(int argc, char *argv[], ifstream& file) {   
    
    if (argc <= 1) {
        cout << "Incorrect arguments." << endl;
        return false;
    } else if (!checkFileExistence(argv[1])) {
        cout << "File " << argv[1] << " not found." << endl;
        return false;
    }

    file.open(argv[1]);
    return true;
}

Graph create_graph(ifstream& file) {   
    
    int V, E;
    int src, dest, weight;

    file >> V;
    file >> E;

    Graph graph(V);

    while(file >> src && file >> dest && file >> weight) {
        graph.addEdge(src, dest, weight);
    }
    file.close();

    return graph;
}