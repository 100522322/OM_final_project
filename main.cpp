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

    const string instance = "DSJC250.5.col";
    const int n_colors = 28;
    const int iterations = 10000;

    Graph graph;
    if (!graph.load_from_file("instances/" + instance)) {
        return 1;
    }

    cout << "Instance: " << instance << endl;
    cout << "Nodes: " << graph.num_nodes << ", edges: " << graph.num_edges << endl;
    cout << "Colors (k): " << n_colors << ", iterations: " << iterations << endl << endl;

    float temperature = 100.0f;
    float alpha = 0.99f;

    cout << "SA running (baseline)" << endl;
    SA sa(n_colors, graph, iterations, temperature, alpha);

    auto start = chrono::steady_clock::now();
    vector<int> results = sa.run();
    auto end = chrono::steady_clock::now();

    cout << "Best fitness: " << results[0] << endl;
    cout << "Worst fitness: " << results[1] << endl;
    cout << "SA run time: " << chrono::duration<double>(end - start).count() << " seconds\n\n";

    int colony_size = 20;
    int limit = 50;

    cout << "ABC running" << endl;
    ABC abc(graph, n_colors, colony_size, limit, iterations);

    start = chrono::steady_clock::now();
    results = abc.run();
    end = chrono::steady_clock::now();

    cout << "Best fitness: " << results[0] << endl;
    cout << "Worst fitness: " << results[1] << endl;
    cout << "ABC run time: " << chrono::duration<double>(end - start).count() << " seconds\n\n";

    int harmony_size = 20;
    double HMCR = 0.9;
    double PAR = 0.3;

    cout << "DHS running" << endl;
    DHS dhs(graph, n_colors, harmony_size, HMCR, PAR, iterations);

    start = chrono::steady_clock::now();
    results = dhs.run();
    end = chrono::steady_clock::now();

    cout << "Best fitness: " << results[0] << endl;
    cout << "Worst fitness: " << results[1] << endl;
    cout << "DHS run time: " << chrono::duration<double>(end - start).count() << " seconds\n";

    return 0;
}
