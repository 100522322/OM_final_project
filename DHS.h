#pragma once

#include <vector>
#include "Graph.h"

using namespace std;

struct Harmony {
    vector<int> individual;
    int fitness;
};

class DHS {
public:
    Graph& graph;
    int num_colors;
    int harmony_size;
    double HMCR;
    double PAR;
    int iterations;

    vector<Harmony> harmony_mem;
    Harmony best;
    Harmony worst;

    DHS(Graph& graph, int num_colors, int harmony_size, double HMCR, double PAR, int iterations);

    vector<int> run();

    void initialize();
    vector<int> new_solution();
    int best_color(int node, vector<int> individual);
    void update();
    int worst_index() const;
};