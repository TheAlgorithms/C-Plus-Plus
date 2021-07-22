/**
 * @file
 * @brief An implementation of
 * [graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type)) using
 * [adjacency list](https://en.wikipedia.org/wiki/Adjacency_list).
 *
 * A graph is a data structure that consists of the following two components:
 *  * A finite set of vertices also called as nodes.
 *  * A finite set of ordered pair of the form (u, v) called as edge.
 *
 * The (u, v) pair of edges is ordered pair in case of a directed graph while
 * this is not the case in undirected graphs.
 *
 * ##Implimentation:
 * In case of adjacency list, the index of vertices which are connected to a
 * vertex is stored in a linked list connected to that vertex. The structure
 * looks like:
 *
 *      index    vertices         adjacencyList
 *        0        node1  ->  adjacencyList[1, 3, 6]
 *        1        node2  ->  adjacencyList[1, 0]
 *        2        node3  ->  adjacencyList[1, 2, 3]
 *        3        node4  ->  adjacencyList[1]
 *      ...
 *
 * The main advantage of this implementation is that we are using only the space
 * which is needed in other words the space complexity is better than adjacency
 * matrix where we use O(v^2) where v is the number of vertices.
 *
 * Unlike in case of adjacency matrix where we use space to store both info,
 * connected and not connected, in case of adjacency list we only store the info
 * of is_connected.
 *
 * A disadvantage of this implementation over adjacency matrix is the time taken
 * for finding an index in adjacency list, because it'll be a linear search,
 * time will be O(n), where in adjacency matrix it was constant as we has to
 * access elements by index.
 *
 * #Applications:
 *      * Graphs are used to represent many real-life applications:
 *      * Graphs are used to represent networks. The networks may include paths
 * in a city or telephone network or circuit network.
 *      * Graphs are also used in social networks like linkedIn, Facebook.
 *      * For example, in Facebook, each person is represented with a vertex(or
 * node).
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 * */

#include <cassert>   ///  for assert
#include <iostream>  ///  for IO Operations
#include <vector>    ///  for std::vector

/**
 * @namespace adjacency_list_graph
 * @brief Implementation of graph data structure using adjacency list.
 */
namespace adjacency_list_graph {

/**
 * @namespace adjacency_list
 * @brief Implementation of linked list for adjacency list.
 */
namespace adjacency_list {
/**
 * @brief A Node structure representing a single node in Linked list
 */
class Node {
 public:
    int64_t data{};        ///< The key/value of the node
    int64_t weight = 1;    ///< Weight of the edge, default weight is 1
    Node *next = nullptr;  ///< Pointer to next node
};

/**
 * @brief A singly linked list implementation for adjacency list.
 */
class LinkedList {
 private:
    Node *head = nullptr;  ///< Pointer to head node of linked list
    Node *tail = nullptr;  ///< Pointer to the tail node of linked list

    /**
     * @brief Allocates a new node in heap for given data as a node and returns
     * it's pointer.
     * @param data Data for the node.
     * @returns A pointer to the newly allocated Node.
     * */
    static Node *getNode(int64_t data, int64_t weight) {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->weight = weight;
        return new_node;
    }

 public:
    /**
     * @brief A utility function to access the head pointer by object.
     * @returns A pointer to the head of linked list.
     * */
    Node *getHead() { return head; }

    /**
     * @brief An insert function to create and add new nodes in linked list from
     * the given data.
     * @param data Data to be inserted in the node.
     * @param weight Weight to be associated with the edge associated with the
     * node.
     * @returns Void
     * */
    void insert(int64_t data, int64_t weight = 1) {
        Node *node = getNode(data, weight);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = tail->next;
        }
    }

    /**
     * @brief A utility function to check if the given data exists in linked
     * list or not.
     * @param data Data to be searched
     * @returns bool
     * */
    bool exists(int64_t data) {
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    /**
     * @brief A function which converts linked list in a vector.
     * @returns std::Vector A vector of data.
     * */
    std::vector<int64_t> getAsList() {
        std::vector<int64_t> list;
        Node *temp = head;
        while (temp != nullptr) {
            list.push_back(temp->data);
            temp = temp->next;
        }
        return list;
    }

    /**
     * @brief A function which converts linked list in a vector with the edge
     * weight.
     * @returns std::Vector A vector of data and their edge weight.
     * */
    std::vector<std::pair<int64_t, int64_t>> getAsWeightedList() {
        std::vector<std::pair<int64_t, int64_t>> list;
        Node *temp = head;
        while (temp != nullptr) {
            std::pair<int64_t, int64_t> edge(temp->data, temp->weight);
            list.push_back(edge);
            temp = temp->next;
        }
        return list;
    }

    /**
     * @brief Prints the linked list.
     * @returns Void
     * */
    void print() {
        Node *temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void deallocateLinkedList() {
        while (head != nullptr) {
            Node *temp = head->next;
            delete head;
            head = temp;
        }
        head = nullptr;
    }
};

}  // namespace adjacency_list

/**
 * @namespace graph
 * @brief Implementation of graph data structure
 */
namespace graph {

/**
 * @brief A Vertex structure representing a vertex in graph.
 */
class Vertex {
 public:
    int64_t data;  ///< The key/value of the node
    adjacency_list::LinkedList
        *adjacencyList;  ///< The adjacency list for storing edges.
};

/**
 * @brief A graph implementation using adjacency list
 */
class Graphs {
 private:
    std::vector<Vertex *> vertices;  ///< A list of vertices/nodes in the graph

    /**
     * @brief Allocates a new node in heap for given data as a vertex and also
     * assign adjacency list head pointer.
     * @param data Data for the vertex.
     * @returns A pointer to the newly allocated Node.
     * */
    static Vertex *makeVertex(int64_t data) {
        auto *newVertex = new Vertex;
        auto *connections = new adjacency_list::LinkedList;
        newVertex->data = data;
        newVertex->adjacencyList = connections;
        return newVertex;
    }

 public:
    /**
     * @brief A utility function to find the index of the given data in
     * vertices.
     * @param data Data of the vertex to be searched.
     * @returns int64_t Index of the node if found, else -1.
     * */
    int64_t getIndex(int64_t data) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i]->data == data)
                return i;
        }
        return -1;
    }

    /**
     * @brief Adds a node in the graph for given data.
     * @param data Data for the node.
     * @returns void
     * */
    void addNode(int64_t data) {
        Vertex *newVertex = makeVertex(data);
        vertices.push_back(newVertex);
    }

    /**
     * @brief Adds multiple nodes at once in the graph for vector given data.
     * @param data Data vector for the nodes.
     * @returns void
     * */
    void addNodes(const std::vector<int64_t> &data) {
        for (auto i : data) {
            addNode(i);
        }
    }

    /**
     * @brief Adds an edge between two vertices.
     * @param edge A pair of int64_t data representing nodes/vertex in the graph
     * @returns bool Returns true if the edge is added successfully else if the
     * given node not found, will return false.
     * */
    bool addEdge(std::pair<int64_t, int64_t> edge) {
        int64_t edgeFromIndex = getIndex(edge.first);
        int64_t edgeToIndex = getIndex(edge.second);

        if (edgeFromIndex == -1 or edgeToIndex == -1) {
            return false;
        }

        /// Un-directed bidirectional graph
        vertices[edgeFromIndex]->adjacencyList->insert(edgeToIndex);
        vertices[edgeToIndex]->adjacencyList->insert(edgeFromIndex);
        return true;
    }

    /**
     * @brief Adds a weighted edge between two vertices with the given weights.
     * @param edge A pair of int64_t data representing nodes/vertex in the
     * graph.
     * @returns bool Returns true if the edge is added successfully else if the
     * given node not found, will return false.
     * */
    bool addWeightedEdge(const std::vector<int64_t> &weightedEdge) {
        int64_t edgeFromIndex = getIndex(weightedEdge[0]);  /// edge from vertex
        int64_t edgeToIndex = getIndex(weightedEdge[1]);    /// edge to vertex
        int64_t weight = weightedEdge[2];  /// weight of the edge

        if (edgeFromIndex == -1 or edgeToIndex == -1) {
            /// if any of the vertex (from or to) not found, that means there
            /// can not be an edge, return false.
            return false;
        }

        /// add index of the vertex in adjacency list
        vertices[edgeFromIndex]->adjacencyList->insert(edgeToIndex, weight);
        vertices[edgeToIndex]->adjacencyList->insert(edgeFromIndex, weight);

        return true;
    }

    /**
     * @brief A function to check if the two nodes are connected or not.
     * @param nodeData1 Data of the first node.
     * @param nodeData2 Data of the second node.
     * @returns bool Returns true if the edge exists between given two nodes
     * else returns false.
     * */
    bool isConnected(int64_t nodeData1, int64_t nodeData2) {
        int64_t index = getIndex(nodeData2);
        if (index == -1) {
            /// if the given node is not found.
            return false;
        }

        for (Vertex *vertex : vertices) {
            if (vertex->data == nodeData1) {
                return vertex->adjacencyList->exists(index);
            }
        }
        return false;
    }

    /**
     * @brief For a given data, will find all the connected vertices to that
     * node.
     * @param data Data for the node for which you want all the connected nodes.
     * @returns std::vector A vector of vertices from the adjacency list of all
     * the connected nodes.
     * */
    std::vector<int64_t> getAllConnectedAsVertex(int64_t data) {
        std::vector<int64_t> temp;
        for (Vertex *vertex : vertices) {
            if (vertex->data == data) {
                std::vector<int64_t> indexes =
                    vertex->adjacencyList->getAsList();
                for (int64_t index : indexes) {
                    temp.push_back(vertices[index]->data);
                }
            }
        }
        return temp;
    }

    /**
     * @brief Prints the graph with details of nodes and edges.
     * @returns void
     * */
    void printGraph() {
        for (Vertex *vertex : vertices) {
            std::cout << "Node: " << vertex->data
                      << " is connected to :" << std::endl;
            std::cout << "--> ";
            for (auto indexPair : vertex->adjacencyList->getAsWeightedList()) {
                Vertex *connectedNode = vertices[indexPair.first];
                if (connectedNode) {
                    std::cout << "(Node: " << connectedNode->data
                              << ", weight : " << indexPair.second << "), ";
                } else {
                    std::cout << "None ";
                }
            }
            std::cout << std::endl;
        }
    }
    /**
     * @brief Destructor to cleanup the allocated memory.
     * */
    void deallocateGraph() {
        for (auto vertex : vertices) {
            vertex->adjacencyList->deallocateLinkedList();
            delete vertex->adjacencyList;
            delete vertex;
            vertex = nullptr;
        }
        vertices.clear();
    }
};
}  // namespace graph
}  // namespace adjacency_list_graph

/**
 * @brief Test cases implementation.
 * */
namespace test_cases {
namespace graph = adjacency_list_graph::graph;  /// namespcase alias

/**
 * @brief A function to print given message on console.
 * @tparam T Type of the given message.
 * @returns void
 * */
template <typename T>
void log(T msg) {
    // It's just to avoid writing cout and endl
    std::cout << "[TESTS] : ---> " << msg << std::endl;
}

/**
 * @brief A test case which adds weighted and non weighted edges in graph.
 * The assert statement will check connected nodes for a given vertex against
 * the expected output.
 * @returns void
 * */
static void testCase_1() {
    const std::vector<int64_t> expectedOutput{2, 3, 4, 5, 8};
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    log("This is test case 1 : ");
    graph::Graphs graphs = graph::Graphs();

    std::vector<int64_t> nodes{1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<std::pair<int64_t, int64_t>> edges{
        std::pair<int64_t, int64_t>(1, 2), std::pair<int64_t, int64_t>(1, 3),
        std::pair<int64_t, int64_t>(1, 4), std::pair<int64_t, int64_t>(1, 5),
        std::pair<int64_t, int64_t>(8, 1),
    };

    std::vector<std::vector<int64_t>> weighted{
        std::vector<int64_t>{2, 3, 4},
        std::vector<int64_t>{2, 4, 4},
        std::vector<int64_t>{2, 5, 4},
        std::vector<int64_t>{2, 6, 4},
    };

    graphs.addNodes(nodes);  /// add nodes to the graph

    for (auto edge : edges) {
        /// add edges to between nodes
        graphs.addEdge(edge);
    }
    for (const auto &weightedEdge : weighted) {
        /// add weighted edges to between nodes
        graphs.addWeightedEdge(weightedEdge);
    }

    /// a vector containing all the connected nodes to the given vertex
    std::vector<int64_t> output = graphs.getAllConnectedAsVertex(1);

    log("Checking assert...");
    assert(std::equal(expectedOutput.begin(), expectedOutput.end(),
                      output.begin()));
    log("Assert check successful!");
    graphs.deallocateGraph();
}

/**
 * @brief A test case which adds non weighted edges in graph.
 * The assert statement will check connected nodes for a given vertex against
 * the expected output.
 * @returns void
 * */
static void testCase_2() {
    const std::vector<int64_t> expectedOutput{56, 11};
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    log("This is test case 2 : ");
    graph::Graphs graphs = graph::Graphs();

    std::vector<int64_t> nodes{
        56, 78, 13, 900,
        67, 11, 0,  66};  /// vertex data to be inserted in graph as vertices

    std::vector<std::pair<int64_t, int64_t>> edges{
        std::pair<int64_t, int64_t>(56, 900),
        std::pair<int64_t, int64_t>(13, 78),
        std::pair<int64_t, int64_t>(56, 0),
        std::pair<int64_t, int64_t>(900, 11),
        std::pair<int64_t, int64_t>(67, 66),
        std::pair<int64_t, int64_t>(11, 56),
    };  /// edges data to be added in graph as edges between two nodes.

    graphs.addNodes(nodes);  /// add nodes to the graph

    for (auto edge : edges) {
        /// add edges to between nodes
        graphs.addEdge(edge);
    }

    std::vector<int64_t> output = graphs.getAllConnectedAsVertex(
        900);  /// vertex data to be inserted in graph as vertices

    log("Checking assert...");
    assert(std::equal(expectedOutput.begin(), expectedOutput.end(),
                      output.begin()));
    log("Assert check successful!");

    graphs.deallocateGraph();
}

/**
 * @brief A test case which adds non weighted edges in graph.
 * The assert statement will check if two nodes are connected or not.
 * @returns void
 * */
static void testCase_3() {
    const bool expectedOutput = true;
    log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    log("This is test case 3 : ");
    graph::Graphs graphs = graph::Graphs();

    std::vector<int64_t> nodes{
        1, 2, 3, 4,
        5, 6, 7, 8};  /// vertex data to be inserted in graph as vertices

    std::vector<std::pair<int64_t, int64_t>> edges{
        std::pair<int64_t, int64_t>(1, 2), std::pair<int64_t, int64_t>(1, 3),
        std::pair<int64_t, int64_t>(1, 4), std::pair<int64_t, int64_t>(1, 5),
        std::pair<int64_t, int64_t>(8, 1), std::pair<int64_t, int64_t>(3, 4),
    };  /// edges data to be added in graph as edges between two nodes.

    graphs.addNodes(nodes);  /// add nodes to the graph

    for (auto edge : edges) {
        /// add edges to between nodes
        graphs.addEdge(edge);
    }

    bool output = graphs.isConnected(
        3, 4);  /// a bool to check if two nodes are connected or not
    log("Checking assert...");
    assert(output == expectedOutput);
    log("Assert check successful!");

    graphs.deallocateGraph();
}

static void executeTests() {
    std::cout << "Executing Test Cases..." << std::endl;
    testCase_1();
    testCase_2();
    testCase_3();
    std::cout << "Test Cases Over!" << std::endl << std::endl;
}

}  // namespace test_cases

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
// */
int main(int argc, char *argv[]) {
    test_cases::executeTests();  // run self-test implementations

    namespace graph = adjacency_list_graph::graph;  /// namespace alias

    graph::Graphs graphs = graph::Graphs();  /// graph object

    std::vector<int64_t> nodes = {
        1, 2, 3, 4,
        5, 6, 7, 8};  /// vertex data to be inserted in graph as vertices

    std::vector<std::pair<int64_t, int64_t>> edges{
        std::pair<int64_t, int64_t>(1, 2), std::pair<int64_t, int64_t>(1, 3),
        std::pair<int64_t, int64_t>(1, 4), std::pair<int64_t, int64_t>(1, 5),
        std::pair<int64_t, int64_t>(8, 1),
    };  /// edges data to be added in graph as edges between two nodes.

    graphs.addNodes(nodes);  /// add nodes to the graph

    for (auto edge : edges) {
        /// add edges to between nodes
        graphs.addEdge(edge);
    }

    graphs.printGraph();  /// print the relationship of nodes and edges.
    graphs.deallocateGraph();

    return 0;
}
