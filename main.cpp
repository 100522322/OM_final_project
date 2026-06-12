#include <iostream>
#include "Graph.h"
#include "SA.h"
#include "ABC.h"
#include <chrono>
#include <string>

int main() {
    srand(time(0));

    std::vector<std::string> instanaces = {
        "queen6_6.col.txt",
        "le450_15b.col.txt",
        "DSJC125.1.col",
        "DSJC250.5.col",
        "DSJC500.5.col"
    };
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


    int n_colors = 8;
    Graph new_graph = Graph();
    new_graph.load_from_file("instances/DSJC125.1.col");

    std::cout << "SA running" << std::endl;


    int iterations = 10000;
    float temperature = 100.0f;
    float alpha = 0.99f;

    SA sa(n_colors, new_graph, iterations, temperature, alpha);

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    std::vector<int> results = sa.run();

    auto end = clock::now();

    std::cout << "Best fitness:" << results[0] << std::endl;
    std::cout << "Worst fitness:" << results[1] << std::endl;

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "SA run time: " << elapsed.count() << " seconds\n";


    n_colors = 8;
    new_graph = Graph();
    new_graph.load_from_file("instances/" + instanaces[2]);

    iterations = 10000;
    int colony_size = 20;
    int limit = 50;

    std::cout << "ABC running" << std::endl;

    ABC abc(new_graph, n_colors, colony_size, limit, iterations);

    using clock = std::chrono::high_resolution_clock;
    start = clock::now();

    results = abc.run();

    end = clock::now();
    elapsed = end - start;

    std::cout << "Best fitness:" << results[0] << std::endl;
    std::cout << "Worst fitness:" << results[1] << std::endl;
    std::cout << "ABC run time: " << elapsed.count() << " seconds\n";
}
