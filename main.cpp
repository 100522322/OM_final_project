#include <iostream>
#include "Graph.h"
#include "SA.h"

int main() {
    srand(time(0));

    /*
    Graph graph = Graph();

    graph.load_from_file("instances/DSJC125.1.col");

    std::cout << "There are " << graph.num_nodes<< " nodes and " << graph.num_edges << " edges" << std::endl;

    for (Node node : graph.nodes) {
        std::cout << "Node_id:"<<node.id << std::endl;
    }


    std::vector<int> colors;
    // List of colors for testing fitness
    for (int i = 0; i < graph.num_nodes; i++) {

        colors.push_back(rand()%12+1);
    }

    std::cout << "Last Color:" << colors.back() <<std::endl;

    int fitness = graph.fitness(colors);
    std::cout << "Fitness:" << fitness << std::endl;
    */

    int n_colors = 5;
    Graph new_graph = Graph();
    new_graph.load_from_file("instances/DSJC125.1.col");
    int iterations = 10000;
    float temperature = 100.0f;
    float alpha = 0.99f;

    SA sa(n_colors, new_graph, iterations, temperature, alpha);

    std::vector<int> results = sa.run();

    std::cout << "Best fitness:" << results[0] << std::endl;
    std::cout << "Worst fitness:" << results[1] << std::endl;

}
