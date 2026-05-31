//
// Created by hugo2 on 03/05/2026.
//

#ifndef OM_FINAL_PROJECT_GRAPH_H
#define OM_FINAL_PROJECT_GRAPH_H
#include <string>
#include <vector>

#include "Node.h"


class Graph {
  public:
    int num_nodes;
    int num_edges;
    std::vector<Node> nodes;

    Graph();

    bool load_from_file(const std::string& filename);

    int count_conflicts(int node_id);

    int fitness(std::vector<int> colors);

    void color_graph(std::vector<int> colors);

    std::vector<int> random_color_graph(int num_colors);
};


#endif //OM_FINAL_PROJECT_GRAPH_H
