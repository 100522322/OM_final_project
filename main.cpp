#include <iostream>
#include "Graph.h"
#include "SA.h"
#include "ABC.h"
#include "DHS.h"
#include <chrono>
#include <string>

using namespace std;

int main() {
    srand(time(0));

    vector<string> instanaces = {
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

    cout << "SA running" << endl;


    int iterations = 10000;
    float temperature = 100.0f;
    float alpha = 0.99f;

    SA sa(n_colors, new_graph, iterations, temperature, alpha);

    using clock = std::chrono::steady_clock;
    auto start = clock::now();

    vector<int> results = sa.run();

    auto end = clock::now();

    cout << "Best fitness:" << results[0] << endl;
    cout << "Worst fitness:" << results[1] << endl;

    chrono::duration<double> elapsed = end - start;
    cout << "SA run time: " << elapsed.count() << " seconds\n";


    n_colors = 8;
    new_graph = Graph();
    new_graph.load_from_file("instances/" + instanaces[2]);

    iterations = 10000;
    int colony_size = 20;
    int limit = 50;

    cout << "ABC running" << endl;

    ABC abc(new_graph, n_colors, colony_size, limit, iterations);

    start = clock::now();

    results = abc.run();

    end = clock::now();
    elapsed = end - start;

    cout << "Best fitness:" << results[0] << endl;
    cout << "Worst fitness:" << results[1] << endl;
    cout << "ABC run time: " << elapsed.count() << " seconds\n";

    cout << "DHS running" << endl;

    new_graph = Graph();
    new_graph.load_from_file("instances/" + instanaces[2]);

    int harmony_size = 20;
    double HMCR = 0.9;
    double PAR = 0.3;

    DHS dhs(new_graph, n_colors, harmony_size, HMCR, PAR, iterations);

    start = clock::now();
    results = dhs.run();
    end = clock::now();

    elapsed = end - start;

    cout << "Best fitness:" << results[0] << endl;
    cout << "Worst fitness:" << results[1] << endl;
    cout << "DHS run time: " << elapsed.count() << " seconds\n";

    return 0;
}
