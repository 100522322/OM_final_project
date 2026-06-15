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
    void update();
    int worst_index() const;

    vector<int> get_conflicting_vertices(const vector<int>& solution) const;
    int best_color_local(int node, const vector<int>& solution) const;
    int count_conflicts_local(int node, const vector<int>& solution, int color) const;
};