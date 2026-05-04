#include <iostream>
#include "Graph.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph graph = Graph();

    graph.load_from_file("instances/DSJC125.1.col");

    std::cout << "There are " << graph.num_nodes<< " nodes and " << graph.num_edges << " edges" << std::endl;

    for (Node node : graph.nodes) {
        std::cout << "Node_id:"<<node.id << std::endl;
    }

}
